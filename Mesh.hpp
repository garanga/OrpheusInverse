/*
 * Mesh.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef MESH_HPP_
#define MESH_HPP_

#include <map>
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

    Element*
    getElement(int) const;

    std::vector<Element*>
    getElements() const;

<<<<<<< HEAD
    ElementSet*
    getElementSet(std::string) const;

    std::map<std::string,ElementSet*>
=======
    std::vector<ElementSet*>
>>>>>>> branch 'master' of https://github.com/garanga/OrpheusInverse.git
    getElementSets() const;

private:

<<<<<<< HEAD
    std::vector <Node*>                _nodes;
    std::vector <Element*>             _elements;
    std::map <std::string,ElementSet*> _elementSets;
=======
    std::vector <Node*>       _nodes;
    std::vector <Element*>    _elements;
    std::vector <ElementSet*> _elementSets;
>>>>>>> branch 'master' of https://github.com/garanga/OrpheusInverse.git

};


#endif /* MESH_HPP_ */
