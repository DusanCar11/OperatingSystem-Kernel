/*
 * PCB.h
 *
 *  Created on: Jun 18, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#define NEW 0
#define READY 1
#define BLOCKED 2
#define IDLE 3
#define FINISHED 4
class List;
class Thread;

class PCB {
private:
	unsigned* stack;
	unsigned stackPointer;
	unsigned stackSegment;
	unsigned basePointer;
	unsigned int timeSlice;
	unsigned int timeToSleep;
	volatile int stanje;
	Thread* myThread;
public:
	int waitReturned;
	List* blokirane;
	int lck;
	PCB(unsigned long ss, unsigned int tim, Thread* mT);
	Thread* getMyThread();
	static void wrapper();
	unsigned getStackPointer();
	void setStackPointer(unsigned sp);
	unsigned getStackSegment();
	void setStackSegment(unsigned ss);
	unsigned getBasePointer();
	void setBasePointer(unsigned bp);
	unsigned getTimeSlice();
	void setTimeSlice(unsigned ts);
	unsigned getTimeToSleep();
	void setTimeToSleep(unsigned tts);
	int getStanje();
	void setStanje(int k);
	~PCB();
};



#endif /* PCB_H_ */
