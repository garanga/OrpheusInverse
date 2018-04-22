/*
 * Mesh.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include <vector>

class Node;
class Element;
class ElementSet;

class Mesh
{
public:

     Mesh();
    ~Mesh();

    void
    addNode(Node*);

    void
    addElement(Element*);

    void
    addElementSet(ElementSet*);

    std::vector<Node*>
    getNodes() const;

    int
    getNodesNum() const;

    std::vector<Element*>
    getElements() const;

    std::vector<ElementSet*>
    getElementSets() const;

private:

    std::vector <Node*>       _nodes;
    std::vector <Element*>    _elements;
    std::vector <ElementSet*> _elementSets;

};


#endif /* MESH_HPP_ */
