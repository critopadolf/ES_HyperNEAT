#include "activations.h"
//Activations
inline float leaky_relu(float x)
{
	return (x > 0) * x + (x <= 0) * 0.01 * x;
}
inline float inputActivation(float x)
{
	return x;
}
//sinf, tanf

//combine
inline float add(float a, float b)
{
	return a + b;
}
inline float mul(float a, float b)
{
	return a * b;
}
