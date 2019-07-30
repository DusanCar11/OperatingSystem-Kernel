/*
 * KSemT.h
 *
 *  Created on: Jul 9, 2018
 *      Author: OS1
 */

#ifndef KSEMT_H_
#define KSEMT_H_
class List;
class KernelSem {
public:
	KernelSem(int init);
	void wait(int toBlock);
	void signal();
	~KernelSem();
	int val() const;
private:
	int value;
	List* cekaju;
};



#endif /* KSEMT_H_ */
