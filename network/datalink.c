#include <stdio.h>
#include <string.h>

#include "protocol.h"
#include "datalink.h"

#define MAX_SEQ 31			// 帧序号上限
#define NR_BUFS ((MAX_SEQ+1)/2)		// 窗口大小上限
#define MAX_PKT 256			// 最大帧内数据长度	
#define ACK_TIMER 280		// ACK帧超时重传等待时间

#define inc(k) if(k < MAX_SEQ)k++;else k=0	// 帧序号递增

typedef enum {false, true} boolean;		// 布尔
typedef unsigned char seq_nr;			// 帧序号
typedef unsigned char frame_kind;		// 帧类型

struct FRAME{		// 帧格式
	unsigned short kas;		// 帧的类型、序号和ACK序号
	unsigned char  data[MAX_PKT];	// 帧内数据
	unsigned int   padding;			// CRC填充位
};

struct BUF{			// 缓存格式
	unsigned char buf[MAX_PKT];		// 缓存单元数据
	unsigned int length;			// 实际数据长度
};

boolean no_nak = true;		// 是否发送过nak
boolean phl_ready = false;	// 物理层是否就绪
boolean low_error = false;	// 信道是否具有低误码率
long long bits_received;	// 已收到的数据总位数
long long error_received;	// 已出现的错误总位数
int DATA_TIMER = 5000;		// Data帧超时重传等待时间

static boolean between(seq_nr a, seq_nr b, seq_nr c){
	return ((a <= b) && (b < c)) || ((c < a) && (a <= b)) || ((b < c) && (c < a));
}

static void put_frame_crc(unsigned char *frame, int len){
	*(unsigned int *)(frame + len) = crc32(frame, len);
	send_frame(frame, len + 4);
	phl_ready = false;
}

static void put_frame_even(unsigned char *frame){
	*(unsigned short *)(frame + 1) = (((*frame)<<8)|(*frame));
	send_frame(frame, 2);
}

static void put_frame_bit(unsigned char *frame){
	unsigned char check = 0;
	check ^= (*frame)&0x01; check ^= (*frame)&0x02; check ^= (*frame)&0x04; check ^= (*frame)&0x08;
	check ^= (*frame)&0x10; check ^= (*frame)&0x20; check ^= (*frame)&0x40; check = check << 7;
	(*frame) ^= check;
	send_frame(frame, 1);
}

boolean double_check(unsigned short * t){
	if (((*t)&0x00FF) == (((*t)>>8)&0x00FF))
		return true;
	return false;
}

boolean bit_check(unsigned char * t){
	unsigned char temp = 0;
	unsigned char origin = *t;
	while (origin>0){
		temp ^= (origin&1);
		origin>>=1;
	}
	return temp == 0 ? true : false;
}


static void send_link_frame(frame_kind fk, seq_nr frame_nr, seq_nr frame_expceted, struct BUF buffer[]){
	struct FRAME s;
	s.kas = 0;
	s.kas |= fk;
	if (fk == FRAME_DATA){
		memcpy(s.data, buffer[frame_nr % NR_BUFS].buf, buffer[frame_nr % NR_BUFS].length);
		s.kas |= (frame_nr << 7);
		dbg_frame("Send DATA %d %d, ID %d\n", frame_nr, 
			((frame_expceted + MAX_SEQ) % (MAX_SEQ + 1)), *(short *)s.data);
	}
	s.kas |= (((frame_expceted + MAX_SEQ) % (MAX_SEQ + 1)) << 2);
	if (fk == FRAME_NAK){
		dbg_frame("Send NAK %d\n", frame_expceted);
		no_nak = false;
	}
	if (fk == FRAME_ACK || fk == FRAME_NAK){
		if (low_error)
			put_frame_bit((unsigned char*)&s);
		else
			put_frame_even((unsigned char*)&s);
	}
	else
		put_frame_crc((unsigned char*)&s, 2 + buffer[frame_nr% NR_BUFS].length);
	if (fk == FRAME_DATA){
		start_timer(frame_nr % NR_BUFS, DATA_TIMER);
	}
	stop_ack_timer();
}

