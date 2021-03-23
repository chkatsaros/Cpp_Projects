#include "HashTable.h"
#include "HashTableException.h"
#include <stdio.h>

using namespace std;

HashTable::Iterator::Iterator(const HashTable *t) {
	
	this->ht = t;
	this->curr = NULL;
	
	for (int i=0; i<t->capacity; i++) {
		if (!t->isAvailable(i)){
			this->curr = &t->table[i];
			break;
		}
	}
					
}
HashTable::Iterator::Iterator(const HashTable *t,bool start) {
	
	this->ht = t;
	this->curr = NULL;
		
	if (start) {
		for (int i=0; i<t->capacity; i++) {
			if (!t->isAvailable(i)){
				this->curr = &t->table[i];
				break;
			}
		}		
	}
	else {
		if (t->size != 0) {
			this->curr = &t->table[t->capacity];
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
	
	
	++this->curr;
	
	while(((*this->curr).empty() || (*this->curr) == "##tomb##") && curr != this->ht->end().curr ) {
		++this->curr;
	}
	
	return(*this);
}

HashTable::Iterator HashTable::Iterator::operator++(int a) {
	
	Iterator old_it = Iterator(*this);
	
	++this->curr;
	
	while(((*this->curr).empty() || (*this->curr) == "##tomb##") && curr != this->ht->end().curr ) {
		++this->curr;
	}
	
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
  
	return (*this->curr);
}

const string* HashTable::Iterator::operator->() {
	
	return(this->curr);
}
