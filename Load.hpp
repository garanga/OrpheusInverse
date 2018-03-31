/*
 * Load.hpp
 *
 *  Created on: Mar 24, 2018
 *      Author: pavel
 */

#ifndef LOAD_HPP_
#define LOAD_HPP_

#include <string>
#include <vector>

namespace Symbol
{
    enum class ConcentratedForce;
}

class Load
{
public:

     Load();
     Load(std::string);
     virtual
    ~Load();

    virtual std::vector<int>
    getRegion() const = 0;

    virtual Symbol::ConcentratedForce
    getType() const = 0;

    virtual double*
    getValue() const = 0;

protected:
    std::string _name;
};



#endif /* LOAD_HPP_ */
