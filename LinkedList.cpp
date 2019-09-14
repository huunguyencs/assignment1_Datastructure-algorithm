#include <iostream>
using namespace std;
template <class T>
struct L1Item {
	T data;
	L1Item* link;
	L1Item(): data(0), link(NULL) {}
	L1Item(T& a) {
		data = a;
		link = NULL;
	}
};
template <class T>
class L1List{
	L1Item<T>* head;
	size_t _size;
public:
	L1List() : head(NULL), _size(0) {}
	~L1List() {};

	void    clean();
	bool    isEmpty() {
		return head == NULL;
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
int L1List<T>::push_back(T &a) {
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (head == NULL) {
			temp->link = head;
			head = temp;
			_size++;
		}
		else {
			L1Item<T>* p = new L1Item<T>;
			p = head;
			while (p->link != NULL) {
				p = p->link;
			}
			p->link = temp;
			_size++;
		}
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

template <class T>
int L1List<T>::insert(int i,T& a) {
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (i == 0) {
			if (head != NULL) temp->link = head;
			head = temp;
			_size++;
			return 0;
		}
		else {
			L1Item<T>* p = head;
			int index = 0;
			while (index + 1 < _size && index + 1 != i) {
				p = p->link;
				index++;
			}
			if (index + 1 == i) {
				temp->link = p->link;
				p->link = temp;
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
int L1List<T>::removeHead() {
	try {
		L1Item<T>* p = head;
		head = head->link;
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
		L1Item<T>* p = head;
		while (p->link->link != NULL) {
			p = p->link;
		}
		p->link = NULL;
		delete p->link;
		_size--;
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

template <class T>
int L1List<T>::insertHead(T& a) {
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (head != NULL)
			temp->link = head;
		head = temp;
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

template <class T>
int L1List<T>::remove(int i) {
	L1Item<T>* temp = head;
	int index = 0;
	while (index + 1 != i && index < _size - 1) {
		index++;
		temp = temp->link;
	}
	if (index == i - 1) {
		L1Item<T>* p = temp->link;
		temp->link = temp->link->link;
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
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T>* p = head;
	int index = 0;
	while (index < _size && p->data != a) {
		p = p->link;
		index++;
	}
	if (_size == index && p->data != a) return false;
	else {
		idx = index;
		return true;
	}
}

template <class T>
T& L1List<T>::operator[](int i) {
	L1Item<T>* p = head;
	int index = 0;
	while (index < _size && i != index) {
		p = p->link;
		index++;
	}
	return p->data;
}

int main() {
	L1List<int> list;
	int x = 5, y = 6, z = 7;
	list.push_back(x);
	list.push_back(y);
	list.push_back(z);
	list.removeLast();
	return 0;
}
