/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dbLib.h"
 /* TODO: You can implement methods, functions that support your data structures here.
  * */
using namespace std;
void Process_CL(TDataset* pData, void*& pOutput, string city_name, int& N);
void Process_LSC(TDataset* pData, void*& pOutput, string city_name, int& N);
void Process_LLC(TDataset* pData, void*& pOutput, string city_name, int& N);
void Process_LSL(TDataset* pData, void*& pOutput, int line_id, int& N);
void Process_FC(TDataset* pData, void*& pOutput, string city_name, int& N);
void Process_FS(TDataset* pData, void*& pOutput, string station_name, int& N);
void Process_SLP(TDataset* pData, void*& pOutput, int station_id, int track_id, int& N);
void Process_RS(TDataset* pData, void*& pOutput, int station_id, int& N);
void Process_ISL(TDataset* pData, void*& pOutput, int station_id, int line_id, int index, int& N);
void Process_RSL(TDataset* pData, void*& pOutput, int station_id, int line_id, int& N);
void Initialization() {
	// If you use global variables, please initialize them explicitly in this function.

}

void Finalization() {
	// Release your data before exiting
	
}

void ProcessRequest(const char* pRequest, void* pData, void*& pOutput, int& N) {
	// TODO: Implement this function for processing a request
	// NOTE: You can add other functions to support this main process.
	//       pData is a pointer to a data structure that manages the dataset
	//       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
	//       N is the size of output, must be a non-negative number
	TDataset* data = (TDataset*)pData;
	//Count line
	if (pRequest[0] == 'C' && pRequest[1] == 'L') {
		int i = 2;
		string city_name = "";
		while (pRequest[i] != '\0') {
			if (pRequest[i] == ' ') i++;
			else {
				city_name += pRequest[i];
				i++;
			}
		}
		Process_CL(data, pOutput, city_name, N);
		return;
	}
	//List the stations in the city
	if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'C') {
		int i = 4;
		string city_name = "";
		while (pRequest[i] != '\0') {
			city_name += pRequest[i];
			i++;
		}
		Process_LSC(data, pOutput, city_name, N);
		return;
	}
	//List the lines in the city
	if (pRequest[0] == 'L' && pRequest[1] == 'L' && pRequest[2] == 'C') {
		int i = 4;
		string city_name = "";
		while (pRequest[i] != '\0') {
			city_name += pRequest[i];
			i++;
		}
		Process_LLC(data, pOutput, city_name, N);
		return;
	}
	//List the stations on line
	if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		int i = 4;
		string city_id_string = "";
		while (pRequest[i] != '\0'){
			city_id_string += pRequest[i];
			i++;
		}
		int city_id_int = atoi(city_id_string.c_str());
		Process_LSL(data, pOutput, city_id_int, N);
		return;
	}
	//Find the city
	if (pRequest[0] == 'F' && pRequest[1] == 'C') {
		int i = 3;
		string city_name = "";
		while (pRequest[i] != '\0') {
			city_name += pRequest[i];
			i++;
		}
		Process_FC(data, pOutput, city_name, N);
		return;
	}
	//Find the station
	if (pRequest[0] == 'F' && pRequest[1] == 'S') {
		int i = 3;
		string station_name = "";
		while (pRequest[i] != '\0') {
			station_name += pRequest[i];
			i++;
		}
		Process_FS(data, pOutput, station_name, N);
		return;
	}
	//Remove the station
	if (pRequest[0] == 'R' && pRequest[1] == 'S' && pRequest[2]==' ') {
		int i = 3;
		string station_id_string = "";
		while (pRequest[i] != '\0') {
			station_id_string += pRequest[i];
			i++;
		}
		int station_id_int = atoi(station_id_string.c_str());
		Process_RS(data, pOutput, station_id_int, N);
	}

}

