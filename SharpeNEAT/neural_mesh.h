#pragma once
#include "neat.h"
#include "Mesh.h"

class neural_mesh
{
public:
	neural_mesh();
	void activate(std::vector<float>* inp, std::vector<float>* out);
	//build the model
	//neuron net queries a position on the mesh and gives it a bias and activation function
	//connection net queries two positions on the mesh and determines whether a connection exists between them
	void build(Mesh* msh, neat* neuron_net, neat* conn_net);
	//after this network receives a fitness score, destroy it by clearing neurons, neuron_vals, and connections
	void destroy();
private:
	std::vector<neuron> neurons;
	std::vector < std::pair<float, float> > neuron_vals;
	std::vector<connection> connections;

	void get_neuron_input(std::vector<std::vector<float>>* inputs, Mesh* msh, int dim, int x);
	void addNeuron(std::vector<float>* n_class, int y);
	void addConnection(std::vector<float>* c_class, int x, int y);
};

