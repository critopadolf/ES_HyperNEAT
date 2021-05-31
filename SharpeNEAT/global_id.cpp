#include "global_id.h"

global_id::global_id(int inplen, int outlen)
{
	inpLen = inplen;
	outLen = outlen;
	len = inplen + outlen;
	ng = len-1;
	int t = 0;
	for (int x = 0; x < inplen; x++)
	{
		for (int y = inplen; y < len; y++)
		{
			connections[std::make_pair(x, y)] = t;
			t++;
		}
	}
	cg = t-1;
	S0.release();
	S1.release();
}

int global_id::getCID(int n0, int n1)
{
	S0.acquire();
	int ret;
	//if the Neuron is in the table, return that number
	std::pair<int, int> mk = std::make_pair(n0, n1);
	auto k = connections.find(mk);
	if (k != connections.end())
	{
		ret = (*k).second;
	}
	//otherwise increment ng
	else
	{
		connections.insert( std::make_pair(mk, ++cg) );
		ret = cg;
	}

	S0.release();
	return ret;
}

int global_id::getNID(int c0)
{
	S1.acquire();
	int ret;
	//if the Neuron is in the table, return that number
	auto k = neurons.find(c0);
	if (k != neurons.end())
	{
		//map[cg]
		ret = (*k).second;
	}
	//otherwise increment ng
	else
	{
		neurons.insert( std::make_pair(c0, ++ng) );
		ret = ng;
	}

	S1.release();
	return ret;
}
std::map<int, int>* global_id::get_neurons()
{
	return &neurons;
}
std::map< std::pair<int, int>, int >* global_id::get_connections()
{
	return &connections;
}
std::ostream& operator<<(std::ostream& os, global_id& gid)
{
	const std::map<int, int>* neurons = gid.get_neurons();
	const std::map< std::pair<int, int>, int >* connnections = gid.get_connections();
	os << "neurons:\n[ ";
	for (auto n : *neurons)
	{
		os << "<" << n.first << ", " << n.second << ">"  << ", ";
	}
	os << " ]\n";

	os << "connections:\n[ ";
	for (auto c : *connnections)
	{
		os << "<<" << c.first.first << ", " << c.first.second << ">, " << c.second << ">" << ", ";
	}
	os << " ]\n";
	return os;
}