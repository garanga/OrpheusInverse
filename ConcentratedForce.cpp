/*
 * ConcentratedForce.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#include "ConcentratedForce.hpp"

#include "includes.hpp"

ConcentratedForce::ConcentratedForce(std::string               name  ,
                                     std::vector<int>          region,
                                     Symbol::ConcentratedForce type  ,
                                     double*                   value  )
    : Load(name),
      _region(region), _type(type), _value(value)
{
}

ConcentratedForce::ConcentratedForce(const ConcentratedForce& concentratedForce)
{
    _name  = concentratedForce._name;
    _type  = concentratedForce._type;
    _region = std::vector<int>(concentratedForce._region);

    _value = new double[2];
    _value[0] = concentratedForce._value[0];
    _value[1] = concentratedForce._value[1];
}

ConcentratedForce::~ConcentratedForce()
{
    if (_value != nullptr)
        delete [] _value;
}

std::vector<int>
ConcentratedForce::getRegion() const
{
    return _region;
}

Symbol::ConcentratedForce
ConcentratedForce::getType() const
{
    return _type;
}

double*
ConcentratedForce::getValue() const
{
    return _value;
}

