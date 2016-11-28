#ifndef HEAP_H_
#define HEAP_H_ 
#include <algorithm>

template<typename T> 
void swap(T &a,T &b){
	T temp=a;
	a = b;
	b = temp;
}

template<class T, int N> class heap_t {
private:
	int size;
	T s[N];
	void up(int x) {
		if (x != 1) {
			if (s[x >> 1] < s[x]) {
				swap(s[x >> 1], s[x]);
				up(x >> 1);
			}
		}
	}
	void down(int x) {
		if (x <= size) {
			if ((x << 1) <= size) {
				int ch = x << 1;
				if (ch + 1 <= size && s[ch] < s[ch + 1]) {
					ch += 1;
				}
				if (s[x] < s[ch]) {
					swap(s[ch], s[x]);
					down(ch);
				}
			}
		}
	}
public:
	T top() {
		T result = s[1];
		return result;
	}
	T pop() {
		T result = s[1];
		swap(s[1], s[size--]);
		down(1);
		return result;
	}
	void push(T key) {
		s[++size] = key;
		up(size);
	}
	bool empty() {
		return size == 0;
	}
	bool full(){
		return size== MAXNN;
	}
};

#endif
