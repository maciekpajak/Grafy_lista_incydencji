#include "Graph.h"
#include <string>
#include <iostream>

Graph::~Graph()
{
}

Vertex& Graph::opposite(Vertex & vertex, Edge & edge)
{
	Vertex** vertices = edge.getVertices();
	if (vertices[0] != &vertex and vertices[1] != &vertex)
	{
		std::string exeption = "edge is not incident to vertex";
		throw exeption;
	}
	else 
	{
		if (vertices[0] == &vertex)
			return *vertices[1];
		//if(vertices[1] == &vertex)
		else
			return *vertices[0];
	}
}

bool Graph::areAdjacent(Vertex & v1, Vertex & v2)
{
	if (v1.numberOfIncidentEdges() == 0)
		return false;
	SLinkedList<Edge>* tmp = v1.getIncidentEdges();
	for (int i = 1; i <= v1.numberOfIncidentEdges(); i++)
	{
		Vertex** vertices = (*tmp)[i].getVertices();
		if (vertices[0] == &v2 or vertices[1] == &v2)
			return true;
	}
	return false;
}

int Graph::loadFromFile(std::string fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (!file.good())
	{
		std::string exeption = "Bad file";
		throw exeption;
	}

	int nEdges;
	int nVertices;
	int startVertex;

	file >> nEdges >> nVertices >> startVertex;
	int i;
	for (i = 1; i <= nEdges; i++)
	{
		int vertex1elem;
		int vertex2elem;
		int weight;
		file >> vertex1elem >> vertex2elem >> weight;
		if (!file.fail())
		{
			Vertex* vertex1 = new Vertex(vertex1elem);
			Vertex* vertex2 = new Vertex(vertex2elem);
			bool isVertex1InList = false;
			bool isVertex2InList = false;
			int i;
			for (i = 1; i <= vertices_->getSize(); i++)
			{
				if ((*vertices_)[i] == *vertex1)
				{
					isVertex1InList = true;
					vertex1 = &(*vertices_)[i];
				}
				if ((*vertices_)[i] == *vertex2)
				{
					isVertex2InList = true;
					vertex2 = &(*vertices_)[i];
				}
			}
			if (isVertex1InList == false)
				insertVertex(*vertex1);
			if (isVertex2InList == false)
				insertVertex(*vertex2);

			if (vertices_->getSize() > nVertices)
			{
				std::string exeption = "more vertices than declared";
				throw exeption;
			}

			insertEdge(*vertex1, *vertex2, weight);
		}
		else
			 break; 
	} 
	if (i < nEdges)
		{
			std::string exeption = "less edges than declared";
			throw exeption;
		}
	return startVertex;
}

bool Graph::saveToFile(std::string fileName, int* P, int* D)
{
	std::ofstream file;
	file.open(fileName);
	if (!file.good())
		return false;
	int i;
	for (i = 1; i <= numberOfVertices(); i++)
		if (indexOfStartVertex_ == (*vertices_)[i].getElement())
			break;
	Vertex& startVertex = (*vertices_)[i];

	int* S = new int[numberOfVertices()];

	int startNumber = startVertex.getElement();

	std::string weight = "weight";
	file << weight << " : path \n";
	for (int i = 0; i < numberOfVertices(); i++)
	{	
		file.width(weight.length());
		file << std::left << D[i] << " : ";
		int j = i, n = 0;
		while (j != startNumber)
		{
			S[n++] = j;
			j = P[j];
		}
		S[n++] = startNumber;
		while (n > 0)
		{
			file << S[--n] << ' ';
		}
		file << "\n";
	}
	return true;
}

void Graph::graphGenerator(int nVertices, int density)
{
	if (density > 100 or density <= 0)
	{
		std::string exeption = "Incorrect density (density < 0 or density > 100)";
		throw exeption;
	}
	if (nVertices <=0 )
	{
		std::string exeption = "Not enaugh vertices";
		throw exeption;
	}
	int nEdges = (int)(density*(nVertices - 1)*nVertices / 200);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < nVertices; i++)
		insertVertex(i);

	for (int i = 0; i < nEdges; i++)
	{
		int randVertex1 = (std::rand() % nVertices) + 1;
		int randVertex2 = (std::rand() % nVertices) + 1;
		
		if (areAdjacent((*vertices_)[randVertex1], (*vertices_)[randVertex2])) //if edge between these vertices exist
			continue;

		int randWeight = (std::rand() % 100) + 0;
		insertEdge((*vertices_)[randVertex1], (*vertices_)[randVertex2], randWeight);
	}
}
