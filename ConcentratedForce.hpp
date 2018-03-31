/*
 * ConcentratedForce.hpp
 *
 *  Created on: Feb 3, 2017
 *      Author: pavel
 */

#ifndef CONCENTRATEDFORCE_HPP_
#define CONCENTRATEDFORCE_HPP_

#include "Load.hpp"

#include <iostream>
#include <vector>

namespace Symbol
{
    enum class ConcentratedForce;
}

class ConcentratedForce : public Load
{
public:

     ConcentratedForce(std::string              ,
                       std::vector<int>         ,
                       Symbol::ConcentratedForce,
                       double*                  );

     ConcentratedForce(const ConcentratedForce&);

    ~ConcentratedForce();

    std::vector<int>
    getRegion() const final;

    Symbol::ConcentratedForce
    getType() const final;

    double*
    getValue() const final;

private:

    std::vector<int>          _region;
    Symbol::ConcentratedForce _type  ;
    double*                   _value ;
};



#endif /* CONCENTRATEDFORCE_HPP_ */
