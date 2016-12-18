// @author: Forec(王耀)
// @last-edit: 2016-12-18
// @email: forec@bupt.edu.cn
// @codec: UTF-8
// @platform: GNU/Linux(Kernel 4.4.0)
// @g++ version: 5.4
// @filename: BASIC.hpp

#ifndef __PAGE_ALGO_H
#define __PAGE_ALGO_H

#include <stdlib.h>
#include <time.h>

#define random(x) (rand()%x)
// macro to create random numbers

template <typename T=int>
class BASIC{
protected:
	int _pagePoolSize;
	T *_pageQueue;
	int _pageFaultTime, _swapTime;
	float _pageFaultRate;
	virtual void swapIn(int) = 0;
public:
	BASIC(unsigned int pagePoolSize = 10){
		_pageFaultTime = _swapTime = 0;
		_pageFaultRate = 0;
		if (pagePoolSize < 0){
			pagePoolSize = 1;
		}
		_pagePoolSize = pagePoolSize;
		_pageQueue = new T[pagePoolSize];
	}
	~BASIC(){
		if (_pageQueue != nullptr){
			delete _pageQueue;
		}
	}
	void simulate(int, int);
	void simulateSeveralTimes(int, int, int);
	void init(int);
	void clear();
	void destroy();
	float getPageFaultRate();
};

template <typename T>
void BASIC<T>::simulate(int swapTime, int maxPageNumber){
	srand( (int)time(NULL) );
	for (int i = 0; i < swapTime; i ++){
		swapIn(random(maxPageNumber));
	}
}

template <typename T>
void BASIC<T>::simulateSeveralTimes(int times,
									int swapTime, 
									int maxPageNumber){
	float totalPageFaultRate = 0;
	for (int i = 0; i < times; i++){
		clear();
		simulate(swapTime, maxPageNumber);
		totalPageFaultRate += _pageFaultRate;
	}
	_pageFaultRate = totalPageFaultRate / times;
}

template <typename T>
void BASIC<T>::init(int pagePoolSize){
	_pageFaultRate = 0;
	_pageFaultTime = _swapTime = 0;
	if (pagePoolSize < 0){
		pagePoolSize = 1;
	}
	_pagePoolSize = pagePoolSize;
	if (_pageQueue != nullptr)
		delete _pageQueue;
	_pageQueue = new T[pagePoolSize];
}

template <typename T>
void BASIC<T>::clear(){
	_pageFaultTime = _swapTime = 0;
	_pageFaultRate = 0;
}

template <typename T>
void BASIC<T>::destroy(){
	clear();
	if (_pageQueue != nullptr)
		delete _pageQueue;
}

template <typename T>
float BASIC<T>::getPageFaultRate(){
	return _pageFaultRate;
}

#endif