void Process_CL(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* result = new int;
	if (city_name == "") {
		N = 1;
		int numOfLine = pData->pLine.getSize();
		pOutput = new int;
		result[0] = numOfLine;
		pOutput = result;
		return;
	}
	else {
		int count = -1;
		int idOfCity = 0;
		int numOfCity = (int)pData->pCity.getSize();
		for (int i = 0; i < numOfCity; i++) {
			if (pData->pCity[i].city_name == city_name) {
				idOfCity = pData->pCity[i].city_id;
				break;
			}
		}
		if (idOfCity == 0) {
			N = 1;
			result[0] = count;
			pOutput = result;
			return;
		}
		else {
			count = 0;
			int numOfLine = (int)pData->pLine.getSize();
			for (int i = 0; i < numOfLine; i++) {
				if (pData->pLine[i].city_id == idOfCity) count++;
			}
			N = 1;
			result[0] = count;
			pOutput = result;
			return;
		}
	}
}
void Process_LSC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* station_id = new int[1000];
	int idOfCity = 0;
	int numOfCity = (int)pData->pCity.getSize();
	for (int i = 0; i < numOfCity; i++) {
		if (pData->pCity[i].city_name == city_name) {
			idOfCity = pData->pCity[i].city_id;
			break;
		}
	}
	int index = 0;
	int numOfStation = pData->pStation.getSize();
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].city_id == idOfCity) {
			station_id[index] = pData->pStation[i].station_id;
			index++;
		}
	}
	pOutput = station_id;
	N = index - 1;
}
void Process_LLC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* line_id = new int[1000];
	int idOfCity = 0;
	int numOfCity = (int)pData->pCity.getSize();
	for (int i = 0; i < numOfCity; i++) {
		if (pData->pCity[i].city_name == city_name) {
			idOfCity = pData->pCity[i].city_id;
			break;
		}
	}
	int index = 0;
	int numOfLine = pData->pLine.getSize();
	for (int i = 0; i < numOfLine; i++) {
		if (pData->pLine[i].city_id == idOfCity) {
			line_id[index] = pData->pLine[i].line_id;
			index++;
		}
	}
	pOutput = line_id;
	N = index - 1;
}
void Process_LSL(TDataset* pData, void*& pOutput, int line_id, int& N) {
	int* idOfStation = new int[1000];
	int index = 0;
	int numOfStation = pData->pStation.getSize();
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].line_id == line_id) {
			idOfStation[index] = pData->pStation[i].station_id;
			index++;
		}
	}
	pOutput = idOfStation;
	N = index - 1;
}
void Process_FC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* idOfCity = new int;
	idOfCity[0] = -1;
	int numOfCity = pData->pCity.getSize();
	for (int i = 0; i < numOfCity; i++) {
		if (city_name == pData->pCity[i].city_name) {
			idOfCity[0] = pData->pCity[i].city_id;
			break;
		}
	}
	pOutput = idOfCity;
	N = 1;
}
void Process_FS(TDataset* pData, void*& pOutput, string station_name, int& N) {
	int* station_id = new int;
	station_id[0] = -1;
	int numOfStation_name = pData->pStation_name.getSize();
	for (int i = 0; i < numOfStation_name; i++) {
		if (station_name == pData->pStation_name[i].station_name) {
			station_id[0] = pData->pStation_name[i].station_id;
			break;
		}
	}
	pOutput = station_id;
	N = 1;
}
void Process_SLP(TDataset* pData, void*& pOutput, int station_id, int track_id, int& N) {

}
void Process_RS(TDataset* pData, void*& pOutput, int station_id, int& N) {
	int* result = new int;
	try {
		bool isSuccess = false;
		int numOfStation = pData->pStation.getSize();
		for (int i = 0; i < numOfStation; i++) {
			if (pData->pStation[i].station_id == station_id) {
				pData->pStation.remove(i);
				break;
			}
		}
		int numOfStation_name = pData->pStation_name.getSize();
		for (int i = 0; i < numOfStation_name; i++) {
			if (pData->pStation_name[i].station_id == station_id) {
				pData->pStation_name.remove(i);
				isSuccess = true;
				break;
			}
		}
		if (isSuccess) result[0] = 0;
		else result[0] = -1;
		pOutput = result;
		N = 1;
	}
	catch (exception) {
		result[0] = -1;
		pOutput = result;
		N = 1;
	}


}
void Process_RSL(TDataset* pData, void*& pOutput, int station_id, int line_id, int& N) {
	int* result = new int;
	try
	{
		bool isSuccess = false;
		int numOfStation = pData->pStation.getSize();
		for (int i = 0; i < numOfStation; i++) {
			if (pData->pStation[i].line_id == line_id) {
				pData->pStation.remove(i);
				isSuccess = true;
				break;
			}
		}
		if (isSuccess) result[0] = 0;
		else result[0] = -1;
		pOutput = result;
		N = 1;
	}
	catch (exception)
	{
		result[0] = -1;
		pOutput = result;
		N = 1;
	}
}
