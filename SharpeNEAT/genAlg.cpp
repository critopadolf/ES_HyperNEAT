#include "genAlg.h"

int sel(std::vector<float>* s, int qty)
{
    float max = 0;
    int maxI = 0;
    for (int x = 0; x < qty; x++)
    {
        int k = randInt(0, s->size() - 1);
        float ts = (*s)[k];
        if (ts > max)
        {
            max = ts;
            maxI = k;
        }
    }
    return maxI;
}





