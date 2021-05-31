#include "Model.h"
std::ostream& operator<<(std::ostream& os, Model& m)
{
	os << "Model object\n";
	os << m.msh << "\n";
	os << m.prenet << "\n";
	return os;
}
Model::Model()
{

}
Model::Model(int inpLen, int outLen, int meshDim, std::mt19937* meng, global_id* gid, config* cfg)
{
	prenet = neat(meng, inpLen, outLen, gid, cfg);
	msh = Mesh(meng, meshDim, inpLen, outLen, cfg->maxMeshStartingPoints, cfg->minMeshVal, cfg->maxMeshVal);
}
void mate(Model* m_new, const Model& m0, const Model& m1, global_id* gid, config* cfg, std::mt19937* meng)
{
	//global_id* gid, config* cfg
	//mate(const neat& n1, const neat& n2, global_id* gid, config* cfg);
	//void mate(Mesh* m, const Mesh& m0, const Mesh& m1, std::mt19937* meng, config* cfg);
	mate(&(m_new->msh), (m0.msh), (m1.msh), meng, cfg);
	mate(&(m_new->prenet), (m0.prenet), (m1.prenet), gid, cfg);
	//neat n4 = mate(n2, n3, &gid, &cfg);
}