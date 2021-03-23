#include "HashTable.h"
#include "HashTableException.h"
#include <stdio.h>
#include <new>
#include <string.h>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int HashTable::getHashCode(const char *str) {
	int code = 0;
	while(*str != 0) {
		code += *(str++);
	}
	return code;
}

int HashTable::getSize() const { return (size); }
int HashTable::getCapacity() const {return (capacity); }

bool HashTable::isEmpty(int pos) const { 
	if (pos < capacity) {
		if(table[pos].empty()) {
			return true;
		}
		return false;
	}
	return false;
}

bool HashTable::isTomb(int pos) const { 
	if(pos<capacity){
		if(table[pos].compare("##tomb##")==0) {
			return true; 
		}
		return false;
	}
	return false;
}

bool HashTable::isAvailable(int pos) const {
	if (isEmpty(pos) == true || isTomb(pos) == true)
		return true;
		
	return false;

}

HashTable::HashTable(int capacity) {
	std::bad_alloc ex;
	this->capacity = capacity;
	size=0;
	table = new (nothrow)string[capacity];
	if (table == NULL || capacity < 0){
		throw ex;
	}
}

HashTable::HashTable(const HashTable &ht) {
	
	std::bad_alloc ex;
	capacity = ht.capacity;
	size = ht.size;
	table = new (nothrow)string[capacity];
	table = ht.table;
	if (table == NULL){
		throw ex;
	}
}

bool HashTable::contains(const string &s) const {
	
	int start = getHashCode(&s[0]) % capacity;
	
	for (int i=0; i<capacity; i++) {
		int pos = (getHashCode(&s[0]) + i) % capacity;
		if (table[pos] == s){
			return true;
		}
		if (i != 0 && pos == start) {
			return false;
		}
	}
	
	return false;
}

bool HashTable::contains(const char *s) const {
	
	int start = getHashCode(&s[0]) % capacity;
	
	for (int i=0; i<capacity; i++) {
		int pos = (getHashCode(&s[0]) + i) % capacity;
		if (table[pos] == s){
			return true;
		}
		if (i != 0 && pos == start) {
			return false;
		}
	}
	
	return false;
}

string HashTable::print() const {
  string str;
  char buf[128];
  
/* Remove the following comment if you want 
 * to try the iterator version.
 */
#define __USE_ITERATOR__
#ifdef  __USE_ITERATOR__
  int j=0;
  cout << "........end " <<(*end()) << endl;
  for(HashTable::Iterator it = begin(); it!=end();it++ ) {
	  cout << "........it " <<(*it) << endl;
      sprintf(buf, "%2d. -%s-\n", j++, (*(it)).c_str());
      str.append(buf);
    }
  
#else

  for(int i=0,j=0; i<capacity; i++) 
	
    if(!isAvailable(i)) {
      sprintf(buf, "%2d. -%s-\n", j++, table[i].c_str());
      str.append(buf);
    }
  
#endif
  sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", capacity, size);
  str.append(buf);
  return str;
}

bool HashTable::add(const string &str) {
	
	HashTableException  ex;
	bool flag = false;
	
	if (contains(str)) {
		return false;
	}
	for (int i=0; i < capacity; i++) {
		if (isAvailable(i)) {
			flag = true;
		}
	}
	
	if (flag == false) {
		throw ex;	
	}
	
	int start = getHashCode(&str[0]) % capacity;
	for (int i=0; i < capacity; i++){
		int pos = (getHashCode(&str[0]) + i) % capacity;
		if (isAvailable(pos)){
			table[pos] = str;
			size++;
			return true;
		}
		if (i != 0 && pos == start) {
			return false;
		}
	}
	return false;
}

bool HashTable::add(const char *s) {
	
	HashTableException ex;
	bool flag = false;
	
	if (contains(s)) {
		return false;
	}
	for (int i=0; i < capacity; i++) {
		if (isAvailable(i)) {
			flag = true;
		}
	}
	if (flag == false) {
		throw ex;
	}
	
	int start = getHashCode(s) % capacity;
	for (int i=0; i < capacity; i++){
		int pos = (getHashCode(s) + i) % capacity;
		if (isAvailable(pos)){
			table[pos] = s;
			size++;
			return true;
		}
		if (i != 0 && pos == start) {
			return false;
		}
	}
	return false;
}

bool HashTable::remove(const string &str) {
	
	int i;
	if (contains(str)){
		for (i=0; i<capacity ;i++) {
			if (this->table[i] == str){
				this->table[i].clear();
				this->table[i] = "##tomb##";
				this->size--;
				return true;
			}
		}
	}
	return false;
}

bool HashTable::remove(const char *s) {
	
	int i;
	if (contains(s)){
		for (i=0; i<capacity ;i++) {
			if (this->table[i] == s){
				this->table[i].clear();
				this->table[i] = "##tomb##";
				this->size--;
				return true;
			}
		}
	}
	return false;
}

HashTable& HashTable::operator=(const HashTable &ht) {
	
	capacity = ht.capacity;
	size = ht.size;
	table = ht.table;
	
	return (*this);
}

bool HashTable::operator += (const string &str) { 
	
	return add(str); 
}
bool HashTable::operator += (const char* s) { 
	
	return add(s);
}
bool HashTable::operator -= (const string &str) {
  
	return remove(str);
}
bool HashTable::operator -= (const char *s) {
	 
	return remove(s);
}

HashTable HashTable::operator + (const string &str) const {
	
	HashTableException  ex;
	HashTable ht;
	bool flag = false;
	
	for (int i=0; i < capacity; i++) {
		if (isAvailable(i)) {
			flag=true;
		}
	}
	
	if (!flag) {
		throw ex;
	}
	
	ht = HashTable(*this);
		
	if (!contains(str) && flag) ht.add(str);
	
	return(ht);	
}

HashTable HashTable::operator + (const char* s) const {
	
	HashTableException  ex;
	HashTable ht;
	bool flag = false;
	
	for (int i=0; i < capacity; i++) {
		if (isAvailable(i)) {
			flag=true;
		}
	}
	
	if (!flag) {
		throw ex;
	}
		
	ht = HashTable(*this);
		
	if (!contains(s) && flag) ht.add(s);
	
	return(ht);
}
HashTable HashTable::operator - (const string &str) const {
	
	HashTable ht = HashTable(*this);
		
	if (contains(str)){
		ht.remove(str);
	}
	
	return(ht);
}
HashTable HashTable::operator - (const char *s) const {
	
	HashTable ht = HashTable(*this);
		
	if (contains(s)){
		ht.remove(s);
	}
	
	return(ht);
}

HashTable HashTable::operator+(const HashTable &t) const {

	int new_capacity = t.capacity + capacity;
	HashTable ht = HashTable(new_capacity);
	
	for (int i=0; i<capacity; i++) {
		ht.add(table[i]);
	}
	for (int i=0; i<t.capacity; i++) {
		ht.add(t.table[i]);
	} 
	
	return(ht);
}

HashTable& HashTable::operator+=(const HashTable &t) {
	
	*this  = *this + t;
		
	return (*this);
}

std::ostream& operator<<(std::ostream &os, HashTable &t) {
	
	os << t.print();
	return os;
}

HashTable::Iterator HashTable::begin() const {
	
	Iterator it = Iterator(this);
	return(it);
}

HashTable::Iterator HashTable::end() const {
	
	Iterator it = Iterator(this, false);
	return (it);
}
