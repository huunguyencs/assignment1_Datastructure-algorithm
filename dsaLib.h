/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

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

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T& a) {
	// TODO: Your code goes here
	try {
		L1Item<T>* temp = new L1Item<T>(a);
		if (_pHead == NULL) {
			temp->pNext = _pHead;
			_pHead = temp;
		}
		else {
			L1Item<T>* p = new L1Item<T>;
			p = _pHead;
			while (p->pNext != NULL) {
				p = p->pNext;
			}
			p->pNext = temp;
			_size = _size + 1;
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
		return 0;
	}
	catch (exception) {
		return -1;
	}
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
	// TODO: Your code goes here
	try {
		if (_pHead == NULL) return -1;
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

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	// TODO: Your code goes here
	try {
		if (_pHead == NULL) return -1;
		L1Item<T>* p = _pHead;
		while (p->pNext->pNext != NULL) {
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

template <class T>
bool L1List<T>::find(T& a, int& idx) {
	bool isFinded = false;
	L1Item<T> temp;
	int index = 0;
	temp.pNext = _pHead;
	while (temp.pNext != NULL) {
		if (temp.data == a) {
			idx = index;
			isFinded = true;
			break;
		}
		else {
			index++;
			temp = *(temp.pNext);
		}
	}
	return isFinded;
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
int L1List<T>::remove(int i) {
	try {
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
#endif //DSA191_A1_DSALIB_H
#pragma once
