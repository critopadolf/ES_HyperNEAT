#pragma once
#include <random>
#include "vectorRandom2.cpp"
#include "global_id.h"
#include "activations.h"
#include "config.h"
class neuron
{
private:
	
	float Z = 0;
	float tmp = 0;
	float bias;
	int act;
public:
	int id;
	neuron();
	neuron(float bias_fl, float activation_fl, int id_fl);
	neuron(std::mt19937* mersenne_engine, int nid, config* cfg);
	neuron(std::mt19937* mersenne_engine, global_id* gid, int c, config* cfg);
	void set(float z);
	void load(float x);
	float activate();
	void mutate(std::mt19937* meng, config* cfg);
	int getAct();
	void setInp();
	int getID();
	float getVal();

	friend std::ostream& operator<<(std::ostream& os, const neuron& n);
	friend bool operator==(const neuron& n1, const neuron& n2);
	friend bool operator!=(const neuron& n1, const neuron& n2);
	friend bool operator<(const neuron& n1, const neuron& n2);
	friend bool operator<=(const neuron& n1, const neuron& n2);
	friend bool operator>(const neuron& n1, const neuron& n2);
	friend bool operator>=(const neuron& n1, const neuron& n2);
};

