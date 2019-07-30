/*
 * KEvent.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */
#include "KEvent.h"
#include "PCB.h"
#include "IVTEnt.h"
#include "Thread.h"
#include "SCHEDULE.H"

#define lock asm pushf;\
	asm cli;
#define unlock; asm popf;

KernelEvent::KernelEvent(unsigned char ivtNo) {
	if (IVTEntry::IVTTable[ivtNo]!=0) {
		myIVTNo=ivtNo;
		value=0;
		PCBMade=System::running;
		IVTEntry::IVTTable[myIVTNo]->setMyKerEvent(this);
	}
}

void KernelEvent::wait() {
	lock;
	if (PCBMade==System::running) {
		if (value==1)
			value=0;
		else if (value==0) {
			value=-1;
			PCBMade->setStanje(BLOCKED);
			unlock;
			dispatch();
			return;
		}
		else
			value=-1;
	}
	unlock;
}

void KernelEvent::signal() {
	if (value==-1) {
		PCBMade->setStanje(READY);
		Scheduler::put(PCBMade);
		value=0;
	}
	else if (value==0)
		value=1;
	else
		value=1;
}

KernelEvent::~KernelEvent() {
	PCBMade=0;
}


