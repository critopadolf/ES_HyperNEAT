#include "neuron.h"
neuron::neuron()
{

}
neuron::neuron(float bias_fl, float activation_fl, int id_fl)
{
	bias = bias_fl;
	act = activation_fl * ACTIVATION_LIST.size();
	id = id_fl;
}
neuron::neuron(std::mt19937* mersenne_engine, int nid, config* cfg)
{
	bias = randfloat(mersenne_engine, cfg->minWeight, cfg->maxWeight);
	act = randInt(mersenne_engine, 0, ACTIVATION_LIST.size());
	id = nid;
}

neuron::neuron(std::mt19937* mersenne_engine, global_id* gid, int c, config* cfg)
{
	bias = randfloat(mersenne_engine, cfg->minWeight, cfg->maxWeight);
	act = randInt(mersenne_engine, 0, ACTIVATION_LIST.size());
	id = gid->getNID(c);
}

float neuron::getVal()
{
	return Z;
}

std::ostream& operator<<(std::ostream& os, const neuron& n)
{
	os << n.id << " | " << n.act << " | " << n.bias << "\n";
	return os;
}
void neuron::set(float z)
{
	Z = z;
}
void neuron::load(float x)
{
	tmp += x;
}
float neuron::activate()
{
	Z = ACTIVATION_LIST[act](tmp);
	tmp = 0;
	return Z;
}
void neuron::mutate(std::mt19937* meng, config* cfg)
{
	if(randfloat(meng, 0, 1) < cfg->mutateWeightRate)
		mutateFloat(&bias, meng, cfg->minWeight, cfg->maxWeight, 0.01f);
	if (randfloat(meng, 0, 1) < cfg->mutateNeuronRate)
		mutateInt(&act, meng, 0, ACTIVATION_LIST.size());
}

int neuron::getID()
{
	return id;
}

int neuron::getAct()
{
	return act;
}
void neuron::setInp()
{
	act = 0;
}
bool operator==(const neuron& n1, const neuron& n2)
{
	return n1.id == n2.id;
}

bool operator!=(const neuron& n1, const neuron& n2)
{
	return n1.id != n2.id;
}

bool operator<(const neuron& n1, const neuron& n2)
{
	return n1.id < n2.id;
}

bool operator<=(const neuron& n1, const neuron& n2)
{
	return n1.id <= n2.id;
}

bool operator>(const neuron& n1, const neuron& n2)
{
	return n1.id > n2.id;
}

bool operator>=(const neuron& n1, const neuron& n2)
{
	return n1.id >= n2.id;
}
