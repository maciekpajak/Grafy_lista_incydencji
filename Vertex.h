#pragma once
#include "SLinkedList.h"
#include "Edge.h"
#include <string>

class Edge;

class Vertex
{
private:
	int element_;
	int distance_;
public:

	SLinkedList<Edge>* incidentEdges;

	Vertex();
	Vertex(int element);
	~Vertex();

	int getElement() const { return element_; }
	int getDistance() const { return distance_; }

	void setElement(int newElement) { element_ = newElement; }
	void setDistance(int newDistance) { distance_ = newDistance; }

	void pushIncidentEdge(Edge& edge) { incidentEdges->addLast(edge); }
	void removeIncidentEdge(Edge& edge) { incidentEdges->remove(&edge); }
	int numberOfIncidentEdges() { return incidentEdges->getSize(); }
	
	SLinkedList<Edge>* getIncidentEdges() { return incidentEdges; }
	SLinkedList<Vertex>* adjacentVertices();

	bool operator == (Vertex& v) { return element_ == v.element_ ? true : false; }
	bool operator > (Vertex& v) { return element_ > v.element_ ? true : false; }
	bool operator >= (Vertex& v) { return element_ >= v.element_ ? true : false; }
	bool operator < (Vertex& v) { return element_ < v.element_ ? true : false; }
	bool operator <= (Vertex& v) { return element_ <= v.element_ ? true : false; }
	bool operator != (Vertex& v) { return element_ != v.element_ ? true : false; }

};

