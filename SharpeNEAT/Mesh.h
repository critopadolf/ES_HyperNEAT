#pragma once
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
#include "vectorRandom2.cpp"
#include "vectorMath.cpp"
#include "KDTree.hpp"
#include "config.h"

class Mesh
{
public:
	std::vector< point_t > input;
	std::vector< point_t > hidden;
	std::vector< point_t > output;

	int dim;
	float min = 0;
	float max = 1;
	
	//mutation params
	/*
	float newPointRate = 0.001;
	float removePointRate = 0.001;
	float mutatePointRate = 0.01;
	*/

	Mesh();
	Mesh(float min, float max, float dim);
	Mesh(std::mt19937* meng, int dimensions, int inpLength, int outLength, int maxNumPoints);
	Mesh(std::mt19937* meng, int dimensions, int inpLength, int outLength, int maxNumPoints, float minMeshVal, float maxMeshVal);
	Mesh(const Mesh& m);
	void setParams(float min, float max, int dim);
	point_t std_dev(std::vector< point_t >* points);
	point_t mean(std::vector< point_t >* points);
	point_t& operator[](int); //t
	//Mesh mate(Mesh* m);
	friend void mate(Mesh* m, const Mesh& m0, const Mesh& m1, std::mt19937* meng, config* cfg);
	//friend void mate(neat* nte, const neat& n1, const neat& n2, global_id* gid, config* cfg);
	//mutation ops
	void mutate(std::mt19937* meng, config* cfg);
	point_t newPoint(std::mt19937* meng);
	void mutatePointVec(std::vector<point_t>* p, std::mt19937* meng, config* cfg);


	//mating ops
	//merges hidden vertices by inserting them into a K-D tree (dim-dimensional quadtree/octree) and averages together vertices within a radius (thresh) of eachother
	int merge_Verts(float thresh);

	void testMerge();

	
	//getters
	int inpLen();
	int outLen();
	int hiddenLen();
	int dimSize();
	int size();
	std::vector<point_t>* getInput();
	std::vector<point_t>* getHidden();
	std::vector<point_t>* getOutput();
};
std::ostream& operator<<(std::ostream& os, const Mesh& m);