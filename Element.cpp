/*
 * Element.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#include "Element.hpp"

#include "ElementLib/ElementType.hpp"

Element::Element()
    : _id(-1), _connect(nullptr), _type(nullptr)
{
}

Element::Element(int id, int* connect, ElementType* type)
    : _id(id), _connect(connect), _type(type)
{
}

Element::~Element()
{
    if (_connect != nullptr)
        delete [] _connect;
    /*
    if (_type != nullptr) Type deletes in Mesh
        delete _type;
    */
}

/*
void
Element::setConnect(int* connect)
{
    if (_connect != nullptr)
        delete [] _connect;

    _connect = connect;
}
*/

int
Element::getId() const
{
     return _id;
}

int*
Element::getConnect() const
{
     return _connect;
}

ElementType*
Element::getType() const
{
     return _type;
}
