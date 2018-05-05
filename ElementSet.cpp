/*
 * ElementSet.cpp
 *
 *  Created on: Apr 22, 2018
 *      Author: pavel
 */

#include "ElementSet.hpp"

#include "includes.hpp"

ElementSet::ElementSet(std::string name)
    : _name(name)
{
}

ElementSet::~ElementSet()
{

}

void
ElementSet::addId(int id)
{
    _set.push_back(id);
}

std::string
ElementSet::getName() const
{
    return _name;
}

std::vector<int>
ElementSet::getSet() const
{
    return _set;
}




