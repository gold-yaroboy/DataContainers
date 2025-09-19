#include<iostream>
using namespace std;

void elevator(int floor);

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Enter the floor: "; cin >> n;
	elevator(n);
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Exit" << endl;
		return;
	}
	cout << "You are on the " << floor << " floor" << endl;
	elevator(floor-1);
	cout << "You are on the " << floor << " floor" << endl;
}