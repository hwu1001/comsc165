#include <iostream>
#include <string>

using namespace std;

class Car
{
private:
	int year;
	string make;
	int speed;

public:
	Car(int yr, string mk)
	{
		year = yr;
		make = mk;
		speed = 0;
	}

	Car()
	{
		// do nothing
	}

	int getYear()
	{
		return year;
	}

	string getMake()
	{
		return make;
	}

	int getSpeed()
	{
		return speed;
	}

	void accelerate()
	{
		speed += 5;
	}

	void brake()
	{
		speed -= 5;
	}

	void setYear(int yr)
	{
		year = yr;
	}

	void setMake(string mk)
	{
		make = mk;
	}

	void setSpeed(int spd)
	{
		speed = spd;
	}


};

int main()
{
	Car myCar(2002, "Honda Civic");

	cout << myCar.getYear() << endl;
	cout << "Accelerating" << endl;
	for (int i = 0; i < 5; i++)
	{
		myCar.accelerate();
		cout << "The current speed of the car: " << myCar.getSpeed() << endl;
	}

	cout << "Braking" << endl;
	for (int i = 0; i < 5; i++)
	{
		myCar.brake();
		cout << "The current speed of the car: " << myCar.getSpeed() << endl;
	}

	return 0;
}