/*
 * System.h
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
typedef void interrupt(*PInterrupt)(...);
class PCB;
class List;

class System {
public:
	volatile static int happened;
	static PInterrupt staritimer;
	static void inic();
	static void restore();
	static void interrupt timer(...);
	static PCB* running;
	static List* uspavane;
	volatile static int context_switch_on_demand;
	volatile static unsigned int cntr;
	static PCB* IdlePCB;
	static PCB* forMain;
};



#endif /* SYSTEM_H_ */
