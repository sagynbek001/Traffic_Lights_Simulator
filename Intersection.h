#pragma once

//the maximum number of traffic lights this class can store is 20
#define MaxNumberOfLights 20

class Intersection {
private:
	//private data members
	int cycleLength;
	int numOfLights;
	TrafficLight Lights[MaxNumberOfLights];
	double flowRates[MaxNumberOfLights];
public:
	//constructor
	Intersection() {
		numOfLights = 0;
		cycleLength = 120;
		for (int i = 0; i < MaxNumberOfLights; i++)
		{
			flowRates[i] = 1000;
		}
	}
	//Accessors
	int getCycleLength() { return cycleLength; }
	int getNumOfLights() { return numOfLights; }
	double getFlowRates(int i) { return flowRates[i]; }
	//function to add new traffic lights to the class
	void addLight(TrafficLight A) {
		//if the current number of lights is at the boundary,
		//the message that no more additions are possible displayed
		if (numOfLights >= MaxNumberOfLights)
			cout << "Cannot add more traffic lights" << endl;
		else
		{
			//if the number of lights is ok, then the object is added to the
			//array of traffic lights and number of traffic lights
			//in this particlar intersection is incremented
			Lights[numOfLights] = A;
			numOfLights++;
		}
	}
	//this function is used to remove a light from the intersection
	bool dropLight(TrafficLight A) {
		//the ID of the traffic light that needs to be removed is assigned 
		//to some variable
		int keyID = A.getID();
		int foundIndex = -1;
		for (int i = 0; i < numOfLights; i++)
		{
			//when the light is found, its position in the array is also saved
			if (keyID == Lights[i].getID()) { foundIndex = i; break; }
		}
		//if the object wasn't found in the array, then the function returns false
		if (foundIndex == -1) return false;
		else {
			//otherwise, it removes the traffic light from the intersection
			//and moves all the elements of the array after the found element 
			//one place to the left and decrements the number fo lights 
			//stored in the intersection object
			numOfLights--;
			for (int k = foundIndex; k < numOfLights; k++)
			{
				Lights[k] = Lights[k + 1];
			}
		}
		return true;
	}
	//this function reads the data from a file and stores it in the 
	//corresponding data members
	void readTrafficData() {
		ifstream inFile;
		inFile.open("SensorData.txt");
		if (inFile.fail()) //open failed
		{
			cerr << "File sensor1.txt could not be opened";
			exit(1); //end execution of the program
		}
		inFile >> cycleLength;
		for (int i = 0; i < numOfLights; i++) {
			inFile >> flowRates[i];
		}
		inFile.close();
	}
	//this function updates the data members by calling the read function
	//and also updates the greenTime data members of separate traffic lights
	//included in the intersection by using the provided formula
	void updateTiming() {
		readTrafficData();
		for (int i = 0; i < numOfLights; i++) {
			if (Lights[i].getState() == 0) { flowRates[i] = 0; }
		}
		double sum = 0;
		for (int i = 0; i < numOfLights; i++) {
			sum += flowRates[i];
		}
		for (int i = 0; i < numOfLights; i++) {
			double calculatedTiming = round(cycleLength * flowRates[i] / sum);
			if ((int)calculatedTiming == 0 && Lights[i].getState() != 0) Lights[i].setGreenTime(1);
			else Lights[i].setGreenTime((int)calculatedTiming);
		}
	}
	//this function prints the relevant information about the update
	//this function should be called only after calling the updateTiming function
	void announceTheUpdate() {
		cout << endl;
		cout << "-Cycle length and flow rates were read by the program successfully" << endl;
		cout << "-Timings for the green state was updated and provided below" << endl;
		cout << "-Please, note that the values were rounded" << endl;
		cout << "Cycle length is: " << cycleLength << endl;
		for (int i = 0; i < numOfLights; i++)
		{
			cout << "Green timing for a traffic light with an ID ";
			cout << Lights[i].getID() << " is: " << Lights[i].getGreenTime() << endl;
		}
		cout << endl;
	}
	//this function checks if any of the traffic lights is working
	//in case all the traffic lights are in state 0, the program is exitted
	void checkTheLights() {
		int sum = 0;
		for (int i = 0; i < numOfLights; i++)
			sum += Lights[i].getState();
		if (sum == 0)
		{
			cerr << "\n --> The program stopped because all the lights are off! \n";  exit(1);
		}
	}
	//this function checks if the update interval state at the beginning of the simulation has passed
	//and if so it calls the update function and set the init time to the current time 
	//so that it could be in the same way in the next update iterations
	void updateIntervalChecker(long long int& initTime, long long int updateInterval) {
		if (time(NULL) >= initTime + updateInterval) {
			updateTiming();
			initTime = time(NULL);
			cout << endl;
			cout << "-" << updateInterval << " seconds have passed since the last update" << endl;
			announceTheUpdate();
			for (int k = 0; k < numOfLights; k++)
			{
				cout << "Light " << Lights[k].getID() << " \t";
			}
			cout << endl;
		}
	}
	//this is the core function for the simulatio of the traffic lights
	//system for a particular intersection 
	//the yellow timing and update interval values are passed to the run() function
	//wherever this funtion is called
	void run(int yellowTiming, long long int updateInterval) {
		cout << "Preset timing for the yellow state is " << yellowTiming << " seconds" << endl;
		cout << "Preset interval for the updates is " << updateInterval << " seconds" << endl;
		//timing is update before the program starts simulating
		updateTiming();
		announceTheUpdate();
		//initial time is stored for further usages
		long long int initTime = time(NULL);
		//columns for the traffic lights are displayed
		for (int i = 0; i < numOfLights; i++)
		{
			cout << "Light " << Lights[i].getID() << " \t";
		}
		cout << endl;
		//the following loop continues until all the lights are turned off
		while (true) {
			//check if not all the lights are turned off
			checkTheLights();
			//there is a certain algorithm that goes for each of the traffic lights
			for (int i = 0; i < numOfLights; i++) {
				//if the light is turned off, the loop is skipped
				//because there is no need to wait for this state
				if (Lights[i].getState() == 0) continue;
				//set the state to green
				Lights[i].setState(3);
				for (int j = 0; j < numOfLights; j++) { cout << stateConverter(Lights[j].getState()) << "\t\t"; }
				cout << endl;
				//and pause displaying for time that is equal to the green timing of this particulat traffic light
				wait(Lights[i].getGreenTime());
				//when the time for the green state passed, we check if the update interval passed too or not
				//if so, we update the data
				updateIntervalChecker(initTime, updateInterval);
				//set the state to yellow
				Lights[i].setState(2);
				for (int j = 0; j < numOfLights; j++) { cout << stateConverter(Lights[j].getState()) << "\t\t"; }
				cout << endl;
				//and pause displaying for time that is equal to yellow timing
				wait(yellowTiming);
				//when the time for the yellow state passed, we check if the update interval passed too or not
				//if so, we update the data
				updateIntervalChecker(initTime, updateInterval);
				//last, we set the state to red
				//and the loop goes for the next light and so on untill all of them are turned off
				Lights[i].setState(1);
			}
		}
	}
};