/*
 * ElementSet.hpp
 *
 *  Created on: Apr 22, 2018
 *      Author: pavel
 */

#ifndef ELEMENTSET_HPP_
#define ELEMENTSET_HPP_

#include <string>
#include <vector>

class ElementSet
{
public:

     ElementSet(std::string);
    ~ElementSet();

    void
    addId(int);

    std::string
    getName() const;

    std::vector<int>
    getSet() const;

private:

    std::string      _name;
    std::vector<int> _set;
};



#endif /* ELEMENTSET_HPP_ */
