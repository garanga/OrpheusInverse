/*
 * ElementType.cpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */



#include "ElementType.hpp"

#include <string>

ElementType::ElementType()
    : _name(""), _dimension(-1), _nodesNum(-1)
{
}

ElementType::~ElementType()
{
}



std::string
ElementType::getName() const
{
    return _name;
}

int
ElementType::getDimension() const
{
    return _dimension;
}

int
ElementType::getNodesNum() const
{
    return _nodesNum;
}
