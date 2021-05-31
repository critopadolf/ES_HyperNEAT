#include "Mesh.h"

#define MERGE_VERTS true

Mesh::Mesh(const Mesh& m)
{
	min = m.min;
	max = m.max;
	dim = m.dim;

	input = m.input;
	hidden = m.hidden;
	output = m.output;

}

Mesh::Mesh(){}
Mesh::Mesh(float min, float max, float dim) : min(min), max(max), dim(dim) {}
Mesh::Mesh(std::mt19937* meng, int dimensions, int inpLength, int outLength, int maxNumPoints)
{
	float N = randInt(meng, 0.0, maxNumPoints);
	min = -2;
	max = 2;
	dim = dimensions;
	input = std::vector< point_t >(inpLength);
	hidden = std::vector< point_t >(N);
	output = std::vector< point_t >(outLength);
	fill2DVector(&input, meng, dim, min, max); fill2DVector(&hidden, meng, dim, min, max); fill2DVector(&output, meng, dim, min, max);
	//int rm = merge_Verts(0.001);
}
Mesh::Mesh(std::mt19937* meng, int dimensions, int inpLength, int outLength, int maxNumPoints, float minMeshVal, float maxMeshVal)
{
	float N = randInt(meng, 0.0, maxNumPoints);
	min = minMeshVal;
	max = maxMeshVal;
	dim = dimensions;
	input = std::vector< point_t >(inpLength);
	hidden = std::vector< point_t >(N);
	output = std::vector< point_t >(outLength);
	fill2DVector(&input, meng, dim, min, max); fill2DVector(&hidden, meng, dim, min, max); fill2DVector(&output, meng, dim, min, max);
#if MERGE_VERTS
	int rm = merge_Verts(0.001);
#endif
}
void Mesh::setParams(float min, float max, int dim)
{
	min = min; max = max; dim = dim;
}
int Mesh::inpLen()    { return input.size();  }
int Mesh::hiddenLen() { return hidden.size(); }
int Mesh::outLen()    { return output.size(); }

int Mesh::dimSize() { return dim; }
int Mesh::size()    { return inpLen() + outLen() + hiddenLen(); }

std::vector<point_t>* Mesh::getInput() { return &input; }
std::vector<point_t>* Mesh::getHidden() { return &hidden; }
std::vector<point_t>* Mesh::getOutput() { return &output; }

point_t& Mesh::operator[](int k)
{ 
	int m = inpLen();
	if (k < m)
		return input[k];
	int n = hiddenLen();
	if(k >= m && k < n + m)
		return hidden[k - m];
	m = n + m;
	if(k >= m)
		return output[k - m];
}

void Mesh::testMerge()
{
	std::vector< point_t > tmp = hidden;
	std::vector< point_t > h = { {0,2,1}, {0,0,0} , {0,0,1} , {0,1,1} , {0,2,1} , {1,0,0} };
	hidden = h;
	point_t t0 = (hidden[1] + hidden[2] + hidden[5]) / 3;
	point_t t1 = (hidden[0] + hidden[3] + hidden[4]) / 3;
	int rm = merge_Verts(1.2);
	std::vector< point_t > des_hidden = { t1, t0 };

	bool b = hidden == des_hidden;
	if (b)
	{
		std::cout << "passed merge verts test\n" << hidden << "\n\n" << des_hidden;
	}
	else 
	{
		std::cout << "failed merge verts test\n" << hidden << "\n\n" << des_hidden;
	}
	hidden = tmp;
	
}

point_t Mesh::std_dev(std::vector< point_t >* points)
{
	point_t u = mean(points);
	for (int x = 0; x < (*points).size(); x++)
	{
		//float tmp = ((*points)[x] - )
	}

	return u;
}
point_t Mesh::mean(std::vector< point_t >* points)
{
	point_t u;
	return u;
}
void mate(Mesh* m, const Mesh& m0, const Mesh& m1, std::mt19937* meng, config* cfg)
{
	m->setParams(m0.min, m0.max, m0.dim);
	//combine inputs and outputs
	combineSimilar(m->getInput(), &(m0.input), &(m1.input));
	combineSimilar(m->getOutput(), &(m0.output), &(m1.output));
	//combine hidden
	vCrossOver_disjointed(m->getHidden(), &(m0.hidden), &(m1.hidden), meng);
	//hm.merge_Verts(0.001);
	m->mutate(meng, cfg);
}


void Mesh::mutate(std::mt19937* meng, config* cfg)
{
	
	//mutate vectors
	mutatePointVec(&input, meng, cfg);
	mutatePointVec(&hidden, meng, cfg);
	mutatePointVec(&output, meng, cfg);

	if (randfloat(meng, 0, 1) <= cfg->newPointRate)
	{
		//add new point
		hidden.push_back(newPoint(meng));
	}
	// remove point
	
	if (randfloat(meng, 0, 1) <= cfg->removePointRate)
	{
		int sz = hidden.size();
		if (sz == 1)
		{
			hidden.erase(hidden.begin());
		}
		else if(sz > 1)
		{
			//std::cout << "erase node\t" << hidden.size() << "\n";
			hidden.erase(hidden.begin() + randInt(meng, 0, hidden.size() - 1));
		}
	}
#if MERGE_VERTS
	int rm = merge_Verts(0.001);
#endif

}
void Mesh::mutatePointVec(std::vector<point_t>* p, std::mt19937* meng, config* cfg)
{
	for (int x = 0; x < p->size(); x++)
	{
		if (randfloat(meng, 0, 1) <= cfg->mutatePointRate)
		{
			
			for (int y = 0; y < dim; y++)
			{
				mutateFloat(&((*p)[x][y]), meng, (double)min, (double)max, 0.05);
			}
		}
	}
}
point_t Mesh::newPoint(std::mt19937* meng)
{
	point_t pt(dim);
	fillVector(&pt, meng, min, max);
	return pt;
}
int Mesh::merge_Verts(float thresh)
{
	KDTree tree(hidden);
	std::vector<int> toRemove;
	std::vector<point_t> newPoints;
	std::vector<bool> val(hidden.size(), true);
	for (int x = 0; x < hidden.size(); x++)
	{
		if (val[x])
		{
			
			auto neighborhood = tree.neighborhood_indices(hidden[x], thresh);
			point_t avg = hidden[x];
			val[x] = false;
			int _div = 1;
			for (int y = 0; y < neighborhood.size(); y++)
			{
				if (val[neighborhood[y]])
				{
					avg = avg + hidden[neighborhood[y]];
					_div++;
					val[neighborhood[y]] = false;
				}
			}
			avg = avg / _div;
			newPoints.push_back(avg);	
		}
	}
	int rm = hidden.size();
	hidden = newPoints;
	return rm - hidden.size();
}



std::ostream& operator<<(std::ostream& os, const Mesh& m)
{
	/*
	os << "Mesh object\n";
	os << "dimensions      : " << m.dim << "\n";
	os << "input vertices  : " << m.input.size() << "\n";
	os << m.input << "\n";
	os << "output vertices : " << m.output.size() << "\n";
	os << m.output << "\n";
	os << "hidden vertices : " << m.hidden.size() << "\n";
	*/
	os << m.hidden << "\n";
	return os;
}