/*
 * Thread.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */
#include "Thread.h"
#include "PCB.h"
#include "System.h"
#include "List.h"
#include "SCHEDULE.H"
#include <stdio.h>

#define lock System::running->lck++;
#define unlock if (System::running->lck==1 && System::happened==1) \
		{System::happened=0; dispatch();} System::running->lck--;

int Thread::ID=0;

Thread::Thread(StackSize ss, Time tim) {
	lock;
	myPCB = new PCB(ss,tim,this);
	id=++ID;
	unlock;
}

void Thread::start() {
	lock;
	myPCB->setStanje(READY);
	Scheduler::put(myPCB);
	unlock;
}

void Thread::waitToComplete() {
	lock;
	if ((myPCB->getStanje()!=FINISHED) && (myPCB!=System::running) && (myPCB!=System::IdlePCB)) {
		System::running->setStanje(BLOCKED);
		myPCB->blokirane->add(System::running);
		unlock;
		dispatch();
	}
	else
		unlock;
}

Thread::~Thread() {
	waitToComplete();
	lock;
	delete myPCB;
	unlock;
}

void Thread::startIdle() {
	lock;
	myPCB->setStanje(IDLE);
	unlock;
}

void dispatch() {
	asm pushf;
	asm cli;
	System::context_switch_on_demand=1;
	System::timer();
	asm popf;
}

PCB* Thread::getPCB() {
	return myPCB;
}

int Thread::getId() {
	return id;
}

void Thread::sleep(Time timeToSleep) {
	lock;
	System::running->setTimeToSleep(timeToSleep);
	System::running->setStanje(BLOCKED);
	System::uspavane->add_uspavane(System::running);
	unlock;
	dispatch();
}

int Thread::getRunningId() {
	return System::running->getMyThread()->id;
}




