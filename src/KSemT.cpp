/*
 * KSemT.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */
#include "KSemT.h"
#include "List.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "System.h"
#include "Thread.h"

#define lock asm pushf;\
	asm cli;
#define unlock asm popf;

KernelSem::KernelSem(int init) {
	value=init;
	cekaju=new List();
}

void KernelSem::wait(int toBlock) {
	lock;
	if (toBlock==0 && value<=0) {
		System::running->waitReturned=-1;
		unlock;
		return;
	}
	if (--value<0) {
		System::running->setStanje(BLOCKED);
		cekaju->add(System::running);
		System::running->waitReturned=1;
		unlock;
		dispatch();
		return;
	}
	else {
		System::running->waitReturned=0;
		unlock;
		return;
	}
}

void KernelSem::signal() {
	if (value++<0) {
		PCB* toRevive = cekaju->getFirst();
		toRevive->setStanje(READY);
		Scheduler::put(toRevive);
	}
}

KernelSem::~KernelSem() {
	delete cekaju;
	cekaju=0;
}

int KernelSem::val() const {
	return value;
}



