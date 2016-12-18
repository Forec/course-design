// @author: Forec(王耀)
// @last-edit: 2016-12-18
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @g++ version: 5.4
// @filename: LRU.hpp

#ifndef __LRU_H
#define __LRU_H

#include <cstdlib>
#include <memory.h>
#include "BASIC.hpp"

struct node{
	int pageNumber;
	int recentUsed;		// how long since the last used
	bool used;
};

class LRU : public BASIC<node> {
private:
	void swapIn(int);
public:
	LRU(int pagePoolSize = 10):
		BASIC(pagePoolSize){
		memset(_pageQueue, 0, sizeof(node) * pagePoolSize);
	}
	void init(int);
	void clear();
};

void LRU::swapIn(int pageNumber){
	_swapTime ++;
	for (int i = 0; i < _pagePoolSize; i++){
		// refresh the recent used time
		if ( _pageQueue[i].used ){
			_pageQueue[i].recentUsed += 1;
		}
	}
	for (int i = 0; i < _pagePoolSize; i++){
		if ( _pageQueue[i].used && _pageQueue[i].pageNumber == pageNumber ){
			// already in page pool
			_pageQueue[i].recentUsed = 0;
			_pageFaultRate = float(_pageFaultTime) / _swapTime;
			return;
		}
	}
	
	_pageFaultTime ++;
	int maximum = 0, swapOutIndex = 0;
	// we need to find a free page, and maybe we need to swap out a 
	// page whose recentUsed is maximum
	for (int i = 0; i < _pagePoolSize; i++){
		if ( !_pageQueue[i].used ){
			// find a free page
			_pageQueue[i].used = true;
			_pageQueue[i].pageNumber = pageNumber;
			_pageQueue[i].recentUsed = 0;
			_pageFaultRate = float(_pageFaultTime) / _swapTime;
			return;
		} else {
			// refresh the most far page index
			if (_pageQueue[i].recentUsed > maximum){
				maximum = _pageQueue[i].recentUsed;
				swapOutIndex = i;
			}
		}
	}
	// now we need to swap the swapOutIndex page
	_pageQueue[swapOutIndex].pageNumber = pageNumber;
	_pageQueue[swapOutIndex].recentUsed = 0;
}

void LRU::clear(){
	BASIC::clear();
	memset(_pageQueue, 0, sizeof(node) * _pagePoolSize);
}

#endif
