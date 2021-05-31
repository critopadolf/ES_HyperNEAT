#pragma once
class config
{
public:
	//NEAT
	float newNeuronRate = 0.02,
		newConnectionRate = 0.01,
		deleteNeuronRate = 0.001,
		deleteConnectionRate = 0.001,
		mutateWeightRate = 0.001,
		mutateNeuronRate = 0.01;

	float maxWeight = 2,
		 minWeight = -2;

	//MESH mutation params
	float newPointRate = 0.001,
		removePointRate = 0.001,
		mutatePointRate = 0.01;
	//MESH max params
	int	 maxMeshStartingPoints = 0;
	float minMeshVal = -2,
		  maxMeshVal = 2;


	config(float newNeuronRate, float newConnectionRate, float deleteNeuronRate, float deleteConnectionRate, float mutateWeightRate, float newPointRate, float removePointRate, float mutatePointRate, int maxMeshStartingPoints, float maxMeshVal, float minMeshVal, float maxWeight, float minWeight);
		 
};

