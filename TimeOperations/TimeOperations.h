#include "windows.h"
#include <iostream>
using std::wcout;
using std::cout;
using std::wstring;
#include <sstream>
using std::wostringstream;
#include <iomanip>

#include <time.h>

time_t to_seconds(const std::wstring date);
void compareDates(wstring date1, wstring date2);
bool test();
wstring formatInt(int number, int width=2, wchar_t=L'0');