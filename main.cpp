/*
	Flight Calculator Project
	Jacob Coble
	2/4/23
*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

void getCityList(vector<string> &cities, vector<double> &latList, vector<double> &lonList);
void displayCities(vector<string> cities);
int getPlaneSpeed();
int getInput(vector<string> vec);
void removeCity(vector<string>& cities, vector<double>& latList, vector<double>& lonList, vector<string>& newCities, vector<double>& newLatList, vector<double>& newLonList, int index);

// Required Functions 
double haversine(double lat1, double lat2, double lon1, double lon2, double radius);
double getFlightTime(double dis, double speed);

const double RADIUS = 3958.8;
const double PI = 3.1415927 / 180;

int main()
{
	bool running = true;
	while (running)
	{
		vector<string> cityNames;
		vector<double> cityLat;
		vector<double> cityLon;
		vector<string> calculatingCities;
		vector<double> calculatingLat;
		vector<double> calculatingLon;
		getCityList(cityNames, cityLat, cityLon);
		int planeSpeed = getPlaneSpeed();
		cout << "Choose your starting city: " << endl;
		int startingCity = getInput(cityNames);
		removeCity(cityNames, cityLat, cityLon, calculatingCities, calculatingLat, calculatingLon, startingCity);
		cout << endl << "Choose your destination city: " << endl;
		int destinationCity = getInput(cityNames);
		removeCity(cityNames, cityLat, cityLon, calculatingCities, calculatingLat, calculatingLon, destinationCity);
		int distance = haversine(calculatingLat.front(), calculatingLat.back(), calculatingLon.front(), calculatingLon.back(), RADIUS);
		int speed = getPlaneSpeed();
		int time = getFlightTime(distance, speed);
		cout << endl << "Your trip from " << calculatingCities.front() << ", to " << calculatingCities.back() << ", will take " << time << " hours with a distance of " << distance << " miles and a plane speed of " << speed << " mph." << endl;

		int keepRunning;
		cout << endl << endl << "Enter 1 to run the program again, otherwise enter any value to exit the program: ";
		cin >> keepRunning;
		if (keepRunning == 1)
		{
			cout << endl << endl;
			continue;
		}
		else
		{
			break;
		}
	}
	return 0;
}


void getCityList(vector<string>& cities, vector<double>& latList, vector<double>& lonList)
{
	cities = { "Miami Beach, FL, USA", "Fargo, ND, USA", "Idaho City, ID, USA", "Gastona, NC, USA", "Redwood City, CA, USA", "Houston, TX, USA", "Juneau, AK, USA", "Beverly Hills, CA, USA", "Tampa, FL, USA", "Wilmington, NC, USA" };
	latList = { 25.793449, 46.877186, 43.828850, 35.255280, 37.487846, 29.749907, 58.305801, 34.073620, 27.964157, 34.225727 };
	lonList = { -80.139198, -96.789803, -115.837860, -81.180275, -122.236115, -95.358421, -134.433304, -118.400352, -82.452606, -77.944710 };
}
void displayCities(vector<string> cities)
{
	for (int i = 0; i < cities.size(); i++)
	{
		cout << i << ".    " << cities[i] << endl;
	}
}
int getPlaneSpeed()
{
	int maxPSpeed = 575;
	int minPSpeed = 460;
	int pSpeed = rand() % (maxPSpeed - minPSpeed + 1) + minPSpeed;
	return pSpeed;
}
int getInput(vector<string> vec)
{
	displayCities(vec);
	cout << "Welcome to Dorwich Airlines!" << endl;
	int input;
	while (true)
	{
		cout << "Please indicate which city you would like to choose: ";
		cin >> input;
		if (!input)
		{
			cout << "Invalid entry, integers (0-9) only." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else
		{
			if (input < vec.size())
			{
				break;
			}
			else
			{
				cout << "Invalid entry, entry too large." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
		}
	}

	return input;

}
void removeCity(vector<string>& cities, vector<double>& latList, vector<double>& lonList, vector<string>& newCities, vector<double>& newLatList, vector<double>& newLonList, int index)
{
	newCities.push_back(cities[index]);
	newLatList.push_back(latList[index]);
	newLonList.push_back(lonList[index]);
	cities.erase(cities.begin() + index);
	latList.erase(latList.begin() + index);
	lonList.erase(lonList.begin() + index);
}
//Required Functions
double haversine(double lat1, double lat2, double lon1, double lon2, double radius)
{
	double lat = (lat2 - lat1) * PI;
	double lon = (lon2 - lon1) * PI;
	lat1 = lat1 * PI;
	lat2 = lat2 * PI;
	double internal = pow(sin(lat / 2), 2) + pow(sin(lon / 2), 2) * cos(lat1) * cos(lat2);
	double distance = (2 * asin(sqrt(internal))) * radius;
	return distance;
}
double getFlightTime(double dis, double speed)
{
	// Unsure of why I need to have lat1, lat2, lon1, lon2 passed to this function when I can call the distance and speed and calculate it from there.

	double time = dis / speed;
	return time;
}