int main(int argc, char ** argv){
	seq_nr ack_expected = 0;		// 等待对方确认的帧序号
	seq_nr next_frame_to_send = 0;	// 将要发送的帧序号
	seq_nr frame_expected = 0;		// 期望收到的帧序号
	seq_nr nbuffered = 0;			// 当前缓冲区使用数目
	seq_nr r_seq = 0, r_ack = 0;	// 从接收到的帧中提取出的帧序号和ACK序号
	seq_nr too_far = NR_BUFS;		// 当前窗口上界
	unsigned char CHECKBIT = 0;
	int i;
	int event, arg, len;
	struct FRAME r;
	struct BUF out_buf[NR_BUFS];
	struct BUF in_buf[NR_BUFS];
	boolean arrived[NR_BUFS];
	for (i = 0; i < NR_BUFS; i++)
		arrived[i] = false;
	protocol_init(argc, argv);
	disable_network_layer();
	while (true){

		event = wait_for_event(&arg);

		switch (event)
		{
		case NETWORK_LAYER_READY:
			nbuffered++;
			out_buf[next_frame_to_send % NR_BUFS].length = 
				get_packet(out_buf[next_frame_to_send % NR_BUFS].buf);
			send_link_frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
			inc(next_frame_to_send);
			break;

		case PHYSICAL_LAYER_READY:
			phl_ready = true;
			break;

		case FRAME_RECEIVED:
			len = recv_frame((unsigned char *)&r, sizeof r);
			bits_received += len*8;
			if ((len < 5 && len != 2 && len != 1) || (len > 5 && crc32((unsigned char *)&r, len) != 0) ||
				(len == 2 && double_check((unsigned short *)&r) == false) ||
				(len == 1 && bit_check((unsigned char *)&r) == false) ){
				dbg_event("****RECEIVER ERROR, BAD CRC CHECKSUM****\n");
				error_received += 1;
				if (no_nak){
					send_link_frame((frame_kind)FRAME_NAK, 0, frame_expected, out_buf);
				}
				break;
			}

			CHECKBIT = *((unsigned char *)(&r));

			if ((CHECKBIT & 0x03) == FRAME_ACK){
				r_ack = (CHECKBIT & 0x7C) >> 2;
				dbg_frame("Recv ACK  %d\n", r_ack);
			}

			if ((CHECKBIT & 0x03) == FRAME_DATA){
				r_seq = (r.kas & 0x0F80) >> 7;
				r_ack = (r.kas & 0x007C) >> 2;
				dbg_frame("Recv DATA %d %d, ID %d\n", r_seq, r_ack, *(short *)r.data);
				if ((r_seq != frame_expected) && no_nak)
					send_link_frame((frame_kind)FRAME_NAK, 0, frame_expected, out_buf);
				else
					start_ack_timer(ACK_TIMER);
				if (between(frame_expected, r_seq, too_far) && (arrived[r_seq % NR_BUFS] == false)){
					arrived[r_seq % NR_BUFS] = true;
					memcpy(in_buf[r_seq % NR_BUFS].buf, r.data, len - 6);
					in_buf[r_seq % NR_BUFS].length = len - 6;
					while (arrived[frame_expected % NR_BUFS]){
						put_packet(in_buf[frame_expected % NR_BUFS].buf, in_buf[frame_expected % NR_BUFS].length);
						no_nak = true;
						arrived[frame_expected % NR_BUFS] = false;
						inc(frame_expected);
						inc(too_far);
  					}
				}
			}

			if ((CHECKBIT & 0x03) == FRAME_NAK){
				r_ack = (CHECKBIT & 0x7C) >> 2;
				dbg_frame("Recv NAK %d\n", r_ack);
				if (between(ack_expected, (r_ack + 1) % (MAX_SEQ + 1), next_frame_to_send)){
					send_link_frame((frame_kind)FRAME_DATA, (r_ack + 1) % (MAX_SEQ + 1), frame_expected, out_buf);
				}
			}

			while (between(ack_expected, r_ack, next_frame_to_send)){
				nbuffered--;
				stop_timer(ack_expected % NR_BUFS);
				inc(ack_expected);
			}
			break;

		case ACK_TIMEOUT:
			dbg_event("----ACK %d timeout\n", arg);
			send_link_frame((frame_kind)FRAME_ACK, 0, frame_expected, out_buf);
			break;
		
		case DATA_TIMEOUT:
			dbg_event("---- DATA %d timeout\n", arg);
			if (!between(ack_expected, arg, next_frame_to_send))
				arg = arg + NR_BUFS;
			send_link_frame((frame_kind)FRAME_DATA, arg, frame_expected, out_buf);
			break;

		default:
			break;
		}
		if (nbuffered < NR_BUFS && phl_ready == true)
			enable_network_layer();
		else
			disable_network_layer();
		if ((error_received<<22) < bits_received){
			low_error = true;
		}else{
			low_error = false;
		}
		if (bits_received > 0x3FFFFFFFFFFF){
			bits_received >>= 20;
			error_received >>= 20;
		}
		if (low_error){
			DATA_TIMER = 3500;
		}
		else{
			DATA_TIMER = 5000;
		}
	}
}