#include "config.h"

config::config(float newNeuronRate, float newConnectionRate, float deleteNeuronRate, float deleteConnectionRate, float mutateWeightRate, float newPointRate, float removePointRate, float mutatePointRate, int maxMeshStartingPoints, float maxMeshVal, float minMeshVal, float maxWeight, float minWeight) :
	newNeuronRate(newNeuronRate), newConnectionRate(newConnectionRate), deleteNeuronRate(deleteNeuronRate), deleteConnectionRate(deleteConnectionRate), mutateWeightRate(mutateWeightRate),
	newPointRate(newPointRate), removePointRate(removePointRate), mutatePointRate(mutatePointRate), maxMeshStartingPoints(maxMeshStartingPoints), maxMeshVal(maxMeshVal), minMeshVal(minMeshVal),
	maxWeight(maxWeight), minWeight(minWeight)
{

}