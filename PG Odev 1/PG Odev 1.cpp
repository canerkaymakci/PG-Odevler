//As noted in the assignment document, I used 12 hours format in my project.

#include <iostream>

using namespace std;

//Created a struct with a name that "Time". "times" is our object name.
struct Time
{
	int hour;
	int minute;
	int second;
	long total_sec;
}times;

//Mentioned our Convert Function prototype here.
int convertTime(int hrs, int mins, int secs);


int main() {

	//Created colon char (":") as our number splitter
	char colon;

	cout << "Enter the time in 12 hour format like HH:MM:SS..: ";
	cin >> times.hour >> colon >> times.minute >> colon >> times.second;
	cout << endl << endl;

	//If there is an error with our time, it will be detected and will be written.
	if (12 < times.hour || times.hour < 0 || 60 <= times.minute || times.minute < 0 || 60 <= times.second || times.second < 0)
	{
		//Hours error will be detected there.
		if (times.hour > 12 || times.hour < 0)
		{
			cout << "Girilen saat degeri yanlistir..: " << times.hour << endl << endl;
		}

		//Minutes error will be detected there.
		if (60 <= times.minute || times.minute < 0)
		{
			cout << "Girilen dakika degeri yanlistir..: " << times.minute << endl << endl;
		}

		//Seconds error will be detected there.
		if (60 <= times.second || times.second < 0)
		{
			cout << "Girilen saniye degeri yanlistir..: " << times.second << endl << endl;
		}
	}
	//If there isn't any error, Total Seconds will be written.
	else
	{
		//Used our Convert Function there.
		times.total_sec = convertTime(times.hour, times.minute, times.second);
		cout << "Girdiginiz saate gore toplam saniyeniz..: " << times.total_sec;
	}

	return 0;
}

//Converted our HH:MM:SS times in this function. Returned with total seconds.
int convertTime(int hrs, int mins, int secs)
{
	long totalSecs = 0;

	totalSecs += (hrs * 3600) + (mins * 60) + secs;

	return totalSecs;
}