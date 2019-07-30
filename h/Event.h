/*
 * Event.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_
class KernelEvent;
class Event {
public:
	Event(unsigned char ivtNo);
	~Event();
	void wait();
	void signal();
private:
	KernelEvent* myImpl;
};



#endif /* EVENT_H_ */
