/*
 * List.h
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
class PCB;

struct ListElement {
	PCB* toSave;
	ListElement* next;
	ListElement(PCB* ts) {toSave=ts; next=0;}
};

class List {
	ListElement *first, *last;
	static ListElement *first_static, *last_static;
public:
	List() {first=0; last=0;}
	void add(PCB* elem);
	void odblokiraj();
	int empty();
	PCB* getFirst();
	static void azuriraj_uspavane();
	static void add_uspavane(PCB *toAdd);
	~List();
};



#endif /* LIST_H_ */
