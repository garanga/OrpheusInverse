/*
 * Odb.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: pavel
 */

#include "Odb.hpp"

#include "includes.hpp"

Odb::Odb(Mesh* mesh)
    : _mesh(mesh)
{
}

Odb::~Odb()
{
}

void
Odb::addField(Symbol::Output fieldType,std::vector<double> fieldValue)
{
    _fieldOutputs[fieldType] = fieldValue;
}

Mesh*
Odb::getMesh() const
{
    return _mesh;
}

std::vector<double>
Odb::getField(const Symbol::Output& fieldType)
{
    return _fieldOutputs[fieldType];
}
