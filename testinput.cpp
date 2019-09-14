#include <iostream>
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
	~L1List(){}

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
	// TODO: Your code goes here
	try {
		L1Item<T> temp(a);
		if (_pHead == NULL) {
			_pHead = &(temp);
			_size++;
		}
		else {
			L1Item<T>* p;
			p = _pHead;
			while (p != NULL) {
				p = p->pNext;
			}
			p = &temp;
			_size++;
		}
	}
	catch (exception) {
		return -1;
	}
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T& a) {
	// TODO: Your code goes here
	try {
		L1Item<T> temp(a);
		if (_pHead == NULL) {
			_pHead = &temp;
			_size++;
		}
		else {
			temp.pNext = _pHead;
			_pHead = &(temp);
			_size++;
		}
	}
	catch (exception) {
		return -1;
	}
	return 0;
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

struct TCity {
	// The structure to store city information
	int city_id;
	string city_name;
};

struct TLine:TCity {
	// The structure to store line information
	int line_id;
};

struct TStation:TCity {
	int station_id;
};

struct TTrack:TLine {
	// The structure to store track information
	int track_id;
};

class TDataset {
	// This class can be a container that help you manage your tables
public:
	L1List<TLine> pLine;
	L1List<TStation> pStation;
	L1List<TTrack> pTrack ;
	TDataset() {}
	~TDataset() {}

};
int main(){
	TLine a;
	a.city_id=5;
	a.city_name="Ho Chi Minh";
	a.line_id=1;
	TDataset data;
	data.pLine.push_back(a);
	cout<<data.pLine[0].city_name;
	return 0;
}
