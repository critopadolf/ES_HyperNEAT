

#include <iostream>
#include <iomanip>
#include "genAlg.h"
#include "Model.h"



float fit(Mesh* m)
{
    std::vector<point_t>* pts = m->getHidden();
    float score = 100;
    std::vector<point_t> des = { { 0, 0 }, {0, 1}, {1, 0}, {1, 1} };
    int dif = des.size() - pts->size();

    for (int x = 0; x < pts->size(); x++)
    {
        point_t pt;
        if (x < 4)
        {
            pt = des[x] - (*pts)[x];
            score -= magSq(pt);
        }
        else
        {
            score -= 100;
        }
    }
    for (int y = 0; y < dif; y++)
    {
        score -= 100;
    }

    return score;
}
/*
void runGenAlg()
{
    // tries to get a mesh with hidden verts: { { 0, 0 }, {0, 1}, {1, 0}, {1, 1} } (square)
    int popLen = 40;
    int numGens = 500;
    int tournamentSize = 5;

    float newPointRate = 0.2;
    float removePointRate = 0.2;
    float mutatePointRate = 0.1;


    std::vector<Mesh> m(popLen);

    int dim = 2;
    int inpLen = 2;
    int outLen = 2;
    int startHidden = 5;

    for (int x = 0; x < popLen; x++)
    {
        m[x] = Mesh(dim, inpLen, outLen, startHidden);
    }

    //TODO: Implement Speciation (use subtraction operator)
    bool speciation = false;
    float speciationThresh = 0;

    int maxScoreIndex = genAlgAsync(&m, fit, speciation, speciationThresh, popLen, numGens, tournamentSize);
    std::cout << m[maxScoreIndex] << "done_\n";
}
*/
//https://gieseanw.wordpress.com/2017/05/03/a-true-heterogeneous-container-in-c/
//typedef std::vector< std::shared_ptr<Layer> > layer_list;
int main()
{
    //runGenAlg();
    //std::mt19937* meng, int inpLen, int outLen, global_id* gid
    std::random_device rnd_device;
    std::mt19937 meng{ rnd_device() };
    int inpLen = 5;
    int outLen = 4;
    int dim = 2;
    global_id gid(inpLen, outLen);

    //NEAT
    float newNeuronRate = 0.025,
        newConnectionRate = 0.1,
        deleteNeuronRate = 0.01,
        deleteConnectionRate = 0.01,
        mutateWeightRate = 0.001;

    float maxWeight = 2,
        minWeight = -2;

    //MESH
    float newPointRate = 0.001,
        removePointRate = 0.001,
        mutatePointRate = 0.01;

    int maxMeshStartingPoints = 50;
    float minMeshVal = -2,
          maxMeshVal =  2;
    

    config cfg(newNeuronRate, newConnectionRate, deleteNeuronRate, deleteConnectionRate, mutateWeightRate, newPointRate, removePointRate, mutatePointRate, maxMeshStartingPoints, maxMeshVal, minMeshVal, maxWeight, minWeight);

    Model mod0(inpLen, outLen, dim, &meng, &gid, &cfg);
    Model mod1(inpLen, outLen, dim, &meng, &gid, &cfg);
    Model mod;
    mate(&mod, mod0, mod1, &gid, &cfg, &meng);
    std::cout << mod0 << mod1 << mod;
}

