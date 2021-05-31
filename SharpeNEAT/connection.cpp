#include "connection.h"

connection::connection()
{

}

connection::connection(global_id* gid, int n0, int n1,  std::mt19937* mersenne_engine)
{
	cg = gid->getCID(n0, n1); //semaphore integer counter
	ng[0] = n0;
	ng[1] = n1;
	Z = 0;
	w = randfloat(mersenne_engine, -2, 2); //weight
}
void connection::load(float inp)
{
	Z = inp;
	if (!enabled)
		Z = 0;
}
void connection::mutate(std::mt19937* meng, config* cfg)
{
	if(randfloat(meng, 0, 1) < cfg->mutateWeightRate)
		mutateFloat(&w, meng, -2.0f, 2.0f, 0.01f);
}

void connection::disable()
{
	enabled = false;
}

int connection::getN(int x)
{
	return ng[x];
}
neuron* connection::getNref(int x)
{
	return nref[x];
}
void connection::setRef(neuron* n0, neuron* n1)
{
	nref[0] = n0;
	nref[1] = n1;
}
float connection::getVal()
{
	return Z;
}
float connection::getWeight()
{
	return w;
}
int connection::getID()
{
	return cg;
}
std::ostream& operator<<(std::ostream& os, const connection& c)
{
	os << c.cg << " | " << c.ng[0] << " -> " << c.ng[1] << " | " << c.w << "\n";
	return os;
}
bool operator==(const connection& c1, const connection& c2)
{
	return c1.ng[0] == c2.ng[0] && c1.ng[1] == c2.ng[1];
}
bool operator!=(const connection& c1, const connection& c2)
{
	return c1.ng[0] != c2.ng[0] || c1.ng[1] != c2.ng[1];
}
