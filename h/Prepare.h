/*
 * Prepare.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef PREPARE_H_
#define PREPARE_H_
#include "Thread.h"
#include "IVTEnt.h"

#define PREPAREENTRY(ivtno, logical) void interrupt ulaz##ivtno(...); \
	IVTEntry noviUlaz##ivtno(ivtno, ulaz##ivtno); \
	void interrupt ulaz##ivtno(...) { \
		if (logical) noviUlaz##ivtno.zoviStaru(); \
		noviUlaz##ivtno.signal(); \
		dispatch(); \
	}



#endif /* PREPARE_H_ */
