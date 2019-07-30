/*
 * System.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */
#include <dos.h>
#include "System.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Idle.h"
#include "List.h"

volatile int System::happened=0;
PCB* System::forMain=0;
PCB* System::running=0;
PCB* System::IdlePCB=0;
List* System::uspavane=0;
PInterrupt System::staritimer;
volatile int System::context_switch_on_demand=0;
volatile unsigned int System::cntr=20;

void System::inic() {
#ifndef BCC_BLOCK_IGNORE
	staritimer=getvect(0x08);
	setvect(0x08,System::timer);
	Idle* idle = new Idle();
	IdlePCB=idle->getPCB();
#endif
}

void System::restore() {
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08, staritimer);
#endif
}

unsigned tsp, tss, tbp;
extern void tick();
void interrupt System::timer(...) {
	if (context_switch_on_demand==0) {
		(*staritimer)();
		tick();
		List::azuriraj_uspavane();
		cntr--;
	}

	if ((context_switch_on_demand==1) || ((cntr<=0)/* && (System::running->getTimeSlice()!=0)*/)) {
		if (System::running->lck>0 && context_switch_on_demand==0) {
			happened=1;
			return;
		}
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}

		System::running->setStackPointer(tsp);
		System::running->setStackSegment(tss);
		System::running->setBasePointer(tbp);

		if ((System::running!=0) && (System::running->getStanje()!=FINISHED) && (System::running->getStanje()!=BLOCKED) && (System::running != IdlePCB))
			Scheduler::put(System::running);

		System::running=Scheduler::get();

		if (System::running==0)
			System::running=IdlePCB;

		tsp=System::running->getStackPointer();
		tss=System::running->getStackSegment();
		tbp=System::running->getBasePointer();
		System::cntr=System::running->getTimeSlice();

		asm {
			mov sp,tsp
			mov ss,tss
			mov bp,tbp
		}
	}
	context_switch_on_demand=0;
}






