#pragma once
#include <iostream>
#include <vector>
#include "neat.h"
#include "Mesh.h"

class Model
{
public:
	//Mesh.h =====>		int dimensions, int inpLength, int outLength, int maxNumPoints, float newPointRate, float removePointRate, float mutatePointRate
	//neat.h =====>		 
	Model();
	Model(int inpLen, int outLen, int meshDim, std::mt19937* meng, global_id* gid, config* cfg);
	friend void mate(Model* m_new, const Model& m0, const Model& m1, global_id* gid, config* cfg, std::mt19937* meng);
	Mesh msh; //mesh used as base for direct encoding network
	neat prenet; //neat network indirect encoding
};

std::ostream& operator<<(std::ostream& os, Model&  m);