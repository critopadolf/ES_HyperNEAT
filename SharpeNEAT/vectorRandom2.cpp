#pragma once
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
typedef std::vector<float>(*funcInp)(std::vector<float>);
//fill a vector with random elements (bool, int, float)
template <typename T>
inline void fillVector(T* vec, std::mt19937* mersenne_engine, float RangeStart, float RangeEnd)
{

    //using T0 = typename std::decay<decltype(*vec.begin())>::type;
    typename T::value_type type;
    if (typeid(type) == typeid(bool))
    {
        std::uniform_int_distribution<int> dist{ 0, 1 };
        auto gen = [&dist, mersenne_engine]() {
            return dist(*mersenne_engine);
        };
        std::generate(begin(*vec), end(*vec), gen);
    }
    else if (typeid(type) == typeid(int))
    {
        std::uniform_int_distribution<int> dist{ (int)RangeStart, (int)RangeEnd };
        auto gen = [&dist, mersenne_engine]() {
            return dist(*mersenne_engine);
        };
        std::generate(begin(*vec), end(*vec), gen);
    }
    else if (typeid(type) == typeid(float))
    {
        std::uniform_real_distribution<float> dist{ RangeStart, RangeEnd };
        auto gen = [&dist, mersenne_engine]() {
            return dist(*mersenne_engine);
        };
        std::generate(begin(*vec), end(*vec), gen);
    }
    else if (typeid(type) == typeid(double))
    {
        std::uniform_real_distribution<double> dist{ RangeStart, RangeEnd };
        auto gen = [&dist, mersenne_engine]() {
            return dist(*mersenne_engine);
        };
        std::generate(begin(*vec), end(*vec), gen);
    }

}
//fill a 2D vector with random elements (bool, int, float)
template <typename T>
inline void fill2DVector(T* vec, std::mt19937* mersenne_engine, int len, float RangeStart, float RangeEnd)
{
    auto gen = [mersenne_engine, &RangeStart, &RangeEnd, &len]() {
        typename T::value_type v(len);
        fillVector(&v, mersenne_engine, RangeStart, RangeEnd);
        return v;
    };
    std::generate(begin(*vec), end(*vec), gen);
}

/*
// C++ template to print vector container elements 
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}
*/
/*
//pick a random index from the input vector, excluding zeros
template <typename T>
inline int pickRandomOne(T* vec, std::mt19937* mersenne_engine)
{
    int len = (*vec).size();
    std::vector<int> o(len);
    int x = 0;
    int y = 0;
    for (typename T::value_type v : *vec)
    {
        if (v)
        {
            o[y] = x;
            y++;
        }
        x++;
    }
    y--;
    if (y < 0)
        return -1;
    std::uniform_int_distribution<int> dist{ 0, y };
    return o[dist(*mersenne_engine)];
}
//pick random index from vector
template <typename T>
inline int pickRand(T* vec, std::mt19937* mersenne_engine)
{
    std::uniform_int_distribution<int> dist{ 0, (int)((*vec).size() - 1) };
    return dist(*mersenne_engine);
}
//create random var
template <typename T>
inline T my_rand(std::mt19937* mersenne_engine, T RangeStart, T RangeEnd)
{
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };
    //typename T::value_type type;
    if (typeid(T) == typeid(bool))
    {
        std::uniform_int_distribution<int> dist{ 0, 1 };
        return dist(*mersenne_engine);
    }
    else if (typeid(T) == typeid(int))
    {
        std::uniform_int_distribution<int> dist{ (int)RangeStart, (int)RangeEnd };
        return dist(*mersenne_engine);
    }
    else if (typeid(T) == typeid(float))
    {
        //float tmp = RangeEnd - RangeStart;
        std::uniform_real_distribution<float> dist{ (float)RangeStart, (float)RangeEnd };
        return dist(*mersenne_engine);
    }
    else
    {
        return 0;
    }
}
*/

inline float randfloat(std::mt19937* mersenne_engine, float RangeStart, float RangeEnd)
{
    std::uniform_real_distribution<float> dist{ RangeStart, RangeEnd };
    return dist(*mersenne_engine);
}

inline double randDouble(std::mt19937* mersenne_engine, double RangeStart, double RangeEnd)
{
    std::uniform_real_distribution<double> dist{ RangeStart, RangeEnd };
    return dist(*mersenne_engine);
}
inline int randInt(std::mt19937* mersenne_engine, int RangeStart, int RangeEnd)
{
    std::uniform_int_distribution<int> dist{ RangeStart, RangeEnd };
    return dist(*mersenne_engine);
}

