/*
 * KEvent.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef KEVENT_H_
#define KEVENT_H_
class PCB;
class KernelEvent {
public:
	KernelEvent(unsigned char ivtNo);
	void wait();
	void signal();
	~KernelEvent();
private:
	unsigned char myIVTNo;
	int value;
	PCB* PCBMade;
};



#endif /* KEVENT_H_ */
