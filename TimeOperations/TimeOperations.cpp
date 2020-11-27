// TimeOperations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TimeOperations.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// YYYYMMDDHHMMSS	
	wstring date1 = L"20201031000000";
	wstring date2 = L"20201101000000";

	//compareDates(date1, date2);
	test();

	return 0;
}

time_t to_seconds(const wstring date)
{
	// This can be improved and use std::string class instead of wstring 
	// and probably std::stoi() (that is supported from C++11) instead of wcstol

	time_t retval = 0;
	tm Time;	
	
	Time.tm_year = wcstol(date.substr(0,4).c_str(), NULL, 10) -1900;
	Time.tm_mon = wcstol(date.substr(4,2).c_str(), NULL, 10) -1; // Months go from 0-11
	Time.tm_mday = wcstol(date.substr(6,2).c_str(), NULL, 10);
	Time.tm_hour = wcstol(date.substr(8,2).c_str(), NULL, 10);
	Time.tm_min = wcstol(date.substr(10,2).c_str(), NULL, 10);
	Time.tm_sec = wcstol(date.substr(12,2).c_str(), NULL, 10);

	return mktime(&Time);
}

void compareDates(wstring date1, wstring date2)
{
	time_t d1=to_seconds(date1);
	wcout << "Seconds date1:" << d1 << std::endl;
	time_t d2=to_seconds(date2);
	wcout << "Seconds date2:" << d2 << std::endl;

	wcout << "Date comparison 1st:" << date1.c_str() << " 2nd: " << date2.c_str() << std::endl;
	if(d1==d2) printf("EQUAL\n");
	if(d2>d1)  printf("second date is later\n");
	if(d2<d1)  printf("second date is earlier\n");
}

/*
 * Test weather a date is lower than a consecutive date along current year
 *
*/
bool test()
{
	int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int month, d;
	SYSTEMTIME st;
	GetLocalTime(&st);
	wstring year = formatInt(st.wYear, 4);
	wstring time = L"000000"; // We don't need time for this test
	wstring currentDate = L"19000101" + time;
	wstring newDate = currentDate;

	// Check each month of the year
	for (month = 0; month <= 12; month++)
	{
		// And each day of the month
		for(d = 1; d <= monthDays[month]; d++)
		{
			wstring w_Month = formatInt(month+1); // Because months start in 1 not zero
			newDate = year + w_Month + formatInt(d) + time;
			time_t t_newDate = to_seconds(newDate);
			time_t t_currentDate = to_seconds(currentDate);

			if (t_newDate < t_currentDate)
			{
				// Something is wrong, new date cannot be lower than current date
				wcout << L"Test failed at currentDate>" << currentDate.c_str() << L" and newDate>" << newDate.c_str() << std::endl;
				return false;
			}
			//wcout << L"Current>" << currentDate.c_str() << L" vs New>" << newDate.c_str() << L" OK" << std::endl;
			currentDate = newDate;
		}
	}
	wcout << L"All good" << std::endl;
	return true;
}

wstring formatInt(int number, int width, wchar_t pad)
{
	wostringstream stream;
	stream << std::setw(width) << std::setfill(pad) << number;
	return stream.str();
}
