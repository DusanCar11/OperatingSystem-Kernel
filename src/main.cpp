/*
 * main.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "System.h"
#include <stdio.h>
#include "List.h"
int syncPrintf(const char* format, ...);
int userMain(int argc, char** argv);

int main(int argc, char **argv) {
	System::forMain = new PCB(4096,3,0);
	System::forMain->setStanje(READY);
	syncPrintf("system main begin\n");
	System::running=System::forMain;
	System::inic();
	userMain(argc,argv);
	System::restore();
	printf("Main ends\n");
	delete System::forMain;
	delete System::IdlePCB;
	delete System::uspavane;
	System::running=0;
	return 0;
}


