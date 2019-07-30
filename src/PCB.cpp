/*
 * PCB.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */
#include "Thread.h"
#include "PCB.h"
#include <dos.h>
#include "List.h"
#include "System.h"

#define lock System::running->lck++;
#define unlock if (System::running->lck==1 && System::happened==1) \
		{System::happened=0; dispatch();} System::running->lck--;
#include <STDIO.H>
#include <STDARG.H>

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	lock;
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	unlock;
		return res;
}

PCB::PCB(unsigned long stackSize, unsigned int time, Thread* mT) {
	if (stackSize >= 32768)
		stackSize=32767;
	timeSlice=time;
	timeToSleep=0;
	lck=0;
	myThread=mT;
	stanje = NEW;
	basePointer=stackPointer=stackSegment=0;
	stack=0;
	blokirane=new List();
	unsigned long realstacksize = stackSize;
	stack=new unsigned[realstacksize];
	stack[realstacksize-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[realstacksize-2]=FP_SEG(PCB::wrapper);
	stack[realstacksize-3]=FP_OFF(PCB::wrapper);
	stackPointer=FP_OFF(stack+realstacksize-12);
	stackSegment=FP_SEG(stack+realstacksize-12);
	basePointer=stackPointer;
#endif;
}

PCB::~PCB() {
	lock;
	delete []stack;
	delete blokirane;
	stack=0; myThread=0; blokirane=0;
	unlock;
}

void PCB::wrapper() {
	System::running->myThread->run();
	lock;
	System::running->stanje=FINISHED;
	System::running->blokirane->odblokiraj();
	unlock;
	dispatch();
}

unsigned PCB::getStackPointer() {
	return stackPointer;
}

void PCB::setStackPointer(unsigned sp) {
	stackPointer=sp;
}

unsigned PCB::getStackSegment() {
	return stackSegment;
}

void PCB::setStackSegment(unsigned ss) {
	stackSegment=ss;
}

unsigned PCB::getBasePointer() {
	return basePointer;
}

void PCB::setBasePointer(unsigned bp) {
	basePointer=bp;
}

unsigned PCB::getTimeSlice() {
	return timeSlice;
}

void PCB::setTimeSlice(unsigned ts) {
	timeSlice=ts;
}

unsigned PCB::getTimeToSleep() {
	return timeToSleep;
}

void PCB::setTimeToSleep(unsigned tts) {
	timeToSleep=tts;
}

int PCB::getStanje() {
	return stanje;
}

void PCB::setStanje(int k) {
	stanje=k;
}

Thread* PCB::getMyThread() {
	return myThread;
}

