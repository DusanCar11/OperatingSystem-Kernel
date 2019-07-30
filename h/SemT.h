/*
 * SemT.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef SEMT_H_
#define SEMT_H_

class KernelSem;
class Semaphore {
public:
	int wait(int toBlock);
	Semaphore(int init);
	~Semaphore();
	void signal();
	int val() const;
private:
	KernelSem* myImpl;
};



#endif /* SEMT_H_ */
