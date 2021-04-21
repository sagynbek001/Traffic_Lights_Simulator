Important Notes:
1. To execute the program, the user needs to compile and run the code found in the file named Source.cpp
2. There is no menu to interact with a user. When the program is run, it starts the simulation automatically and no actions are required from the user.
3. The data (flow rates and cycle length) should be included in a txt file called SensorData.txt and be written in separate lines. The SensorData.txt is assumed to be located in the project folder together with Source.cpp
4. It is assumed that cycle length is a positive integer, while flow rates are non-negative real numbers.
5. The green timings are calculated according to the provided formula in the step 2.
6. The cycle length in the data file is assumed to be the summation of green timings only.
7. The simulation runs while at least one of the lights is working. If all the lights are turned off at some point the program is terminated.
8. The green timings of the turned off lights are set to 0, and the cycle length time is distributed to other lights proportionally among the turned-on lights only.
9. The green timings are rounded to the nearest integer and green timings cannot be 0 after the simulation is started. If the calculations lead to it being 0, then it is set to 1.
10. When the update interval time passes, the program waits for the occurring state timing and only after that updates the data members.