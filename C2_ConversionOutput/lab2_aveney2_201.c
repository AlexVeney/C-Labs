/*
 * Alexandra Veney 
 * 
 * Lab 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	char tempInput[100];
	int temp;
	char windInput[100];
	double wind;

	printf("Enter temperature in degrees (F): \n");
	fgets(tempInput, 99, stdin);

	sscanf(tempInput, "%d", &temp);
	

	// Check for invalid temperature above 50 
	if(temp > 50){
		printf("Error: A temperature above 50 was entered\n");
		exit(0);
	}
	
	printf("Enter a value for windspeed (MPH): \n");
	fgets(windInput, 99,stdin);
	
	sscanf(windInput, "%lf", &wind);
	
	// Check for invalid windspeed below 3.0
	if(wind < 3.0){
		printf("Error: A windspeed below 3.0 was entered\n");
		exit(0);
	}

	double windChill;

	// Windspeed raised to a power of (+0.16)
	double windPow = pow (wind, 0.16);

	windChill = 35.74 + (0.6215 * temp) - (35.75 * windPow) +
	 (0.4275 * temp * windPow);


	printf("Temperature: %d degrees Fahrenheit\n", temp);
	printf("Wind Speed: %.1f mph\n", wind);
	printf("Wind Chill Index: %.1lf degrees Fahrenheit\n", windChill);

	return 0;

}
