#ifndef __TEST_H_
#define __TEST_H_

#include "stdafx.h"

void initServer();
void simpleTest();

template <typename T>
void simpleShow(T &);

template <typename T>
void showDetails(T &);

template <typename T>
void shows(T &, bool);

template <typename T>
void simpleShowToString(T &, std::string &);

template <typename T>
void showDetailsToString(T &, std::string &);

template <typename T>
void showsToString(T &, bool, std::string &);


void console(int, char **);
std::string recv(std::string);
void IO();
std::string backIO();
bool startClientSocket();
bool startServerSocket();
void startClient();

#endif