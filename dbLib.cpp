/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

 /* TODO: You can implement methods, functions that support your data structures here.
  * */
void LoadData(void* &data) {
	TDataset* pData = new TDataset;
#pragma region LoadLine
	TLine line;
	fstream FileIn;
	FileIn.open("lines.csv", ios::in);
	string temp;
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		getline(FileIn, temp, ',');
		line.line_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		line.city_id = atoi(temp.c_str());
		getline(FileIn, temp);
		pData->pLine.push_back(line);
	}
	FileIn.close();
#pragma endregion
#pragma region LoadCity
	TCity city;
	FileIn.open("cities.csv", ios::in);
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		getline(FileIn, temp, ',');
		city.city_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		city.city_name = temp;
		getline(FileIn, temp);
		pData->pCity.push_back(city);
	}
	FileIn.close();
#pragma endregion
#pragma region LoadStation
	TStation station;
	FileIn.open("station_lines.csv", ios::in);
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		getline(FileIn, temp, ',');
		getline(FileIn, temp, ',');
		station.station_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		station.line_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		station.city_id = atoi(temp.c_str());
		getline(FileIn, temp);
		pData->pStation.push_back(station);
	}
	FileIn.close();
#pragma endregion
#pragma region LoadStation_name
	TStation_name station_name;
	FileIn.open("stations.csv", ios::in);
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		int idOfStation;
		getline(FileIn, temp, ',');
		station_name.station_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		station_name.station_name = temp;
		getline(FileIn, temp);
		pData->pStation_name.push_back(station_name);
	}
	FileIn.close();
#pragma endregion

	


	data = pData;
	data = static_cast<TDataset*>(data);
}

void ReleaseData(void*& data) {
	delete data;
}
