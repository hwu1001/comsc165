// Weather Data lab - 08/29/2017

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	const int SIZE = 12;
	string months[SIZE];
	double tempLow[SIZE], tempHigh[SIZE], avgTemp[SIZE];
	ifstream dataFile;
	dataFile.open("weather.txt");

	if (!dataFile)
	{
		cout << "Error opening file.";
	}
	else
	{
		//for (int i = 0; i < SIZE; i++)
		//{
		//	dataFile >> months[i] >> tempLow[i] >> tempHigh[i];
		//	dataFile.ignore();
		//	avgTemp[i] = (tempLow[i] + tempHigh[i]) / 2.0;
		//}

		int i = 0;
		while (dataFile >> months[i] >> tempLow[i] >> tempHigh[i])
		{
			avgTemp[i] = (tempLow[i] + tempHigh[i]) / 2.0;
			i++;
		}

		cout << "Average Temperatures: " << endl;
		for (int i = 0; i < SIZE; i++)
		{
			cout << months[i] << ": " << avgTemp[i] << endl;
		}
	}

	dataFile.close();

	return 0;
}
