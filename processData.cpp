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
void Process_ISL(TDataset* pData, void*& pOutput, int station_id, int line_id, int pos, int& N);
void Process_RSL(TDataset* pData, void*& pOutput, int station_id, int line_id, int& N);
void Process_IS(TDataset* pData, void*& pOutput, string decreption, int& N);
void Process_US(TDataset* pData, void*& pOutput, int station_id, string decreption, int& N);
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
	//Đếm số lượng đường
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
	//Liệt kê các nhà ga có trong thành phố
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
	//Liệt kê các đường trong thành phố
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
	//Liệt kê các nhà ga có trên đường
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
	//Tìm thành phố bằng tên
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
	//Liệt kê nhà ga trong nhà phố
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
	//Xóa nhà ga khỏi dataset
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
	//Tìm vị trí của nhà ga trong track
	if (pRequest[0] == 'S' && pRequest[1] == 'L' && pRequest[2] == 'P') {
		int i = 4;
		string temp = "";
		while (pRequest[i] != ' ') {
			temp += pRequest[i];
			i++;
		}
		int station_id = atoi(temp.c_str());
		temp = "";
		for (int j = i + 1; j < strlen(pRequest); j++) {
			temp += pRequest[j];
		}
		int track_id = atoi(temp.c_str());
		Process_SLP(data, pOutput, station_id, track_id, N);
		return;

	}
	//Loại bỏ nhà ga khỏi đường
	if (pRequest[0] == 'R' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		int i = 4;
		string temp = "";
		while (pRequest[i] != ' ') {
			temp += pRequest[i];
			i++;
		}
		int station_id = atoi(temp.c_str());
		temp = "";
		for (int j = i + 1; j < strlen(pRequest); j++) {
			temp += pRequest[j];
		}
		int line_id = atoi(temp.c_str());
		Process_RSL(data, pOutput, station_id, line_id, N);
		return;
	}
	//Chèn nhà ga vào tập dữ liệu
	if (pRequest[0] == 'I' && pRequest[1] == 'S' && pRequest[2] == ' ') {
		int i = 3;
		string decreption = "";
		while (pRequest[i] != '\0') {
			decreption += pRequest[i];
			i++;
		}
		Process_IS(data, pOutput, decreption, N);
		return;
	}
	//Chèn nhà ga vào đường
	if (pRequest[0] == 'I' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		int i = 4;
		string temp = "";
		while (pRequest[i] != ' ') {
			temp += pRequest[i];
			i++;
		}
		i++;
		int station_id = atoi(temp.c_str());
		temp = "";
		while (pRequest[i] != ' ') {
			temp += pRequest[i];
			i++;
		}
		i++;
		int line_id = atoi(temp.c_str());
		temp = "";
		while (pRequest[i] != '\0') {
			temp += pRequest[i];
			i++;
		}
		int pos = atoi(temp.c_str());
		Process_ISL(data, pOutput, station_id, line_id, pos, N);
		return;
	}
	//Cập nhật thông tin nhà ga
	if (pRequest[0] == 'U' && pRequest[1] == 'S') {
		int i = 3;
		string decreption = "";
		while (pRequest[i] != ' ') {
			decreption += pRequest[i];
			i++;
		}
		i++;
		int station_id = atoi(decreption.c_str());
		decreption = "";
		while (pRequest[i] != '\0') {
			decreption += pRequest[i];
			i++;
		}
		Process_US(data, pOutput, station_id, decreption, N);
		return;
	}
}

