// @author: Forec(王耀)
// @last-edit: 2016-12-18
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @g++ version: 5.4
// @filename: main.cpp

#include "FIFO.hpp"
#include "LRU.hpp"
#include <stdio.h>

int main(){
	FIFO f = FIFO(20);
	LRU l = LRU(20);
	f.simulateSeveralTimes(50, 40, 40);
	l.simulateSeveralTimes(50, 40, 40);
	printf("%f %f\n", 
			f.getPageFaultRate(),
			l.getPageFaultRate());
	return 0;
}
