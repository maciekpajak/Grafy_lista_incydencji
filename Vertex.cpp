#include "Vertex.h"


Vertex::Vertex()
{ 
	incidentEdges = new SLinkedList<Edge>(); 
}

Vertex::Vertex(int element)
{ 
	element_ = element;
	incidentEdges = new SLinkedList<Edge>(); 
}	


Vertex::~Vertex()
{
	if (numberOfIncidentEdges() > 0)
		for (int i = 1; i <= numberOfIncidentEdges(); i++)
			(*incidentEdges)[i].~Edge();
}

SLinkedList<Vertex>* Vertex::adjacentVertices()
{
	SLinkedList<Vertex>* adjacentVertices = new SLinkedList<Vertex>();
	for (int i = 1; i <= numberOfIncidentEdges(); i++)
	{
		if ((*incidentEdges)[i][0] == *this)
			adjacentVertices->addLast((*incidentEdges)[i][1]);
		else
			adjacentVertices->addLast((*incidentEdges)[i][0]);
	}
	return adjacentVertices;
}
