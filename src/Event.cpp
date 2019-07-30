/*
 * Event.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */
#include "Event.h"
#include "KEvent.h"

#define lock asm pushf;\
	asm cli;
#define unlock asm popf;

Event::Event(unsigned char ivtNo) {
	lock;
	myImpl=new KernelEvent(ivtNo);
	unlock;
}

void Event::wait() {
	//lock;
	myImpl->wait();
	//unlock;
}

void Event::signal() {
	lock;
	myImpl->signal();
	unlock;
}

Event::~Event() {
	lock;
	delete myImpl;
	myImpl=0;
	unlock;
}


