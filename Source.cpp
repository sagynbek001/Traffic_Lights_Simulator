/*--------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121							*/
/* Date: November 27. 2020													*/
/* Program: Source.cpp														*/
/* Description: This program simulates a traffic lights system for the		*/
/*				intersection of four roads and four lights respectively		*/
/*				according to the data provided in the sensor file.			*/
/*--------------------------------------------------------------------------*/

//including all the needed libraries 
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

//think of a way to include the wait function inside the TrafficLight class

//the wait function is used to pause the program and let it 
//continue only when certain amount of time passes
void wait(int t)
{
	//initial time is assigned to a variable
	long long int a = time(NULL);
	//current time is assigned to a variable
	//it is assumed that at this assignment moment the c variable is 0
	long long int c = time(NULL) - a;
	//next it print the phrase waiting...
	cout << "waiting... ";
	//until the required amount of time has not passed, the program does the following
	while (time(NULL) < (a + t)){
		//it checks if the current time changed
		if (time(NULL) - a > c) {
			//and if it changed, it deletes the printed time and displays the current time
			//in other words it just increments the current time displayed
			//to delete a character, \b delimiter was used
			//to find out how many times we need to delete, logarithm of 10 was used
			for (int i = 0; i < (int)(log(c) / log(10)) + 1; i++) { cout << "\b \b"; }
			//the current time is set
			c = time(NULL) - a;
			//and printed
			cout << c;
		}
	}
	//after the required time passes, the program removes everything it printed
	//again, depending on how many digits the current time has, the \b is used
	//it also removes the word 'waiting... ', that is why we need to delete 11 more times
	if (c!=0)
	for (int i = 0; i < (int)(log(c) / log(10)) + 12; i++) { cout << "\b \b"; }
	else 
	for (int i = 0; i < 13; i++) { cout << "\b \b"; }
}

//the function below is used to convert the state value from 
//the indication number to its meaning
string stateConverter(int state)
{
	//for this purpose switch operand was used
	switch (state)
	{
	case 0: return "Off"; break;
	case 1: return "Red"; break;
	case 2: return "Yellow"; break;
	case 3: return "Green"; break;
	default: return "Red";
	}
}

//the header files are included only at this point of the code
//because the functions wait and stateConverter are also called in these header files
#include "TrafficLight.h"
#include "Intersection.h"

int main()
{
	//here, 4 traffic light objects and one intersection object were created
	TrafficLight L1;
	TrafficLight L2;
	TrafficLight L3;
	TrafficLight L4;
	Intersection I1;
	//the traffic light objects were added to the intersection
	I1.addLight(L1);
	I1.addLight(L2);
	I1.addLight(L3);
	I1.addLight(L4);

	//the simulation for the intersection starts here
	//the yellow timing and update interval values are set before the 
	//simulation and passed to the run() function
	const int yellowTiming = 3;
	const long long int updateInterval = 60*60*24;

	I1.run(yellowTiming, updateInterval);

	return 0;
}