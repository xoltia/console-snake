#pragma once
#include "Screen.h"

#ifdef _DEBUG
#define LOG(x) Screen::Log(x);
#define CLEAR_LOG() Screen::ClearLog();
#else
#define LOG(x)
#define CLEAR_LOG()
#endif
