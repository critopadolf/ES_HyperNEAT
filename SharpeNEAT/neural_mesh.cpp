#include "neural_mesh.h"
neural_mesh::neural_mesh()
{
	//neuron_vals = std::vector < std::pair<double, double> >(0, std::make_pair(0.0, 0.0));
}
void neural_mesh::build(Mesh* msh, neat* neuron_net, neat* conn_net)
{
	//neuron net queries a position on the mesh and gives it a bias and activation function
	//connection net queries two positions on the mesh and determines whether a connection exists between them
	
	//neuron_net shape : {inpLen: dim + 2, outLen: 3}
	//conn_net shape : {inpLen: 2*(dim + 2), outLen: 2}

	int mshSize = msh->size();
	int dim = msh->dimSize();
	neurons = std::vector<neuron>(mshSize);

	std::vector<std::vector<float>> inputs(mshSize);
	
	
	for (int x = 0; x < mshSize; x++)
	{
		for (int y = 0; y < mshSize; y++)
		{
			if (x == 0)
			{
				std::vector<float> neuron_class(neuron_net->outLen);
				get_neuron_input(&inputs, msh, dim, y);
				//run input through neuron network
				neuron_net->activate(&(inputs[y]), &neuron_class);
				//add new neuron
				addNeuron(&neuron_class, y);
			}
			std::vector<float> connection_class(conn_net->outLen);
			std::vector<float> connection_input = inputs[x];
			extend(&connection_input, &(inputs[y]));
			conn_net->activate(&connection_input, &connection_class);
			//if first element of connection_class > 0.5, add a new connection with references to neurons x and y
			addConnection(&connection_class, x, y);
		}
	}

}

void neural_mesh::addNeuron(std::vector<float>* n_class, int y)
{
	if ((*n_class)[0] < 0.5)
		return;
	//neuron(float bias_fl, float activation_fl, int id_fl)
	neurons.push_back(neuron((*n_class)[1], (*n_class)[2], y));
}

void neural_mesh::addConnection(std::vector<float>* c_class, int x, int y)
{
	if ((*c_class)[0] < 0.5)
		return;
	//connection(float weight, int n0, int n1)
	connections.push_back(connection((*c_class)[1], x, y));
}
void neural_mesh::get_neuron_input(std::vector<std::vector<float>>* inputs, Mesh* msh, int dim, int x)
{
	//get inputs for neuron network
	(*inputs)[x] = std::vector<float>(2 + dim);
	point_t* pt = &(*msh)[x];
	for (int i = 0; i < dim; i++)
	{
		//assign mesh point to input x
		(*inputs)[x][i] = (*pt)[i];
	}
	if (x >= neuron_vals.size())
	{
		//assign default neuron_values to input x
		(*inputs)[x][dim] = 0;
		(*inputs)[x][dim + 1] = 0;
	}
	else
	{
		//assign past neuron values to input x
		(*inputs)[x][dim] = neuron_vals[x].first;
		(*inputs)[x][dim + 1] = neuron_vals[x].second;
	}
}

void neural_mesh::destroy()
{
	neuron_vals.clear();
	neurons.clear();
	connections.clear();
}


void neural_mesh::activate(std::vector<float>* inp, std::vector<float>* out)
{

}