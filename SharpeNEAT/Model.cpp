#include "Model.h"
std::ostream& operator<<(std::ostream& os, Model& m)
{
	os << "Model object\n";
	os << m.msh << "\n";
	os << m.neuron_net << "\n";
	os << m.conn_net << "\n";
	return os;
}
Model::Model()
{

}
Model::Model(int inpLen, int outLen, int meshDim, std::mt19937* meng, global_id* gid, config* cfg)
{
	//neuron_net shape : {inpLen: dim + 2, outLen: 3}
	//conn_net shape : {inpLen: 2*(dim + 2), outLen: 2}
	
	neuron_net = neat(meng, meshDim + 2, 3, gid, cfg);
	conn_net = neat(meng, 2 * (meshDim + 2), 2, gid, cfg);
	msh = Mesh(meng, meshDim, inpLen, outLen, cfg->maxMeshStartingPoints, cfg->minMeshVal, cfg->maxMeshVal);
}
void mate(Model* m_new, const Model& m0, const Model& m1, global_id* gid, config* cfg, std::mt19937* meng)
{
	//global_id* gid, config* cfg
	//mate(const neat& n1, const neat& n2, global_id* gid, config* cfg);
	//void mate(Mesh* m, const Mesh& m0, const Mesh& m1, std::mt19937* meng, config* cfg);
	mate(&(m_new->msh), (m0.msh), (m1.msh), meng, cfg);
	mate(&(m_new->neuron_net), (m0.neuron_net), (m1.neuron_net), gid, cfg);
	mate(&(m_new->conn_net), (m0.conn_net), (m1.conn_net), gid, cfg);
	//neat n4 = mate(n2, n3, &gid, &cfg);
}

void Model::build()
{
	neural_network.build(&msh, &neuron_net, &conn_net);
}

void Model::activate(std::vector<float>* inp, std::vector<float>* outp)
{

}