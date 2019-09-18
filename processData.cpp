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

