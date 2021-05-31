#pragma once
#include <iostream>
#include <iomanip>
#include <future>
#include "vectorRandom.cpp"
#include "Mesh.h"
#include "global_id.h"

int sel(std::vector<float>* s, int qty);



//template void genAlg<std::string>(const std::string&);
template <typename T>
inline int genAlg(std::vector<T>* m, float (*fitness)(T*), bool speciation, float speciationThresh, int popLen, int numGens, int tournamentSize)
{
    //TODO: Speciation
    std::vector<T> m_child(popLen);
    std::vector<float> s(popLen);
    int a, b, x, maxScoreID = 0;
    float maxScore, fl;
    for (int y = 0; y < numGens; y++)
    {
        maxScore = -INFINITY;
        maxScoreID = 0;

        for (x = 0; x < popLen; x++)
        {
            fl = fitness(&((*m)[x]));
            if (fl > maxScore)
            {
                maxScore = fl;
                maxScoreID = x;
            }
            s[x] = fl;
        }

        //speciate scores here

        for (x = 0; x < popLen; x++)
        {

            a = 0; b = 0;
            while (a == b)
            {
                a = sel(&s, tournamentSize); b = sel(&s, tournamentSize);
            }

            m_child[x] = (*m)[a].mate(&((*m)[b]));
        }
        *m = m_child;
        std::cout << std::setw(5) << maxScore << "\n";

    }
    return maxScoreID;
}

template <typename T>
inline float makeChild(global_id* gid, int x, int tournamentSize, std::vector<T>* m_child, std::vector<T>* m, std::vector<float>* s)
{
    int a = 0;
    int b = 0;
    while (a == b)
    {
        a = sel(s, tournamentSize); b = sel(s, tournamentSize);
    }

    (*m_child)[x] = (*m)[a].mate(&((*m)[b]));
    return 0;
}

template <typename T>
inline int genAlgAsync(std::vector<T>* m, float (*fitness)(T*), bool speciation, float speciationThresh, int popLen, int numGens, int tournamentSize)
{
    //TODO: Speciation, Novelty Search
    std::vector<T> m_child(popLen);
    std::vector<float> s(popLen);
    int a, b, x, maxScoreID = 0;
    float maxScore, fl;
    std::vector<std::future<float>> selVect(popLen);

    // gid(<x, y, pre-a, post-a>, <connectionBool, weight>)
    global_id gid(4,2);


    for (int y = 0; y < numGens; y++)
    {
        maxScore = -INFINITY;
        maxScoreID = 0;
        //start async fitness operations
        for (x = 0; x < popLen; x++)
        {
            selVect[x] = std::async(fitness, &((*m)[x]));
        }
        //get fitness results and save max value
        for (x = 0; x < popLen; x++)
        {
            s[x] = selVect[x].get();
            if (s[x] > maxScore)
            {
                maxScore = s[x];
                maxScoreID = x;
            }
        }
        //TODO: speciate scores here


        //\\
        \\//
        //\\
        \\//
        //\\
        \\// 

        //TODO: Novelty search option


        //\\
        \\//
        //\\
        \\//
        //\\
        \\// 


        //Harmonic mean of fitness and novelty fitness?

        //TODO: pass global_id object into makeChild<T> and mate()

        //start async crossovers
        for (x = 0; x < popLen; x++)
        {
            //makeChild(&gid, x, tournamentSize, &m_child, m, &s);
            selVect[x] = std::async(makeChild<T>, &gid, x, tournamentSize, &m_child, m, &s);
        }
        //wait for async crossovers
        for (x = 0; x < popLen; x++)
        {
            selVect[x].wait();
        }
        //replace current population with child population
        *m = m_child;
        //print out max score
        std::cout << std::setw(5) << maxScore << "\n";

    }
    return maxScoreID;
}