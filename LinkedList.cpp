#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include <stdlib.h>

using namespace std;
template <class T>
struct L1Item {
	T data;
	L1Item<T>* pNext;
	L1Item() : pNext(NULL) {}
	L1Item(T& a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
	L1Item<T>* _pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() {}

	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T& at(int i);// give the reference to the element i-th in the list
	T& operator[](int i);// give the reference to the element i-th in the list

	bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
	int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

	int     push_back(T& a);// insert to the end of the list
	int     insertHead(T& a);// insert to the beginning of the list

	int     removeHead();// remove the beginning element of the list
	int     removeLast();// remove the last element of the list

	void    reverse();

	void    traverse(void (*op)(T&)) {
		// TODO: Your code goes here

	}
	void    traverse(void (*op)(T&, void*), void* pParam) {
		// TODO: Your code goes here
	}
};
template <class T>
int L1List<T>::push_back(T& a) {
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (_pHead == NULL) {
			temp->pNext = _pHead;
			_pHead = temp;
			_size++;
		}
		else {
			L1Item<T>* p = new L1Item<T>;
			p = _pHead;
			while (p->pNext != NULL) {
				p = p->pNext;
			}
			p->pNext = temp;
			_size++;
		}
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T& a) {
	// TODO: Your code goes here
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (_pHead == NULL) {
			_pHead = temp;
			_size++;
		}
		else {
			temp->pNext = _pHead;
			_pHead = temp;
			_size++;
		}
	}
	catch (exception) {
		return -1;
	}
	return 0;
}

template <class T>
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T>* p = _pHead;
	int index = 0;
	while (index < _size && p->data != a) {
		p = p->pNext;
		index++;
	}
	if (_size == index && p->data != a) return false;
	else {
		idx = index;
		return true;
	}
}

template <class T>
int L1List<T>::insert(int i, T& a) {
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (i == 0) {
			if (_pHead != NULL) temp->pNext = _pHead;
			_pHead = temp;
			_size++;
			return 0;
		}
		else {
			L1Item<T>* p = _pHead;
			int index = 0;
			while (index + 1 < _size && index + 1 != i) {
				p = p->pNext;
				index++;
			}
			if (index + 1 == i) {
				temp->pNext = p->pNext;
				p->pNext = temp;
				_size++;
				return 0;
			}
			else return -1;
		}
	}
	catch (exception) {
		return -1;
	}
}

template <class T>
T& L1List<T>::operator[](int i) {
	L1Item<T>* p = _pHead;
	int index = 0;
	while (index < _size && i != index) {
		p = p->pNext;
		index++;
	}
	return p->data;
}

template <class T>
int L1List<T>::remove(int i) {
	L1Item<T>* temp = _pHead;
	int index = 0;
	while (index + 1 != i && index < _size - 1) {
		index++;
		temp = temp->pNext;
	}
	if (index == i - 1) {
		L1Item<T>* p = temp->pNext;
		temp->pNext = temp->pNext->pNext;
		p = NULL;
		delete p;
		_size--;
		return 0;
	}
	else {
		return -1;
	}
}

template <class T>
int L1List<T>::removeHead() {
	try {
		L1Item<T>* p = _pHead;
		_pHead = _pHead->pNext;
		delete p;
		_size--;
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

template <class T>
int L1List<T>::removeLast() {
	try {
		L1Item<T>* p = _pHead;
		while (p->link->link != NULL) {
			p = p->pNext;
		}
		p->pNext = NULL;
		delete p->pNext;
		_size--;
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

struct TCity {
	// The structure to store city information
	int city_id;
	string city_name;
	TCity() : city_id(0), city_name("") {}
};

struct TLine :TCity {
	// The structure to store line information
	int line_id;
	TLine() : line_id(0) {}
};

struct TStation :TCity {
	int station_id;
	TStation() : station_id(0) {}
};

struct TTrack :TLine {
	// The structure to store track information
	int track_id;
};

class TDataset {
	// This class can be a container that help you manage your tables
public:
	L1List<TLine> pLine;
	L1List<TStation> pStation;
	L1List<TTrack> pTrack;
	TDataset() {}
	~TDataset() {}

};
void loadLine(TDataset*& pData) {
	TDataset* data = new TDataset;
	cout << "loadline run" << endl;
	int i = 0;
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
		data->pLine.push_back(line);
		i++;
	}
	pData = data;
	FileIn.close();
}
void loadData(void*& data) {
	cout << "LoadData run" << endl;
	TDataset* pData = new TDataset;
	loadLine(pData);
	data = pData;
}

int main() {
	void* pData = NULL;
	loadData(pData);
	return 0;
}
