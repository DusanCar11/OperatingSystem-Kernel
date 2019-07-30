/*
 * SemT.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#include "SemT.h"
#include "KSemT.h"
#include "System.h"
#include "Thread.h"
#include "PCB.h"
#define lock System::running->lck++;
#define unlock if (System::running->lck==1 && System::happened==1) \
		{System::happened=0; dispatch();} System::running->lck--;


Semaphore::Semaphore(int init) {
	lock;
	myImpl=new KernelSem(init);
	unlock;
}

int Semaphore::wait(int toBlock) {
	//lock;
	myImpl->wait(toBlock);
	//unlock;
	return System::running->waitReturned;
}

void Semaphore::signal() {
	lock;
	myImpl->signal();
	unlock;
}

Semaphore::~Semaphore() {
	lock;
	delete myImpl;
	unlock;
}

int Semaphore::val() const {
	return myImpl->val();
}
