/*
 * IVTEnt.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef IVTENT_H_
#define IVTENT_H_
#include "System.h"
class KernelEvent;
class IVTEntry {
public:
	IVTEntry(unsigned char ivtNo, PInterrupt nova_prekidna);
	~IVTEntry();
	void signal();
	void zoviStaru();
	void setMyKerEvent(KernelEvent* ke);
	static IVTEntry *IVTTable[];
private:
	KernelEvent* myEvent;
	unsigned char myIVTNo;
	PInterrupt stara_prekidna;
};



#endif /* IVTENT_H_ */
