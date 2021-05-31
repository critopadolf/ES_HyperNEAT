#pragma once
#include <vector>
#include <math.h>

//Activations
inline float leaky_relu(float x);
inline float inputActivation(float x);
//sinf, tanf

//combine
inline float add(float a, float b);
inline float mul(float a, float b);


const std::vector<float (*)(float, float)> COMBINE_LIST = { add, mul };
const std::vector<float (*)(float)> ACTIVATION_LIST = { inputActivation, leaky_relu, sinf, tanf };