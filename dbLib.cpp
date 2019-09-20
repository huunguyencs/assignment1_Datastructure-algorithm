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
#pragma region LoadStation_line
	TStation station;
	FileIn.open("station_lines.csv", ios::in);
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		getline(FileIn, temp, ',');
		getline(FileIn, temp, ',');
		station.station_id = atoi(temp.c_str());
		getline(FileIn, temp, ',');
		station.line_id = atoi(temp.c_str());
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
		getline(FileIn, temp, '(');
		getline(FileIn, temp, ')');
		station_name.point = creatPoint(temp);
		getline(FileIn, temp, ',');
		getline(FileIn, temp, ',');
		getline(FileIn, temp, ',');
		getline(FileIn, temp, ',');
		getline(FileIn, temp);
		station_name.city_id = atoi(temp.c_str());
		pData->pStation_name.push_back(station_name);
	}
	FileIn.close();
#pragma endregion
#pragma region LoadTrack
	TTrack track;
	FileIn.open("tracks.csv", ios::in);
	getline(FileIn, temp);
	while (!FileIn.eof()) {
		getline(FileIn, temp, ',');
		track.track_id = atoi(temp.c_str());
		getline(FileIn, temp, '(');
		getline(FileIn, temp, ')');
		pointInTrack(temp, track);
		getline(FileIn, temp);
		pData->pTrack.push_back(track);
	}
#pragma endregion

	


	data = pData;
	data = static_cast<TDataset*>(data);
}

void ReleaseData(void*& data) {
	delete data;
}
Point creatPoint(string p_string) {
	int len = p_string.length();
	Point point;
	int i = 0;
	string temp = "";
	while (p_string[i] != ' ' && p_string[i]!='\0') {
		temp += p_string[i];
		i++;
	}
	point.p1 = atof(temp.c_str());
	temp = "";
	for (int j = i+1; j < len; j++) {
		temp += p_string[j];
	}
	point.p2 = atof(temp.c_str());
	return point;
}
void pointInTrack(string point_array, TTrack& track) {
	string temp = "";
	int index = 0;
	int i = 0;
	Point point_temp;
	while (point_array[i] != '\0') {
		if (point_array[i] == ',' && temp!="") {
			point_temp = creatPoint(temp);
			track.point[index].p1 = point_temp.p1;
			track.point[index].p2 = point_temp.p2;			
			temp = "";
			index++;
		}
		else {
			temp += point_array[i];
		}
		i++;
	}
}

