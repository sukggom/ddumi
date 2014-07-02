#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdlib.h> // rand, srand
#include <time.h> // timen
#include <sstream> // wostringstream
#include "BaseType.h"
#include "Utility.hpp"
#include "DoubleBuffer.h"
#include "UI.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
