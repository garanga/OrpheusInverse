/*
 * Mesh.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#include "Mesh.hpp"

#include "includes.hpp"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{

    for (auto it = _nodes.begin(); it != _nodes.end(); ++it)
        delete *it;

    for (auto it = _elements.begin(); it != _elements.end(); ++it)
        delete *it;

}

void
Mesh::addNode(Node* node)
{
    _nodes.push_back(node);
}

void
Mesh::addElement(Element* element)
{
    _elements.push_back(element);
}

std::vector<Node*>
Mesh::getNodes() const
{
    return _nodes;
}

int
Mesh::getNodesNum() const
{
    return _nodes.size();
}

std::vector<Element*>
Mesh::getElements() const
{
    return _elements;
}
