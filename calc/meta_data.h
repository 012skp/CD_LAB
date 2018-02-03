#ifndef __META_DATA_H
#define __META_DATA_H

	#include<stdio.h>
	#include<stdlib.h>	

	#define BVAL 0
	#define DVAL 1
	struct node{
		int type; // 0 means bval, 1 means dval.
		double dval;
		int bval;
	};

	struct node* allocate();

#endif
