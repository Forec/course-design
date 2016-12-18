// @author: Forec(王耀)
// @last-edit: 2016-12-18
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @g++ version: 5.4
// @filename: FIFO.hpp

#ifndef __FIFO_H
#define __FIFO_H

#include "BASIC.hpp"

class FIFO : public BASIC<int>{
private:
	int _front, _rear, _used;
	void swapIn(int);
public:
	FIFO(unsigned int pagePoolSize = 10):
		BASIC(pagePoolSize){
		_front = _rear = _used = 0;
	}
	void init(int);
	void clear();
	void destroy();
};

void FIFO::swapIn(int pageNumber){
	_swapTime ++;
	for (int i = _front; i < _rear; i++){
		if (_pageQueue[i] == pageNumber){	// page is in memory
			_pageFaultRate = float(_pageFaultTime) / _swapTime;
			return;
		}
	}
	// we need to swap the page into memory from disk
	_pageFaultTime ++;
	_pageFaultRate = float(_pageFaultTime) / _swapTime; 
	if (_used == _pagePoolSize){	// the page pool is full
		_pageQueue[_front] = pageNumber;	// swap out the earliest page
	} else{
		_pageQueue[_rear++] = pageNumber;
		_used ++;
	}
}

void FIFO::init(int pagePoolSize){
	BASIC::init(pagePoolSize);
	_front = _rear = _used = 0;
}

void FIFO::clear(){
	BASIC::clear();
	_front = _rear = _used = 0;
}

void FIFO::destroy(){
	BASIC::destroy();
	_front = _rear = _used = 0;	
}

#endif