//mutate an int using a binomial distribution
inline void mutateInt(int* i, std::mt19937* mersenne_engine, int RangeStart, int RangeEnd)
{
    int range = RangeEnd - RangeStart;
    std::binomial_distribution<> dist{ range,0.5 };
    int di = dist(*mersenne_engine);
    //std::cout << di << "\n";
    int k = *i + (di - (int)(0.5 * range));
    if (k <= RangeEnd && k >= RangeStart)
    {
        *i = k;
    }

}
/*
//mutate elements of an int vector if my_rand < p (for each element)
inline void mutateIntVec(std::vector<int>* vec, std::mt19937* mersenne_engine, int RangeStart, int RangeEnd, float p)
{
    std::for_each((*vec).begin(), (*vec).end(), [mersenne_engine, &RangeStart, &RangeEnd, &p](int& n) {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        if (r < p)
        {
            mutateInt(&n, mersenne_engine, RangeStart, RangeEnd);
        }
        });
}
//invert elements of a bool vector if my_rand < p (for each element)
inline void mutateBoolVec(std::vector<bool>* vec, std::mt19937* mersenne_engine, float p)
{
    for (auto i = vec->begin(); i != vec->end(); ++i)
    {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        if (r < p)
        {
            *i = !*i;
        }
    }

}
*/
//mutate float by ref using a normal distribution
template <typename T>
inline void mutateFloat(T* i, std::mt19937* mersenne_engine, T RangeStart, T RangeEnd, T std_dev)
{
    T range = RangeEnd - RangeStart;
    std::normal_distribution<> dist{ 0, std_dev };
    T di = dist(*mersenne_engine);
    //std::cout << di << "\n";
    T k = *i + di;
    if (k <= RangeEnd && k >= RangeStart)
    {
        *i = k;
    }
}
/*
//mutate elements of a float vector
inline void mutateFloatVector(std::vector<float>* vec, std::mt19937* mersenne_engine, float RangeStart, float RangeEnd, float p, float std_dev)
{
    std::for_each((*vec).begin(), (*vec).end(), [mersenne_engine, &RangeStart, &RangeEnd, &p, &std_dev](float& n) {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        if (r < p)
        {
            mutateFloat(&n, mersenne_engine, RangeStart, RangeEnd, std_dev);
        }
        });
}
template <typename T>
inline void mutate(T* i, std::mt19937* mersenne_engine, float RangeStart, float RangeEnd, float std_dev)
{
    float range = RangeEnd - RangeStart;
    std::normal_distribution<> dist{ 0, std_dev };
    float di = dist(*mersenne_engine);
    //std::cout << di << "\n";
    T k = *i + (T)di;
    if (k <= RangeEnd && k >= RangeStart)
    {
        *i = k;
    }
}
//mutate int or float vec with given std deviation, cast to type
template <typename T>
inline void mutateVec(T* vec, std::mt19937* mersenne_engine, float RangeStart, float RangeEnd, float p, float std_dev)
{
    std::for_each((*vec).begin(), (*vec).end(), [mersenne_engine, &RangeStart, &RangeEnd, &p, &std_dev](typename T::value_type& n) {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        if (r < p)
        {
            mutate(&n, mersenne_engine, RangeStart, RangeEnd, std_dev);
        }
        });
}
template <typename T>
inline T vCrossOver(T* v1, T* v2, std::mt19937* mersenne_engine)
{
    int x = 0;
    T vo;
    for (auto i = v1->begin(); i != v1->end(); ++i)
    {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        vo.push_back(((*v1)[x] * (r < 0.5)) + ((*v2)[x] * (r >= 0.5)));
        x++;
    }
    return vo;
}
*/
template <typename T>
inline T vCrossOver_disjointed(T* v1, T* v2, std::mt19937* mersenne_engine)
{
    bool b = v1->size() < v2->size();
    int loopto1 = v1->size() * b + v2->size() * (!b);
    int loopto2 = v1->size() * (!b) + v2->size() * (b);
    T* ref = v1;
    if (b)
        ref = v2;
    T vo(loopto2);
    int i;
    for (i = 0; i < loopto1; i++)
    {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        vo[i] = (((*v1)[i] * (r < 0.5)) + ((*v2)[i] * (r >= 0.5)));
    }

    for (i = loopto1; i < loopto2; i++)
    {
        vo[i] = ((*ref)[i]);
    }

    return vo;
}
template <typename T>
inline void vCrossOver_disjointed(T* v0, const T* v1, const T* v2, std::mt19937* mersenne_engine)
{
    bool b = v1->size() < v2->size();
    int loopto1 = v1->size() * b + v2->size() * (!b);
    int loopto2 = v1->size() * (!b) + v2->size() * (b);
    const T* ref = v1;
    if (b)
        ref = v2;
    *v0 = T(loopto2);
    int i;
    for (i = 0; i < loopto1; i++)
    {
        float r = randfloat(mersenne_engine, 0.0, 1.0);
        (*v0)[i] = (((*v1)[i] * (r < 0.5)) + ((*v2)[i] * (r >= 0.5)));
    }

    for (i = loopto1; i < loopto2; i++)
    {
        (*v0)[i] = ((*ref)[i]);
    }
}
/*
//fill an x vector with random points from the given range
//fill the y vector with the function values from that x vector
inline void fill2DVectorWithFunc(std::vector<std::vector<float>>* vx, std::vector<std::vector<float>>* vy, funcInp f, std::mt19937* mersenne_engine, int n, float RangeStart, float RangeEnd)
{
    fill2DVector(vx, mersenne_engine, n, RangeStart, RangeEnd);
    for (int x = 0; x < vx->size(); x++)
    {
        (*vy)[x] = f((*vx)[x]);
    }
}
//takes in a matrix and returns a vector where 0's mean that the given column index is entirely zeroes
template <typename T>
inline std::vector<bool>  findZeroColumns(T* vx)
{
    std::vector<bool> zeroCols((*vx)[0].size(), 0);
    for (int i = 0; i < (*vx).size(); i++)
    {
        for (int j = 0; j < (*vx)[i].size(); j++)
        {
            zeroCols[j] = zeroCols[j] || (*vx)[i][j];
        }
    }

    return zeroCols;
}
*/