/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

 /* TODO: Please design your data structure carefully so that you can work with the given dataset
  *       in this assignment. The below structures are just some suggestions.
  */
struct Point {
	double p1;
	double p2;
	Point() :p1(0), p2(0) {}
};
struct TCity {
	// The structure to store city information
	int city_id;
	string city_name;
	TCity() : city_id(0), city_name("") {}
};

struct TLine:TCity {
	// The structure to store line information
	int line_id;
	TLine() : line_id(0) {}
};

struct TStation:TLine {
	int station_id;
	Point point;
	TStation() : station_id(0) {}
};
struct TStation_name {
	int station_id;
	string station_name;
	TStation_name(): station_id(0), station_name("") {}
};

struct TTrack:TStation {
	// The structure to store track information
	int track_id;
	Point* point = new Point;
	TTrack() :track_id(0) {}
};

class TDataset {
	// This class can be a container that help you manage your tables
public:
	L1List<TCity> pCity;
	L1List<TLine> pLine;
	L1List<TStation> pStation;
	L1List<TStation_name> pStation_name;
	L1List<TTrack> pTrack;
	TDataset() {}
	~TDataset() {}
};

// Please add more or modify as needed

void LoadData(void*&);
void ReleaseData(void*&);

#endif //DSA191_A1_DBLIB_H
#pragma once
