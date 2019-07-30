/*
 * IVTEnt.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */
#include "System.h"
#include "IVTEnt.h"
#include <dos.h>
#include "KEvent.h"
IVTEntry* IVTEntry::IVTTable[256];
PInterrupt stara_prekidna=0;

#define lock asm pushf; \
	asm cli;
#define unlock asm popf;

IVTEntry::IVTEntry(unsigned char ivtNo, PInterrupt nova_prekidna) {
	lock;
	myIVTNo=ivtNo;
	IVTEntry::IVTTable[myIVTNo]=this;
	myEvent=0;
	stara_prekidna=0;
#ifndef BCC_BLOCK_IGNORE
	stara_prekidna=getvect(myIVTNo);
	setvect(myIVTNo, nova_prekidna);
#endif
	unlock;
}

void IVTEntry::signal() {
	lock;
	if (myEvent!=0)
		myEvent->signal();
	unlock;
}

void IVTEntry::setMyKerEvent(KernelEvent* ke) {
	lock;
	myEvent=ke;
	unlock;
}

IVTEntry::~IVTEntry() {
	lock;
	IVTEntry::IVTTable[myIVTNo]=0;
#ifndef BCC_BLOCK_IGNORE
	setvect(myIVTNo, stara_prekidna);
#endif;
	(*stara_prekidna)();
	unlock;
}

void IVTEntry::zoviStaru() {
	if (stara_prekidna!=0)
		(*stara_prekidna)();
}


