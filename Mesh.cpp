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

void
Mesh::addElementSet(ElementSet* elementSet)
{
    _elementSets[elementSet->getName()] = elementSet;
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

Element*
Mesh::getElement(int id) const
{
    auto it = std::find_if(_elements.begin(),_elements.end(),
                  [&id](Element* element)
                  {
                         return element->getId() == id;
                  });
    return *it;
}

std::vector<Element*>
Mesh::getElements() const
{
    return _elements;
}

ElementSet*
Mesh::getElementSet(std::string name) const
{
    return _elementSets.at(name);
}

std::map<std::string,ElementSet*>
Mesh::getElementSets() const
{
    return _elementSets;
}
