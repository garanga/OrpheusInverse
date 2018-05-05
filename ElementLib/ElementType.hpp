/*
 * ElementType.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef ELEMENTTYPE_HPP_
#define ELEMENTTYPE_HPP_

#include "Eigen/Dense"
using namespace Eigen;

#include <string>

class Material;

// A base class for all the classes representing finite elements

class ElementType
{
public:

     ElementType();
     virtual
    ~ElementType();

     virtual void
     modfMaterial(Material*) = 0;


    std::string
    getName() const;

    int
    getDimension() const;

    int
    getNodesNum() const;

    virtual
    Material*
    getMaterial() const = 0;

    virtual
    Matrix<double,2,2>
    calcLocK(int,int,Matrix<double,2,4>&) const = 0;

protected:

    std::string _name;
    int         _dimension;
    int         _nodesNum;

};

#endif /* ELEMENTTYPE_HPP_ */
