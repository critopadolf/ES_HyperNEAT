#pragma once
#include <random>
#include "vectorRandom2.cpp"
#include "global_id.h"
#include "neuron.h"

class connection
{
public:
	connection();
	connection(float weight, int n0, int n1);
	connection(global_id* gid, int n0, int n1, std::mt19937* mersenne_engine);
	void load(float inp);
	void mutate(std::mt19937* meng, config* cfg);
	int getN(int x);
	neuron* getNref(int x);
	int getID();
	void disable();
	void setRef(neuron* n0, neuron* n1);
	float getVal();
	float getWeight();

	friend std::ostream& operator<<(std::ostream& os, const connection& c);
	friend bool operator==(const connection& n1, const connection& n2);
	friend bool operator!=(const connection& n1, const connection& n2);
	int ng[2]; //global_id value given to neurons
	neuron* nref[2];
	int cg; //connection ID

private:
	bool enabled = true;
	float Z; //value//
	float w; //weight//

	
};

