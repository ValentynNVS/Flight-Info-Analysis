/*
* FILE : mainFile.cpp
* PROGRAMMER : Valentyn Novosydliuk
* FIRST VERSION : 04/13/2024
* DESCRIPTION :
* This program reads the information from the text document and 
* displays the least fare of the flights. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int processFlight(char* filename, struct flightData* flightArray, int* totalcount);
int displayLeastFareDetails(struct flightData* flightArray, int numberOfFlights);
int parseLine(char* sourceVaribale, char* destinVariable, int* fareVariable, char* lineData);
void removeExtension(char* filename);

const int kCharMaxLenghts = 100;

/*A struct where the flight info will be stored*/
struct flightData {
	char from[kCharMaxLenghts] = "";
	char destination[kCharMaxLenghts] = "";
	int price = 0;
	char fileNameStorage[kCharMaxLenghts] = "";
};


int main(int* argc, char *argv[]) {

	FILE* filePointer = NULL;

#pragma warning(disable: 4996) 
	filePointer = fopen(argv[1], "r");
	if (filePointer == NULL) {
		printf("Could not open the file");
		return 1;
	}


	char fileName[kCharMaxLenghts] = "";
	struct flightData flightInfos[kCharMaxLenghts];
	int totalLinesRead = 0;

	char* pFileName = fileName;
}

int processFlight(char* filename, struct flightData* flightArray, int* totalcount) {

	return 0;
}

int displayLeastFareDetails(struct flightData* flightArray, int numberOfFlights) {

	return 0;

}

int parseLine(char* sourceVaribale, char* destinVariable, int* fareVariable, char* lineData) {

	return 0;

}

void removeExtension(char* filename) {

	

}