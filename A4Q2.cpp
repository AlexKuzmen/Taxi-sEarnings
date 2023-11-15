/* Eran and Alexander

Version 1.0
Report file summarizing taxi's earnings for August

Assumptions:
- 
*/
#include <iomanip>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double calculate_oneTripDist(int x_initial, int y_initial, 
int x_value, int y_value)
{
	double oneTripDist = 0;
	oneTripDist = sqrt(pow((y_value-y_initial),2)+pow((x_value-x_initial),2));
	
	return oneTripDist;
}

double calculate_oneTripCost(bool vip, double tripDist, int stops)
{
	double oneTripCost = 0;
	if(vip)
	{
		oneTripCost = 0.25*(15*stops + 2.6*tripDist);
	}
	else
	{
		oneTripCost = (15*stops + 2.6*tripDist);
	}
	return oneTripCost;
}

int main()
{
	
//General Need: totaldistance (month), total amount(month), 
//longest trip (month), least expensive trip (month), 
//Trip count per Trip sort of (month)

//Charges:( 15.00 per stop, 2.6 per km travel, vips get 25% off )

//display 
//trip#, vip, stops, tripDist, tripCost, totalDist (Month), totalCost (Month)

//open and check file
	ifstream FileIn("taxi.txt");
	ofstream FileOut("output.txt");
	
	if(!FileIn||!FileOut)
	{
		cout<<"Unable to open file";
		return EXIT_FAILURE;
	}
		
//declare variables to be written to from file (and month variables)										
	bool vip = 1;
	int stops = 0;
	double x_value = 0, y_value = 0;
	
	double total_distance = 0, total_amount = 0;
	double longest_trip = 0, least_expensive_trip = 1000000;//large
	
	int trip_count = 0;
	
	FileOut<<setw(15)<<"trip#"<<setw(15)<<"VIP"<<setw(15)<<"Stops"<<setw(15)
	<<"TripDist"<<setw(15)<<setw(15)<<"TripCost"<<setw(15)
	<<"TotalDist"<<setw(15)<<"TotalCost"<<endl;
//open file and read in values
	while(FileIn >> vip >> stops)
	{
		trip_count++;//what trip is this?
//declare tripDist and tripCost in here

		double tripDist = 0; double tripCost = 0;
		
//calculate distance back and add
		double x_initial = 0, y_initial = 0;
		
		for(int loop_stops = 0; loop_stops < stops; loop_stops++)
		{
			FileIn >> x_value >> y_value;
			tripDist += calculate_oneTripDist(x_initial, y_initial, 
			x_value, y_value);
			
			x_initial = x_value;
			y_initial = y_value;
		}//end for loop_stops
		tripDist += calculate_oneTripDist(x_initial, y_initial, 0, 0);
		
//calculate cost
		tripCost = calculate_oneTripCost(vip, tripDist, stops);
		
//calculate total distance cumulative
		total_distance += tripDist;

//calculate totalCost cumulative
		total_amount += tripCost;
		
//check for longest trip and least expensive trip
		if(longest_trip < tripDist)
		{
			longest_trip = tripDist;
		}
		
		if(least_expensive_trip > tripCost)
		{
			least_expensive_trip = tripCost;
		}
			
//print out using setW and setPrecision (to file) only if needed to be displayed
		if(trip_count <=4 || trip_count%10 == 0)
		{
			FileOut<<fixed<<setprecision(2);//for floating point numbers
			FileOut<<setw(15)<<trip_count<<setw(15)<<vip<<setw(15)
			<<stops<<setw(15)<<tripDist<<setw(15)<<tripCost<<setw(15)
			<<total_distance<<setw(15)<<total_amount<<endl;
		}
	}//end FileIn while loop
	
//print out what is wanted on the last line 
	FileOut<<setw(15)<<"TotalDistance"<<setw(15)<<"TotalAmount"<<setw(15)
	<<"LongestTrip"<<setw(15)<<"CheapestTrip"<<endl;
	
	FileOut<<fixed<<setprecision(2);//decimals for floating point numbers
	FileOut<<setw(15)<<total_distance<<setw(15)<<total_amount<<setw(15)
	<<longest_trip<<setw(15)<<least_expensive_trip;
	
	FileIn.close();
	FileOut.close();
	return EXIT_SUCCESS;
}
