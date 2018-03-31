/*
 * Constraint.hpp
 *
 *  Created on: Feb 1, 2017
 *      Author: pavel
 */

#ifndef CONSTRAINT_HPP_
#define CONSTRAINT_HPP_

#include <string>
#include <vector>

namespace Symbol
{
    enum class DisplacementConstraint;
};

class Constraint
{
public:

     Constraint(
        std::string                    ,
        std::vector<int>               ,
        Symbol::DisplacementConstraint ,
        double*                        );

     Constraint(const Constraint&);

    ~Constraint();

    std::vector<int>
    getRegion() const;

    Symbol::DisplacementConstraint
    getType() const;

    double*
    getValue() const;

private:

    std::string                    _name  ;
    std::vector<int>               _region;
    Symbol::DisplacementConstraint _type  ;
    double*                        _value ;
};



#endif /* CONSTRAINT_HPP_ */
