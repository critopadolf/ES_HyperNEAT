#pragma once
#include <iostream>
#include <vector>
#include "neural_mesh.h"

class Model
{
public:
	//Mesh.h =====>		int dimensions, int inpLength, int outLength, int maxNumPoints, float newPointRate, float removePointRate, float mutatePointRate
	//neat.h =====>		 
	Model();
	Model(int inpLen, int outLen, int meshDim, std::mt19937* meng, global_id* gid, config* cfg);
	friend void mate(Model* m_new, const Model& m0, const Model& m1, global_id* gid, config* cfg, std::mt19937* meng);
	Mesh msh; //mesh used as base for direct encoding network
	neat neuron_net; //neat network indirect encoding for neurons
	neat conn_net; //neat network indirect encoding for connections

	neural_mesh neural_network;

	void build();
	void activate(std::vector<float>* inp, std::vector<float>* outp);
};

std::ostream& operator<<(std::ostream& os, Model&  m);