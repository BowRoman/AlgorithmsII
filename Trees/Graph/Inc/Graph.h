#pragma once
#include "Common.h"

template<typename T>
class Graph
{
private:
	struct Vertex
	{
		int mID;
		T mData;
		std::list<int> mAdjacencyList;

		Vertex(int id, T data = T()) : mID(id), mData(data) {}
	}; // class Vertex
	std::vector<Vertex> mVertices;

public:
	Graph(int size = 0);

	void AddVertex(T data);
	void AddEdge(int v0, int v1);

	std::vector<int> DFS(); // Depth-First search
	std::vector<int> BFS(); // Breadth-First search

private:
	void DFHelper(int idx, std::vector<bool>& visited, std::vector<int> result);
}; // class Graph

template<typename T>
inline Graph<T>::Graph(int size)
{
	if (size > 0)
	{
		mVertices.reserve(size);
	}
}

template<typename T>
inline void Graph<T>::AddVertex(T data)
{
	mVertices.push_back(Vertex(mVertices.size(), data));
}

template<typename T>
inline void Graph<T>::AddEdge(int v0, int v1)
{
	mVertices[v0].mAdjacencyList.push_back(v1);
	mVertices[v1].mAdjacencyList.push_back(v0);
}


template<typename T>
inline std::vector<int> Graph<T>::DFS()
{
	// geeksforgeeks.org/depth-first-traversal-for-a-graph
	std::vector<int> result;
	std::vector<bool> visited;
	visited.reserve(mVertices.size());
	for (int i = 0; i < visited.size(); ++i)
	{
		visited[i] = false;
	}

	for (int i = 0; i < mVertices.size(); ++i)
	{
		DFHelper(i, visited, result);
	}
	return result;
}

template<typename T>
inline std::vector<int> Graph<T>::BFS()
{

}

template<typename T>
inline void Graph<T>::DFHelper(int idx, std::vector<bool>& visited, std::vector<int> result)
{
	visited[idx] = true;

	std::list<int>::iterator i;
	for (i = mVertices[idx].mAdjacencyList.begin(); i != mVertices[idx].mAdjacencyList.end(); ++i)
		if (!visited[*i])
			DFHelper(*i, visited);
}
