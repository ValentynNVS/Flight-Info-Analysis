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

//
// FUNCTION : processFlight
// DESCRIPTION : This function gets the line from the file, pass it to
//				 the parsing function and prints accordings errors
//				 based on the return.
// PARAMETERS : int array[] : An array to store the integers entered by the user.
//              int numberOfElements : The number of elements in the array, indicating the size of the array.
// RETURNS : int 1 : In case of successfull function run
//
int processFlight(char* filename, struct flightData* flightArray, int* totalcount) {
	FILE* filePointer = NULL;
	filePointer = fopen(filename, "r");
	if (filePointer == NULL) {
		printf("Error reading or opening the %s\n", filename);
		return 0;
	}
	int index = *totalcount;
	char line[kCharMaxLenghts];
	/*Gets the whole line, pass it to the parseLine function
	and pass the pointers to the elements of a struct where the info would be stored*/
	while (fgets(line, kCharMaxLenghts, filePointer) != NULL && index < kCharMaxLenghts) {

		line[strcspn(line, "\n")] = '\0';
		int parseResult = parseLine(flightArray[index].from, flightArray[index].destination, &flightArray[index].price, line);
		if (parseResult != 1 && parseResult != -3) {
			printf("Error processing file %s line: %s\n", filename, line);
			if (parseResult == -3) {
				continue;
			}
			else if (parseResult == -2) {
				printf("Missing dash in %s\n", line);
			}
			else if (parseResult == -1) {
				printf("Missing comma in %s\n", line);
			}
		}
		else if (parseResult == 1) {
			strcpy(flightArray[index].fileNameStorage, filename);
		}
		index++;
	}
	fclose(filePointer);
	*totalcount = index;

	return 1;
}

//
// FUNCTION : displayLeastFareDetails
// DESCRIPTION : Itterates through all of the flights, compares their values
//				 and prints the flight with the lowest fairs.
// PARAMETERS : struct flightData* flightArray : pointer to the structure with flight information
//              int numberOfFlights : a number of how many flights where found in the files
// RETURNS : int 0: In case of successfull run of the function
//
int displayLeastFareDetails(struct flightData* flightArray, int numberOfFlights) {

	/*The loop takes flight information one-by-one and then compares it it all
	other flights information. Then it displays the flight if there was
	no similar flight. Or it displays the flight with the least price
	if there were 2 same flight.*/
	for (int i = 0; i < numberOfFlights; i++) {
		int currentPrice = flightArray[i].price;
		int isLowestFare = 1;

		for (int j = 0; j < numberOfFlights; j++) {
			if (i == j) {
				continue;
			}
			if (strcmp(flightArray[i].from, flightArray[j].from) == 0 &&
				strcmp(flightArray[i].destination, flightArray[j].destination) == 0) {
				/*if there is another exact flight with lower cost it will set flag to 0*/
				if (flightArray[j].price < currentPrice) {
					isLowestFare = 0;
					break;
				}
			}
		}
		if (isLowestFare) {
			removeExtension(flightArray[i].fileNameStorage);
			if ((flightArray[i].price != 0) && (strlen(flightArray[i].from) != 0) && strlen(flightArray[i].destination) != 0) {
				printf("%s : %s to %s, fare $%d \n", flightArray[i].fileNameStorage, flightArray[i].from, flightArray[i].destination, flightArray[i].price);
			}

		}
	}
	return 0;

}

//
// FUNCTION : parseLine
// DESCRIPTION : This function checks if the flight infromation is correctly written.
//				 It stores the values of the flight inside the struct if they are
//				 correctly written. If not - returns a negative int value.
// PARAMETERS : char* sourceVaribale : pointer to the source variable inside the struct
//				char* destinVariable : pointer to the destination variable inside the struct
//				int* fareVariable : pointer to the price variable inside the struct
//				char* lineData : pointer to a variable where the whole line where stored
// RETURNS : int 1 : In case of successfull parsing the lines
//			 int -3 : If the line is empty
//			 int -2 : If the line is missing dash
//			 int -1 : If the line is missing comma
//
int parseLine(char* sourceVaribale, char* destinVariable, int* fareVariable, char* lineData) {

	if (strlen(lineData) == 0) {
		return -3;
	}

	/*this code check if there is a - and , in the proper places*/
	size_t dash = strcspn(lineData, "-");
	size_t comma = strcspn(lineData, ",");

	if (dash >= strlen(lineData)) {
		return -2;
	}
	else if (comma >= strlen(lineData) || comma <= dash + 2) {
		return -1;
	}

	/* copy the source from lineData to sourceVaribale.*/
	strncpy(sourceVaribale, lineData, dash);
	sourceVaribale[dash] = '\0';

	/*copy the destination (text between the dash and comma) from lineData to destinVariable.*/
	strncpy(destinVariable, lineData + dash + 2, comma - (dash + 2));
	destinVariable[comma - (dash + 2)] = '\0';

	/*this is used to convert string to int and skip comma and -*/
	*fareVariable = atoi(lineData + comma + 1);

	return 1;
}


//
// FUNCTION : removeExtension
// DESCRIPTION : Function to take off any extension from the filename
//				 for proper display of information
// PARAMETERS : char* filename: pointer to the element inside the array of struct
//								where the filaname is stored
// RETURNS : void
//
void removeExtension(char* filename) {

	/*finds the position of the .*/
	char* dot = strrchr(filename, '.');

	if (dot != NULL) {
		*dot = '\0';
	}

}