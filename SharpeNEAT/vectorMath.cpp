#pragma once
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <vector>
template <typename T>
std::vector<T> operator+(const std::vector<T>& v0, const std::vector<T>& v1)
{
    std::vector<T> v = std::vector<T>(v0.size());
    for (int i = 0; i < v0.size(); ++i) 
    {
        v[i] = v0[i] + v1[i];
    }
    return v;
}
template <typename T>
inline void combineSimilar(std::vector<T>* v0, std::vector<T>* v1)
{
    //linear version of merge verts
    for (int x = 0; x < v0->size(); x++)
    {
        (*v0)[x] = ((*v0)[x] + (*v1)[x]) / 2;
    }
}

template <typename T>
inline void combineSimilar(std::vector<T>* v, const std::vector<T>* v0, const std::vector<T>* v1)
{
    //linear version of merge verts
    *v = std::vector<T>(v0->size());
    for (int x = 0; x < v0->size(); x++)
    {
        (*v)[x] = ((*v0)[x] + (*v1)[x]) / 2;
    }
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& v0, const std::vector<T>& v1)
{
    //std::cout << "in minus operator\n";
    std::vector<T> v = std::vector<T>(v0.size());
    for (int i = 0; i < v0.size(); ++i)
    {
        v[i] = v0[i] - v1[i];
    }
    //std::cout << "end minus operator\n";
    return v;
}

template <typename T>
std::vector<T> operator/(const std::vector<T>& v0, const float& f1)
{
    std::vector<T> v = std::vector<T>(v0.size());
    for (int i = 0; i < v0.size(); ++i)
    {
        v[i] = v0[i] / f1;
    }
    return v;
}

template <typename T>
std::vector<T> operator*(const std::vector<T>& v0, const float& f1)
{
    std::vector<T> v = std::vector<T>(v0.size());
    for (int i = 0; i < v0.size(); ++i)
    {
        v[i] = v0[i] * f1;
    }
    return v;
}


template <typename T>
void extend(std::vector<T>* v0, const std::vector<T>* v1)
{
    for (int i = 0; i < v1.size(); ++i)
    {
        v0->push_back((*v1)[i]);
    }
}

template <typename T>
bool in(const T& a, const std::vector<T>& v1)
{
    for (int i = 0; i < v1.size(); ++i)
    {
        if (a == v1[i])
            return true;
    }
    return false;
}


template <typename T>
inline T magSq(const std::vector<T>& v1)
{
    //std::cout << "in magSq\n";
    T f = 0;
    for (int x = 0; x < v1.size(); x++)
    {
        T a = v1.at(x);
        f = f + (a * a);
    }
    //std::cout << "end magSq\n";
    return f;
}

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
