/*
 * Constraint.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: pavel
 */

#include "includes.hpp"

Constraint::Constraint(
        std::string                    name  ,
        std::vector<int>               region,
        Symbol::DisplacementConstraint type  ,
        double*                        value )
    : _name(name), _region(region), _type(type), _value(value)
{

}

Constraint::Constraint(const Constraint& constraint)
{
    _name   = constraint._name;

    _region = std::vector<int>(constraint._region);

    _type   = constraint._type;

    _value = new double[2];
    _value[0] = constraint._value[0];
    _value[1] = constraint._value[1];
}

Constraint::~Constraint()
{
    if (_value != nullptr)
        delete [] _value;
}


std::vector<int>
Constraint::getRegion() const
{
    return _region;
}

Symbol::DisplacementConstraint
Constraint::getType() const
{
    return _type;
}

double*
Constraint::getValue() const
{
    return _value;
}
