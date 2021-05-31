#include "neat.h"
neat::neat() : inpLen(0), outLen(0)
{}
neat::neat(std::mt19937* meng, int inpLen, int outLen) : mersenne_engine(meng), inpLen(inpLen), outLen(outLen)
{}
neat::neat(const neat& n) : inpLen(n.inpLen), outLen(n.outLen)
{
	neurons_map = n.neurons_map;
	connections_map = n.connections_map;
	mersenne_engine = n.mersenne_engine;
}
neat& neat::operator=(const neat& nte)
{
	neurons_map = nte.neurons_map;
	connections_map = nte.connections_map;
	mersenne_engine = nte.mersenne_engine;
	return *this;
}
neat::neat(std::mt19937* meng, int inpLen, int outLen, global_id* gid, config* cfg) :
	inpLen(inpLen), outLen(outLen)
{
	mersenne_engine = meng;

	int x, y;
	int tot = inpLen + outLen;
	//neurons = std::vector<neuron>(tot);
	for (x = 0; x < tot; x++)
	{
		neurons_map[x] = neuron(meng, x, cfg);
	}

	int t = 0;
	int totC = inpLen * outLen;
	//connections = std::vector<connection>(totC);
	for (x = 0; x < inpLen; x++)
	{
		for (y = inpLen; y < tot; y++)
		{
			connections_map[std::make_pair(x, y)] = connection(gid, x, y, meng);
			t++;
		}
	}
}

