#include <iostream>
#include <cstdlib>
#include <string.h>

#include "ExtHashTable.h"


ExtHashTable::ExtHashTable(double upper_bound_ratio, double lower_bound_ratio, int size) {
	
	this->upper_bound_ratio = upper_bound_ratio;
	this->lower_bound_ratio = lower_bound_ratio;
	this->size = 0;
}
  
ExtHashTable::ExtHashTable(const ExtHashTable &t) : HashTable(t) {
	
	this->upper_bound_ratio = t.upper_bound_ratio;
	this->lower_bound_ratio = t.lower_bound_ratio;
	this->size = t.size;
}

void ExtHashTable::rehash() {
	
	double ratio = ((double)size)/((double)capacity);
	int old_capacity = capacity;
	int old_size = size;
	
	if(ratio > upper_bound_ratio){
		capacity = capacity*2;
		table = new (nothrow)string[capacity];
		size = 0;
	}
	
	if (ratio < lower_bound_ratio ) {
		capacity = capacity/2;	
		table = new (nothrow)string[capacity];
		size = 0;
	}
	
	if (old_capacity != capacity) 
		cout << "--> Size: " << old_size << ", New capacity: " << capacity << endl;
}

bool ExtHashTable::add(const string &str) {
	
	int old_capacity = capacity;
	string temp[old_capacity];
	for (int i=0; i<old_capacity; i++) {
		temp[i] = table[i];
	}
	
	rehash();
	
	if (old_capacity == capacity) {
		return (HashTable::add(str));
	}
	else {
		for (int i=0; i<old_capacity;  i++) {
			if (!temp[i].empty()); {
				HashTable::add(temp[i]);
			}
		}
		return (HashTable::add(str));
	}
}

bool ExtHashTable::add(const char *s) {
	
	int old_capacity = capacity;
	string temp[old_capacity];
	for (int i=0; i<old_capacity; i++) {
		temp[i] = table[i];
	}
	
	rehash();
	
	if (old_capacity == capacity) {
		return (HashTable::add(s));
	}
	else {
		for (int i=0; i<old_capacity;  i++) {
			if (!temp[i].empty()); {
				HashTable::add(temp[i]);
			}
		}
		return (HashTable::add(s));
	}
}

bool ExtHashTable::remove(const string &str) {

	int old_capacity = capacity;
	string temp[old_capacity];
	for (int i=0; i<old_capacity; i++) {
		temp[i] = table[i];
	}
	
	rehash();
	
	if (old_capacity == capacity) {
		return (HashTable::remove(str));
	}
	else {
		for (int i=0; i<old_capacity;  i++) {
			if (!temp[i].empty() && temp[i]!="##tomb##")
				HashTable::add(temp[i]);
		}
		return (HashTable::remove(str));
	}
}

bool ExtHashTable::remove(const char *s) {

	int old_capacity = capacity;
	string temp[old_capacity];
	for (int i=0; i<old_capacity; i++) {
		temp[i] = table[i];
	}
	
	rehash();
	
	if (old_capacity == capacity) {
		
		return (HashTable::remove(s));
	}
	else {
		for (int i=0; i<old_capacity;  i++) {
			if (!temp[i].empty() && temp[i]!="##tomb##")
				HashTable::add(temp[i]);
		}
		return (HashTable::remove(s));
	}
}

ExtHashTable ExtHashTable::operator+(const string &str) const {
	
	ExtHashTable ext_ht = ExtHashTable(*this);
		
	if (!contains(str)) ext_ht.add(str);
	
	return(ext_ht);	
}

ExtHashTable ExtHashTable::operator+(const char* s) const {
	
	ExtHashTable ext_ht = ExtHashTable(*this);
		
	if (!contains(s)) ext_ht.add(s);
	
	return(ext_ht);
}

ExtHashTable ExtHashTable::operator-(const string &str) const {
	
	ExtHashTable ext_ht = ExtHashTable(*this);
		
	if (contains(str)){
		ext_ht.remove(str);
	}
	
	return(ext_ht);
}

ExtHashTable ExtHashTable::operator-(const char *s) const {
	
	ExtHashTable ext_ht = ExtHashTable(*this);
		
	if (contains(s)){
		ext_ht.remove(s);
	}
	
	return(ext_ht);
}

bool ExtHashTable::operator += (const string &str) { 
	
	return (add(str));
}

bool ExtHashTable::operator += (const char* s) { 
	
	return (add(s));
}

bool ExtHashTable::operator -= (const string &str) {
	
	return (remove(str));
}
bool ExtHashTable::operator -= (const char *s) {
 
	return (remove(s));
}

ExtHashTable ExtHashTable::operator+(const ExtHashTable &table) const {
	
	ExtHashTable ext_ht;
	
	for (int i=0; i<capacity; i++) {
		ext_ht.add(this->table[i]);
	}
	for (int i=0; i<table.capacity; i++) {
		ext_ht.add(table.table[i]);
	} 
	
	return(ext_ht);
}

ExtHashTable & ExtHashTable::operator+=(const ExtHashTable &table) {
	
	for (int i=0; i<table.capacity; i++) {
		this->add(table.table[i]);
	}
	
	return (*this);
}

ExtHashTable & ExtHashTable::operator=(const ExtHashTable &t) {
	
	this->capacity = t.capacity;
	this->size = t.size;
	this->table = t.table;
	this->upper_bound_ratio = t.upper_bound_ratio;
	this->lower_bound_ratio = t.lower_bound_ratio;
	return (*this);
}
