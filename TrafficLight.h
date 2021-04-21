#pragma once

class TrafficLight {
private:
	//private data members
	int id;
	int state;
	int greenTime;
	//total number of lights is declared as a static variable
	//because it is common to the entire class
	static int totalNumberOfLights;
public:
	//default constructor
	TrafficLight()
	{
		totalNumberOfLights++;
		id = totalNumberOfLights;
		state = 1;
		greenTime = 0;
	}
	//accessors to the data members
	int getID() { return id; }
	int getState() { return state; }
	int getGreenTime() { return greenTime; }
	//modifiers of the data members
	void setState(int state) { this->state = state; }
	void setGreenTime(int greenTime) { this->greenTime = greenTime; }
	//class function to display all the data 
	//members about this particular traffic light
	void printLightInfo()
	{
		cout << "ID: " << id << endl;
		cout << "State: " << state << endl;
		cout << "Green Timing: " << greenTime << endl;
	}
	//accessor to the total number of traffic light objects created
	static int getTotalNumOfLights() { return totalNumberOfLights; }
};

//the static variable is initialized
int TrafficLight::totalNumberOfLights = 0;