std::ostream& operator<<(std::ostream& os, std::map< std::pair<int, int>, connection >& cmap)
{
	for (auto it = cmap.begin(); it != cmap.end(); it++)
	{
		std::cout << it->second;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, std::map< int, neuron >& nmap)
{
	for (auto it = nmap.begin(); it != nmap.end(); it++)
	{
		std::cout << it->second;
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, neat& n)
{
	os << "neurons: " << n.neurons_map << "\n";
	os << "connections: " << n.connections_map << "\n";
	return os;
}


void addToMap(std::map<int, neuron>* m, const neuron* data, std::mt19937* meng)
{
	auto k = m->find(data->id);
	if (k == m->end() || randfloat(meng, 0, 1) < 0.5)
	{
		//if this item exists in the map, then add with coinflip
		//otherwise if it doesn't exist in the map, add it
		(*m)[data->id] = *data;
	}
}
void addToMap(std::map< std::pair<int, int>, connection >* new_connections, const connection* data, std::mt19937* meng)
{
	std::pair<int, int> id_pair = std::make_pair(data->ng[0], data->ng[1]);
	auto k = new_connections->find(id_pair);
	if (k == new_connections->end() || randfloat(meng, 0, 1) < 0.5)
	{
		//if this item exists in the map, then add with coinflip
		//otherwise if it doesn't exist in the map, add it
		(*new_connections)[id_pair] = *data;
	}

}

void fillMap(std::map<int, neuron>* new_neurons, const std::map<int, neuron>* old_neurons0, const std::map<int, neuron>* old_neurons1, std::mt19937* meng)
{
	//sort pointers old_neurons0 and old_neurons1 by length
	auto tmp = old_neurons1;
	int x;
	if (old_neurons0->size() > old_neurons1->size())
	{
		old_neurons1 = old_neurons0;
		old_neurons0 = tmp;
	}
	auto it0 = old_neurons0->begin();
	auto it1 = old_neurons1->begin();
	//iterate over both maps at once, adding their elements to the new_neurons map
	//addToMap addresses conflicts with a coin flip
	for (x = 0; x < old_neurons0->size(); x++)
	{
		//void addToMap(std::map<int, neuron>* m, const neuron* data, std::mt19937* meng)
		addToMap(new_neurons, &(it0->second), meng);
		addToMap(new_neurons, &(it1->second), meng);

		it0++; it1++;
	}
	for (x = old_neurons0->size(); x < old_neurons1->size(); x++)
	{
		addToMap(new_neurons, &(it1->second), meng);
		it1++;
	}
}

bool checkMap(std::map< int, neuron >* nns, const connection* c)
{
	//check if the connections neurons exist in the new child network
	auto n0r = nns->find(c->ng[0]);
	auto n1r = nns->find(c->ng[1]);
	if (n0r == nns->end() || n1r == nns->end())
	{
		return false;
	}
	return true;
}


void fillMap(std::map< std::pair<int, int>, connection >* new_connections, const std::map< std::pair<int, int>, connection >* old_connections0, const std::map< std::pair<int, int>, connection >* old_connections1, std::map< int, neuron >* new_neurons, std::mt19937* meng)
{
	auto tmp = old_connections1;
	int id;
	int x;
	if (old_connections0->size() > old_connections1->size())
	{
		old_connections1 = old_connections0;
		old_connections0 = tmp;
	}
	auto it0 = old_connections0->begin();
	auto it1 = old_connections1->begin();
	for (x = 0; x < old_connections0->size(); x++)
	{
		//add new connections to map, if their respective neurons global id's exist within new_neurons
		if(checkMap(new_neurons, &(it0->second)))
			addToMap(new_connections, &(it0->second), meng);
		if (checkMap(new_neurons, &(it1->second)))
			addToMap(new_connections, &(it1->second), meng);

		it0++; it1++;
	}
	for (x = old_connections0->size(); x < old_connections1->size(); x++)
	{
		if (checkMap(new_neurons, &(it1->second)))
			addToMap(new_connections, &(it1->second), meng);
		it1++;
	}
}


void neat::mutate( global_id* gid, config* cfg )
{
	std::map< std::pair<int, int>, connection > new_cmap;// = connections_map;
	std::map< int, neuron > new_nmap;// = neurons_map;

	//Add a neuron/connection. Disable neuron/connection. Or do nothing
	float r;
	int lng = inpLen + outLen;
	auto itx = neurons_map.begin(); auto ity = neurons_map.begin();
	std::vector< std::map< std::pair<int, int>, connection >::iterator> conns_to_delete;
	std::vector< std::map< int, neuron >::iterator > neurons_to_delete;
	//mark connections for deletion
	for (auto itc = connections_map.begin(); itc != connections_map.end(); itc++)
	{
		r = randfloat(mersenne_engine, 0, 1);
		if (r > cfg->deleteConnectionRate)
		{
			//add connection to new_cmap
			r = randfloat(mersenne_engine, 0, 1);
			itc->second.mutate(mersenne_engine, cfg); //mutate original
			new_cmap[itc->first] = itc->second; //copy original
		}
		else
		{
			//erase connection from connections_map
			conns_to_delete.push_back(itc);
		}
	}
	//mark neurons for deletion
	for (itx = neurons_map.begin(); itx != neurons_map.end(); itx++)
	{
		r = randfloat(mersenne_engine, 0, 1);
		if (itx->second.getID() < lng || r > cfg->deleteNeuronRate)
		{
			//add neuron to new_nmap if it is an input or output neuron, or it isn't rolled to be deleted
			itx->second.mutate(mersenne_engine, cfg); //mutate original
			new_nmap[itx->first] = itx->second; //copy original
		}
		else
		{
			//erase neuron from neurons_map
			neurons_to_delete.push_back(itx);
		}
	}

	//actually delete connections from original map
	for (auto k : conns_to_delete)
	{
		connections_map.erase(k);
	}
	for (auto k : neurons_to_delete)
	{
		neurons_map.erase(k);
	}

	//mutate add new neurons
	for (auto itc = connections_map.begin(); itc != connections_map.end(); itc++)
	{
		r = randfloat(mersenne_engine, 0, 1);
		if (r < cfg->newNeuronRate)
		{
			addNeuron(&new_nmap, &new_cmap, &(itc->second), gid, cfg);
		}
	}
	
	//Mutate, add new connections
	for (itx = neurons_map.begin(); itx != neurons_map.end(); itx++)
	{
		for (ity = neurons_map.begin(); ity != neurons_map.end(); ity++)
		{
			r = randfloat(mersenne_engine, 0, 1);
			if (r < cfg->newConnectionRate)
			{
				//std::cout << itx->second.getID() << " -> " << ity->second.getID() << " : " << addConnection(gid, itx->second.getID(), ity->second.getID()) << std::endl;
				addConnection(&new_cmap, gid, itx->second.getID(), ity->second.getID());
			}
		}
	}

	//replace old maps with new maps
	connections_map = new_cmap;
	neurons_map = new_nmap;

}


void neat::addNeuron(std::map< int, neuron >* new_nmap, std::map< std::pair<int, int>, connection >* new_cmap, connection* c, global_id* gid, config* cfg)
{
	//(std::mt19937* mersenne_engine, global_id* gid, int c);
	neuron n(mersenne_engine, gid, c->cg, cfg);
	(*new_nmap)[n.getID()] = n;
	addConnection_NoCheck(new_cmap, gid, c->getN(0), n.getID());
	addConnection_NoCheck(new_cmap, gid, n.getID(), c->getN(1));
	c->disable();
		
}
void neat::addConnection_NoCheck(std::map< std::pair<int, int>, connection >* new_cmap, global_id* gid, int n0, int n1)
{
	(*new_cmap)[std::make_pair(n0, n1)] = connection(gid, n0, n1, mersenne_engine);
}

bool neat::addConnection(std::map< std::pair<int, int>, connection >* new_cmap, global_id* gid, int n0, int n1)
{
	std::pair<int, int> mk = std::make_pair(n0, n1);
#if CHECK_CONNECTION_EXISTS
	//does connection exist? //getting rid of this check may speed things up
	auto k = connections_map.find(mk);
	if (k != connections_map.end())
		return false;	
#endif

	//add connection from neuron A to neuron B
	(*new_cmap)[mk] = connection(gid, n0, n1, mersenne_engine);
	
	return true;
}
void mate(neat* nte, const neat& n1, const neat& n2, global_id* gid, config* cfg)
{
	//use neat constructor which doesn't instantiate the input/output neurons and connections
	*nte = neat(n1.mersenne_engine, n1.inpLen, n2.outLen);
	fillMap(&(nte->neurons_map), &(n1.neurons_map), &(n2.neurons_map), n1.mersenne_engine);
	fillMap(&(nte->connections_map), &(n1.connections_map), &(n2.connections_map), &(nte->neurons_map), nte->mersenne_engine);
	nte->mutate(gid, cfg);
	nte->prep();
}



void neat::prep() //store neuron references in connections for running the network multiple times
{
	//find references to input/output neurons
	input_output_neurons = std::vector<neuron*>(inpLen + outLen);
	for (auto itx = neurons_map.begin(); itx != neurons_map.end(); itx++)
	{
		if (itx->second.getID() < input_output_neurons.size())
		{
			
			itx->second.setInp(); //set this neuron as input/output
			input_output_neurons[itx->second.getID()] = &(itx->second);
		}
	}
	//add neuron references to connections, delete connections that use neurons that don't exist
	std::vector< std::map< std::pair<int, int>, connection >::iterator> conns_to_delete;
	for (auto itc = connections_map.begin(); itc != connections_map.end(); itc++)
	{
		auto n0 = neurons_map.find(itc->second.getN(0));
		auto n1 = neurons_map.find(itc->second.getN(1));
		if (n0 != neurons_map.end() && n1 != neurons_map.end())
		{
			itc->second.setRef(&(n0->second), &(n1->second));
		}
		else
		{
			conns_to_delete.push_back(itc);
		}
	}
	for (auto k : conns_to_delete)
	{
		connections_map.erase(k);
	}
}

void neat::activate(std::vector<float>* inp, std::vector<float>* outp) //run network
{
	//load values into input neurons
	for (int x = 0; x < inpLen; x++)
	{
		input_output_neurons[x]->set((*inp)[x]);
	}

	
	for (int x = 0; x < 1; x++)
	{
		//load neuron activation value into connections
		for (auto itc = connections_map.begin(); itc != connections_map.end(); itc++)
		{
			float neuron_val = itc->second.getNref(0)->activate();
			itc->second.load(neuron_val);
		}

		//load connection values into neurons
		for (auto itc = connections_map.begin(); itc != connections_map.end(); itc++)
		{
			float connection_val = itc->second.getVal() * itc->second.getWeight();
			itc->second.getNref(1)->load(connection_val); //load connection value int second neuron
			itc->second.load(0); //reset connection value to zero
		}
	}

	//repeat
	

	//load values from output neurons
	for (int x = 0; x < outLen; x++)
	{
		(*outp)[x] = input_output_neurons[x + inpLen]->activate();
	}


}