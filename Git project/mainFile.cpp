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