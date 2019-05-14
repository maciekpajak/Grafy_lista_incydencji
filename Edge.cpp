#include "Edge.h"


Edge::Edge(int weight, Vertex& v1, Vertex& v2)
{
	if (weight < 0)
	{
		std::string exeption = "weight lower than 0";
		throw exeption;
	}
	weight_ = weight;
	vertices_[0] = &v1;
	vertices_[1] = &v2;
	v1.pushIncidentEdge(*this);
	v2.pushIncidentEdge(*this);
}

Edge::~Edge() {
	vertices_[0]->removeIncidentEdge(*this);
	vertices_[1]->removeIncidentEdge(*this);
}

Vertex & Edge::operator[](int i)
{
	if (i == 0) return *vertices_[0];
	if (i == 1) return *vertices_[1];
	else
	{
		std::string exeption = "invalid index";
		throw exeption;
	}
}
