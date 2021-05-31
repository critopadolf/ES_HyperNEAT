#pragma once
#include "Layer.h"
template<typename T>
class typedLayer : public Layer
{
public:
	typedLayer(T& d) : Layer(), data(d) {}
private:
	T data;
};

