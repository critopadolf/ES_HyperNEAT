#pragma once
#include <iostream>
#include <vector>
#include <memory>
class Layer
{
public:
	Layer();
};
std::ostream& operator<<(std::ostream& os, Layer& l);
typedef std::vector< std::shared_ptr<Layer> > layer_list;