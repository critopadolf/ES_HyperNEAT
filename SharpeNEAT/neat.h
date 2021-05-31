#pragma once
#include <vector>
#include <random>
#include "connection.h"
#include "global_id.h"
#include "vectorMath.cpp"


#define CHECK_CONNECTION_EXISTS true

class neat
{
private:
	std::mt19937* mersenne_engine;
	//std::vector<neuron> neurons;
	//std::vector<connection> connections;
	std::map< std::pair<int, int>, connection > connections_map; //<neuron0 gid, neuron1 gid> -> <connection>
	std::map< int, neuron > neurons_map; //<neuron gid, neuron>

	std::vector<neuron*> input_output_neurons;
public:
	neat();
	neat(const neat& n);
	neat(std::mt19937* meng, int inpLen, int outLen);
	neat(std::mt19937* meng, int inpLen, int outLen, global_id* gid, config* cfg);
	const int inpLen;
	const int outLen;

	//Add a neuron/connection. Disable neuron/connection. Or do nothing
	void mutate(global_id* gid, config* cfg);
	//friend Mesh mate(Mesh* m0, Mesh* m1, std::mt19937* meng);
	friend void mate(neat* nte, const neat& n1, const neat& n2, global_id* gid, config* cfg);
	neat& operator=(const neat& nte);
	friend std::ostream& operator<<(std::ostream& os, neat& n);
	friend std::ostream& operator<<(std::ostream& os, std::map< std::pair<int, int>, connection >& cmap);
	friend std::ostream& operator<<(std::ostream& os, std::map< int, neuron >& nmap);

	void addNeuron(std::map< int, neuron >* new_nmap, std::map< std::pair<int, int>, connection >* new_cmap, connection* c, global_id* gid, config* cfg); //always add a neuron
	bool addConnection(std::map< std::pair<int, int>, connection >* new_cmap, global_id* gid, int n0, int n1); //add a connection if that connection doesn't exist yet
	void addConnection_NoCheck(std::map< std::pair<int, int>, connection >* new_cmap, global_id* gid, int n0, int n1);


	void prep(); //store neuron references in connections for running the network multiple times
	void activate(std::vector<float>* inp, std::vector<float>* outp); //run network



};

template <typename T>
void addToMap(std::map<int, neuron>* m, const neuron* data, std::mt19937* meng);
void addToMap(std::map<int, const connection*>* m, std::map< std::pair<int, int>, const connection* >* connections_map, int id, const connection* data, std::mt19937* meng);


void fillMap(std::map<int, neuron>* new_neurons, const std::map<int, neuron>* old_neurons0, const std::map<int, neuron>* old_neurons1, std::mt19937* meng);
void fillMap(std::map< std::pair<int, int>, connection >* new_connections, const std::map< std::pair<int, int>, connection >* old_connections0, const std::map< std::pair<int, int>, connection >* old_connections1, std::map< int, neuron >* new_neurons, std::mt19937* meng);



bool checkMap(std::map<int, const neuron*>* nns, const connection* c);

