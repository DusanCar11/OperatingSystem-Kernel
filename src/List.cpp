/*
 * List.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */
#include "PCB.h"
#include "List.h"
#include "SCHEDULE.H"
#include <stdio.h>
#include "System.h"
#include "SCHEDULE.H"
#include "Thread.h"
#include <stdlib.h>

ListElement* List::first_static=0;
ListElement* List::last_static=0;

#define lock System::running->lck++;
#define unlock if (System::running->lck==1 && System::happened==1) \
		{System::happened=0; dispatch();} System::running->lck--;

void List::add(PCB* elem) {
	asm pushf; asm cli;
	if (first==0) {
		first=new ListElement(elem);
		last=first;
	}
	else {
		last->next=new ListElement(elem);
		last=last->next;
	}
	asm popf;
}

void List::odblokiraj() {
	asm pushf; asm cli;
	for (ListElement* tmp=first; tmp!=0;) {
		ListElement* tmp2 = tmp->next;
		tmp->toSave->setStanje(READY);
		Scheduler::put(tmp->toSave);
		tmp->toSave=0;
		delete tmp;
		tmp=tmp2;
	}
	first=0; last=0;
	asm popf;
}

void List::azuriraj_uspavane() {
	asm pushf; asm cli;
	int ispitivanje;
	ListElement* tmpprev=first_static;
	for (ListElement* tmp=first_static; tmp!=0; ) {
		ispitivanje=tmp->toSave->getTimeToSleep();
		ispitivanje--;
		if (ispitivanje > 0)
			tmp->toSave->setTimeToSleep(ispitivanje);
		else {
			ListElement* tmpToTake=tmp->next;
			if (tmp==first_static) {
				if (first_static==last_static)
					last_static=last_static->next;
				first_static=tmp->next;
				tmp->next=0;
				tmp->toSave->setStanje(READY);
				Scheduler::put(tmp->toSave);
				tmpprev=first_static;
			}
			else {
				tmpprev->next=tmp->next;
				tmp->next=0;
				tmp->toSave->setStanje(READY);
				Scheduler::put(tmp->toSave);
				if (last_static==tmp)
					last_static=tmpprev;
			}
			tmp->toSave=0;
			delete tmp;
			tmp=tmpToTake;
			continue;
		}
		if (tmp!=tmpprev)
			tmpprev=tmpprev->next;
		tmp=tmp->next;
	}
	asm popf;
}

void List::add_uspavane(PCB* toAdd) {
	asm pushf; asm cli;
	if (first_static==0) {
		first_static=new ListElement(toAdd);
		last_static=first_static;
	}
	else {
		last_static->next=new ListElement(toAdd);
		last_static=last_static->next;
	}
	asm popf;
}

PCB* List::getFirst() {
	asm pushf; asm cli;
	PCB* toReturn = first->toSave;
	ListElement* tmp2=first->next;
	if (first==last)
		last=last->next;
	first->next=0;
	first->toSave=0;
	delete first;
	first=tmp2;
	if (tmp2==0)
		first=last=0;
	asm popf;
	return toReturn;
}

List::~List() {
	lock;
	ListElement* tmp2;
	for (ListElement* tmp=first; tmp!=0; ) {
		tmp2=tmp->next;
		tmp->toSave=0;
		//tmp->toSave->setStanje(READY);
		//Scheduler::put(tmp->toSave);
		delete tmp;
		tmp=tmp2;
	}
	first=last=0;
	unlock;
}


