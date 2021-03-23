
#include "HashTable.h"
#include "HashTableException.h"
#include <stdio.h>

using namespace std;

HashTable::Iterator::Iterator(const HashTable *t) {
	
	ht = t;
	for (int i=0; i<t->capacity; i++) {
		if (!t->isAvailable(i)){
			curr = &t->table[i];
			break;
		}
	}
					
}
HashTable::Iterator::Iterator(const HashTable *t,bool start) {
	
	ht = t;
	int size_counter=0;
	
	if (start) {
		for (int i=0; i<t->capacity; i++) {
			if (!t->isAvailable(i)){
				curr = &t->table[i];
				break;
			}
		}		
	}
	else {
		for (int i=0; i<t->capacity; i++) {
			if (!t->isAvailable(i))
				size_counter++;
			if (size_counter == t->size) {
				curr = &t->table[i+1];
				break;
			}
		}	
	}	
}




HashTable::Iterator::Iterator(const HashTable::Iterator &it) {
	
	this->curr = it.curr;
	this->ht = it.ht;
}

HashTable::Iterator& HashTable::Iterator::operator=(const HashTable::Iterator &it) {
	
	this->curr = it.curr;
	this->ht = it.ht;
	
	return(*this);
}

HashTable::Iterator HashTable::Iterator::operator++() {
	
	this->curr++;
	return(*this);
}

HashTable::Iterator HashTable::Iterator::operator++(int a) {
	
	Iterator old_it = Iterator(*this);
	++(this->curr);
	return(old_it);
}

bool HashTable::Iterator::operator==(const HashTable::Iterator &it) const {
  
	if( this->curr == it.curr && this->ht == it.ht  ) {
		return (true);	
	}
	else {
		return (false);	
	}
}

bool HashTable::Iterator::operator!=(const HashTable::Iterator &it) const {
	
	if( this->curr == it.curr && this->ht == it.ht ) {
		return (false);	
	}
	else {
		return (true);	
	}
  
}

const string& HashTable::Iterator::operator*() {
  
	return (*curr);
}

const string* HashTable::Iterator::operator->() {
	
	return(curr);
}
