// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件

#ifndef __STDAFX_H_
#define __STDAFX_H_

#include <iostream>
#include <string>
#include <vector>
#include "human.h"
#include "club.h"
#include "filter.h"
#include "control.h"
#include "io.h"

class base;
class player;
class employee;
class club;
struct filter;
class control;

extern control *CT;

#endif