#pragma once
#include <iostream>
#include "semaphore.h"
#include <vector>
#include <map>
class global_id
{
	semaphore S0;
	semaphore S1;
	int cg = 0;
	int ng = 0;
	int inpLen;
	int outLen;
	int len;

	//std::vector<int> neurons;
	
	//map connection <n0, n1> to int
	//map neuron <c0> to int
	std::map<int, int> neurons;
	std::map< std::pair<int, int>, int > connections;
public:
	global_id(int inplen, int outlen);
	//make semaphore implementation
	int getCID(int n0, int n1);
	int getNID(int c0);

	std::map<int, int>* get_neurons();
	std::map< std::pair<int, int>, int >* get_connections();
};

std::ostream& operator<<(std::ostream& os, global_id& gid);