//Đếm số lượng đường 
void Process_CL(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* result = new int;
	//Dem so luong duong trong tap du lieu
	if (city_name == "") { 
		
		N = 1;
		int numOfLine = pData->pLine.getSize();
		result[0] = numOfLine;
		pOutput = result;
		return;
	}
	else { //Dem so luong duong voi ten thanh pho duoc dua
		int count = -1;
		int idOfCity = 0;
		int numOfCity = (int)pData->pCity.getSize();
		//Tim chi so thanh pho bang ten thanh pho
		for (int i = 0; i < numOfCity; i++) {
			if (pData->pCity[i].city_name == city_name) {
				idOfCity = pData->pCity[i].city_id;
				break;
			}
		}
		if (idOfCity == 0) { //Khong tim thay thanh pho
			N = 1;
			result[0] = count;
			pOutput = result;
			return;
		}
		else {
			count = 0;
			int numOfLine = (int)pData->pLine.getSize();
			for (int i = 0; i < numOfLine; i++) {
				if (pData->pLine[i].city_id == idOfCity) count++; //Dem so luong duong trong thanh pho
			}
			N = 1;
			result[0] = count;
			pOutput = result;
			return;
		}
	}
}
//Liệt kê các nhà ga có trong thành phố
void Process_LSC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* station_id = new int[1000]; 
	int idOfCity = 0;
	int numOfCity = (int)pData->pCity.getSize();
	//Tim chi so thanh pho bang ten duoc dua
	for (int i = 0; i < numOfCity; i++) {
		if (pData->pCity[i].city_name == city_name) {
			idOfCity = pData->pCity[i].city_id;
			break;
		}
	}
	int index = 0;
	int numOfStation = pData->pStation.getSize();
	//Kiem tra nha ga co thuoc thanh pho hay khong
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].city_id == idOfCity) {
			station_id[index] = pData->pStation[i].station_id;
			index++;
		}
	}
	pOutput = station_id;
	N = index - 1;
}
//Liệt kê các đường trong thành phố
void Process_LLC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* line_id = new int[1000];
	int idOfCity = 0;
	int numOfCity = (int)pData->pCity.getSize();
	//Tim chi so thanh pho bang ten
	for (int i = 0; i < numOfCity; i++) {
		if (pData->pCity[i].city_name == city_name) {
			idOfCity = pData->pCity[i].city_id;
			break;
		}
	}
	int index = 0;
	int numOfLine = pData->pLine.getSize();
	//Kiem tra xem duong co thuoc thanh pho hay khong
	for (int i = 0; i < numOfLine; i++) {
		if (pData->pLine[i].city_id == idOfCity) {
			line_id[index] = pData->pLine[i].line_id;
			index++;
		}
	}
	pOutput = line_id;
	N = index - 1;
}
//Liệt kê các nhà ga có trên đường
void Process_LSL(TDataset* pData, void*& pOutput, int line_id, int& N) {
	int* idOfStation = new int[1000];
	int index = 0;
	int numOfStation = pData->pStation.getSize();
	//Kiem tra nha ga co thuoc duong hay khong
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].line_id == line_id) {
			idOfStation[index] = pData->pStation[i].station_id;
			index++;
		}
	}
	pOutput = idOfStation;
	N = index - 1;
}
//Tìm thành phố bằng tên
void Process_FC(TDataset* pData, void*& pOutput, string city_name, int& N) {
	int* idOfCity = new int;
	idOfCity[0] = -1;
	int numOfCity = pData->pCity.getSize();
	//Kiem tra xem ten thanh pho co trung khong
	for (int i = 0; i < numOfCity; i++) {
		if (city_name == pData->pCity[i].city_name) {
			idOfCity[0] = pData->pCity[i].city_id;
			break;
		}
	}
	pOutput = idOfCity;
	N = 1;
}
//Tìm nhà ga bằng tên
void Process_FS(TDataset* pData, void*& pOutput, string station_name, int& N) {
	int* station_id = new int;
	station_id[0] = -1;
	int idInStation = 0;
	int numOfStation_name = pData->pStation_name.getSize();
	//Tim chi so station thong qua ten nha ga
	for (int i = 0; i < numOfStation_name; i++) {
		if (station_name == pData->pStation_name[i].station_name) {
			idInStation = pData->pStation_name[i].id;
			break;
		}
	}
	//Kiem tra xem chi so station co trung khong
	int numOfStation = pData->pStation.getSize();
	for (int i = 0; i < numOfStation; i++) {
		if (idInStation == pData->pStation[i].id) {
			station_id[0] = pData->pStation[i].station_id;
			break;
		}
	}
	pOutput = station_id;
	N = 1;
}
//Tìm vị trí của nhà ga trong track
void Process_SLP(TDataset* pData, void*& pOutput, int station_id, int track_id, int& N) {
	int* result = new int;
	result[0] = -1;
	int numOfTrack = pData->pTrack.getSize();
	int indexOfTrack = 0;
	//Tim chi so track thong qua track_id
	for (int i = 0; i < numOfTrack; i++) {
		if (track_id == pData->pTrack[i].track_id) {
			indexOfTrack = i;
			break;
		}
	}
	int idInStation = 0;
	int indexOfStation = 0;
	int numOfStation = pData->pStation.getSize();
	//Tim chi so cua station thong qua station_id
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].station_id == station_id) {
			idInStation = pData->pStation[i].id;
			break;
		}
	}
	int numOfStation_name = pData->pStation_name.getSize();
	//Kiem tra xem chi so cua station co trung khong
	for (int i = 0; i < numOfStation_name; i++) {
		if (pData->pStation_name[i].id = idInStation) {
			indexOfStation = i;
			break;
		}
	}
	int i = 0;
	//Tim chi so cua station trong 1 track thong qua point
	while(pData->pTrack[indexOfTrack].point[i].p1!=0){
		if (abs(pData->pTrack[indexOfTrack].point[i].p1 - pData->pStation_name[indexOfStation].point.p1)<0.00001 && abs(pData->pTrack[indexOfTrack].point[i].p2 - pData->pStation_name[indexOfStation].point.p2)<0.00001) {
			result[0] = i;
			break;
		}
		i++;
	}
	pOutput = result;
	N = 1;
}
//Xóa nhà ga khỏi dataset
void Process_RS(TDataset* pData, void*& pOutput, int station_id, int& N) {
	int* result = new int;
	try {
		int idInStation = -1;
		bool isSuccess1 = false;
		bool isSuccess2 = false;
		int numOfStation = pData->pStation.getSize();
		//Xoa nha ga khoi station
		for (int i = 0; i < numOfStation; i++) {
			if (pData->pStation[i].station_id == station_id) {
				idInStation = pData->pStation[i].id; //Lay chi so cua station de xoa nha ga trong station_name
				if (i == 0) pData->pStation.removeHead();
				else {
					if (i == numOfStation - 1) if (pData->pStation.removeLast() == -1) { result[0] = -1; break; }
					else if (pData->pStation.remove(i) == -1) { result[0] = -1; break; }
				}
				isSuccess1 = true;
				break;
			}
		}
		int numOfStation_name = pData->pStation_name.getSize();
		//Xoa nha ga khoi station_name
		for (int i = 0; i < numOfStation_name; i++) {
			if (pData->pStation_name[i].id == idInStation) {
				if (i == 0) pData->pStation_name.removeHead();
				else {
					if (i == numOfStation_name - 1) if (pData->pStation_name.removeLast()==-1) { result[0] = -1; break; }
					else if (pData->pStation_name.remove(i) == -1) { result[0] = -1; break; }
				}
				isSuccess2 = true;
				break;
			}
		}
		if (isSuccess1 && isSuccess2 && idInStation!=-1) result[0] = 0;
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
//Loại bỏ nhà ga khỏi đường
void Process_RSL(TDataset* pData, void*& pOutput, int station_id, int line_id, int& N) {
	int* result = new int;
	try
	{
		bool isSuccess = false;
		int numOfStation = pData->pStation.getSize();
		//Kiem tra xem nha ga co thuoc duong khong
		for (int i = 0; i < numOfStation; i++) {
			if (pData->pStation[i].line_id == line_id && pData->pStation[i].station_id==station_id) {
				if (i == 0) pData->pStation.removeHead();
				else {
					if (i == numOfStation - 1) pData->pStation.removeLast();
					else pData->pStation.remove(i);
				}
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
//Chèn nhà ga vào dataset
void Process_IS(TDataset* pData, void*& pOutput, string decreption, int& N) {
	int* result = new int;
	TStation_name station_insert;
	int numOfStation_name = pData->pStation_name.getSize();
	int idMax = pData->pStation_name[0].id;
	for (int i = 0; i < numOfStation_name; i++) {
		if (idMax < pData->pStation_name[i].id) {
			idMax = pData->pStation_name[i].id;
		}
	}

	station_insert.id = idMax +1;
	string temp = "";
	int i = 0;
	//Lay ten cua station
	if (decreption[0] == '\"') {
		i = 1;
		while (decreption[i] != '\"') {
			temp += decreption[i];
			i++;
		}
		station_insert.station_name = temp;
	}
	else {
		while (decreption[i] != ',') {
			temp += decreption[i];
			i++;
		}
		station_insert.station_name = temp;
	}

	temp = "";
	while (decreption[i] != '(') {
		i++;
	}
	i++;
	while (decreption[i] != ')') {
		temp += decreption[i];
		i++;
	}
	Point point = creatPoint(temp);
	station_insert.point.p1 = point.p1;
	station_insert.point.p2 = point.p2;
	pData->pStation_name.push_back(station_insert);
	pData->pStation_name[pData->pStation_name.getSize() - 1].id = station_insert.id;
	pData->pStation_name[pData->pStation_name.getSize() - 1].point = station_insert.point;
	pData->pStation_name[pData->pStation_name.getSize() - 1].station_name = station_insert.station_name;
	//Kiem station co id trung voi insert.id
	for (int j = 0; j < pData->pStation.getSize(); j++) {
		if (station_insert.id == pData->pStation[j].id) {
			result[0] = pData->pStation[j].station_id;
			break;
		}
	}
	pOutput = result;
	N = 1;
}
//Chèn nhà ga vào đường
void Process_ISL(TDataset* pData, void*& pOutput, int station_id, int line_id, int pos, int& N) {
	int* result = new int;
	TStation station;
	station.station_id = station_id;
	station.line_id = line_id;
	int index = 0;
	int indexInsert = 0;
	int numOfStation = pData->pStation.getSize();
	//Kiem tra xem da ton tai nha ga tren duong chua
	for (int i = 0; i < numOfStation; i++) {
		if (pData->pStation[i].line_id == line_id) {
			if (pData->pStation[i].station_id == station_id) {
				result[0] = -1;
				pOutput = result;
				N = 1;
				return;
			}
		}
	}
	//Tim vi tri de chen nha ga vao
	for (int i = 0; i < numOfStation; i++) {
		if (index == pos) {
			indexInsert = i;
			break;
		}
		if (pData->pStation[i].line_id == line_id) index++;
	}
	
	if (pos == 0) {
		pData->pStation.insertHead(station); //Chen vao dau
		result[0] = 0;
		pOutput = result;
		N = 1;
	}
	else {
		if (index == 0 && indexInsert == 0) { //Neu khong tim duoc vi tri
			result[0] = -1;
			pOutput = result;
			N = 1;
		}
		else {
			pData->pStation.insert(indexInsert, station);
			result[0] = 0;
			pOutput = result;
			N = 1;
		}
	}
}
//Cập nhật thông tin của nhà ga
void Process_US(TDataset* pData, void*& pOutput, int station_id, string decreption, int& N) {
	int* result = new int;
	int numOfStation = pData->pStation.getSize();
	int index = 0;
	int idOfStation = -1;
	bool isFound = false;
	//Tim id cua station co station_id
	for (int i = 0; i < numOfStation; i++) {
		if (station_id == pData->pStation[i].station_id) {
			idOfStation = pData->pStation[i].id;
			isFound = true;
			break;
		}
	}
	int numOfStation_name = pData->pStation_name.getSize();
	for (int i = 0; i < numOfStation_name; i++) {
		if (pData->pStation_name[i].id = idOfStation) {
			index = i;
			break;
		}
	}
	if (!isFound) {
		result[0] = -1;
		pOutput = result;
		N = 1;
	}
	else {

		string name_station = "";
		int i = 0;
		while (decreption[i] != ',') {
			name_station += decreption[i];
			i++;
		}
		pData->pStation_name[index].station_name = name_station;
		while (decreption[i] != '(') {
			i++;
		}
		i++;
		string point = "";
		while (decreption[i] != ')') {
			point += decreption[i];
			i++;
		}
		Point p;
		p = creatPoint(point);
		pData->pStation_name[index].point.p1 = p.p1;
		pData->pStation_name[index].point.p2 = p.p2;
		result[0] = 0;
		pOutput = result;
		N = 1;
	}
}
