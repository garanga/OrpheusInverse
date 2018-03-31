/*
 * P4.hpp
 *
 *  Created on: Jan 19, 2017
 *      Author: pavel
 */

#ifndef ELEMENTLIB_P4_HPP_
#define ELEMENTLIB_P4_HPP_

#include "ElementType.hpp"

#include <Eigen/Dense>
using namespace Eigen;

class P4 : public ElementType
{
public:

    P4(double, double, bool=false);
   ~P4();

    // A method returns a stiffness matrix K:
    // the integral over the domain occupied by an element of
    // a quantity B(i,...).transpose()*D*B(j,...)

    Matrix<double,2,2>
    calcLocK(int,int, Matrix<double,2,4>&) const;

    // A method returns an elastic matrix D
    Matrix<double,3,3> getD() const;

//    void updateForce(Matrix<double,2,4>&, VectorXd&, VectorXd&) const;

private:

    double* _alpha;
    double* _beta ;
    double* _gamma;
    double* _delta;

    Matrix<double,3,3> _D;

    Matrix<double,2,4> _quadraturePoints ;
    Matrix<double,1,4> _quadratureWeights;

    // A method returns a shape function corresponded to node \f$ I \f$
    // calculated in a point \f$ (\xi,\eta) \f$ in the local coordinates

    double
    calcShapeFuncLoc(int, double, double) const;

    // A method returns a shape function of node <<i>> local derivatives
    // calculated in a local point (xi,eta): ||dNi/d(xi),dNi/d(eta)||(xi,eta)

    Matrix<double,1,2>
    calcShapeFuncLocDerLoc(int, double, double) const;

    // A method returns the Jacobian matrix d(x,y)/d(xi,eta)
    // calculated in a local point (xi,eta): ||dx/dxi,dx/deta||
    //                                       ||dy/dxi,dy/deta||(xi,eta)
    // nodesCoordGlob is a matrix containing element nodes global coordinates:
    // || x1,x2,x3,x4
    //    y1,y2,y3,y4 ||

    Matrix<double,2,2>
    calcJacobianMatrix(double, double, Matrix<double,2,4>&) const;

    // A method returns a shape function of node <<i>> global derivatives
    // calculated in a local point (xi,eta): ||dNi/d(x),dNi/d(y)||(xi,eta)

    Matrix<double,1,2>
    calcShapeFuncGlobDerLoc(int, double, double, Matrix<double,2,4>&) const;

    // A method returns a matrix \f$ \bm{B}_I \f$ composed of
    // global derivatives of a shape function \f$ N_I \f$

    Matrix<double,3,2>
    calcBi(int, double, double, Matrix<double,2,4>&) const;

    // A method returns a matrix \f$ \bm{B} \f$ composed of
    // global derivatives of shape functions \f$ N_I, I=1,\ldots,4 \f$
    Matrix<double,3,8>
    calcB(double, double, Matrix<double,2,4>&) const;

};

#endif /* ELEMENTLIB_P4_HPP_ */
