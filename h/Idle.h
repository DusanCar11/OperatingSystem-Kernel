/*
 * Idle.h
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */
#ifndef IDLE_H_
#define IDLE_H_
#include <stdio.h>
#include "Thread.h"
class System;
class PCB;

class Idle: public Thread {
public:
	volatile int i;
	volatile int j;
	Idle() {
		startIdle();
		i=0; j=0;
		System::IdlePCB=getPCB();
	}
	void run() {
		while(i==0) {
			if (j%100000000000==0)
				//printf("Dusan car");
			j++;
		}
	}
};



#endif /* IDLE_H_ */
