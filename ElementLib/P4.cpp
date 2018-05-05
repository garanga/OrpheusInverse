/*
 * P4.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: pavel
 */

#include "P4.hpp"

#include "../includes.hpp"

using std::sqrt;

P4:: P4(Material* material, bool isPlainStrain)
    : _material(material), _isPlainStrain(isPlainStrain)
{
    _name       = "P4";
    _dimension  = 2;
    _nodesNum   = 4;

    _alpha = new double[4];
    _alpha[0] =  1.0; _alpha[1] =  1.0; _alpha[2] = 1.0; _alpha[3] =  1.0;
    _beta  = new double[4];
    _beta[0]  = -1.0; _beta[1]  =  1.0; _beta[2]  = 1.0; _beta[3]  = -1.0;
    _gamma = new double[4];
    _gamma[0] = -1.0; _gamma[1] = -1.0; _gamma[2] = 1.0; _gamma[3] =  1.0;
    _delta = new double[4];
    _delta[0] =  1.0; _delta[1] = -1.0; _delta[2] = 1.0; _delta[3] = -1.0;

    updateD();


    _quadraturePoints << -1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0), -1.0/sqrt(3.0),
                         -1.0/sqrt(3.0),-1.0/sqrt(3.0), 1.0/sqrt(3.0),  1.0/sqrt(3.0);

    _quadratureWeights << 1.0, 1.0, 1.0, 1.0;

    Matrix<double,2,4> x;
    x <<-1.0, 1.0, 1.0,-1.0,
        -1.0,-1.0, 1.0, 1.0;

}

P4::~P4()
{
    delete [] _alpha;
    delete [] _beta ;
    delete [] _gamma;
    delete [] _delta;
}

Material*
P4::getMaterial() const
{
    return _material;
}

void
P4::updateD()
{

    double young   = _material->getYoung();
    double poisson = _material->getPoisson();

    // exy is doubled
    if (!_isPlainStrain)
    {
        _D(0,0) = 1.0    ; _D(0,1) = poisson; _D(0,2) = 0.0;
        _D(1,0) = poisson; _D(1,1) = 1.0    ; _D(1,2) = 0.0;
        _D(2,0) = 0.0    ; _D(2,1) = 0.0    ; _D(2,2) = (1.0-poisson)/2.0;
        _D *= young/(1.0-pow(poisson,2));
    }
    else
    {
        _D(0,0) = 1.0-poisson; _D(0,1) = poisson    ; _D(0,2) = 0.0;
        _D(1,0) = poisson    ; _D(1,1) = 1.0-poisson; _D(1,2) = 0.0;
        _D(2,0) = 0.0        ; _D(2,1) = 0.0        ; _D(2,2) = (1.0-2.0*poisson)/2.0;
        _D *= young/((1.0+poisson)*(1.0-2.0*poisson));
    } /* plainStrain */
}

void
P4::modfMaterial(Material* material)
{
    delete _material;

    Material* materialTmp = new Isotropic(material->getName(),
                                          material->getYoung(),
                                          material->getPoisson());

    _material = materialTmp;
    updateD();
}

/*!
 *  Detailed description will be given later.
 *  @param[in]    i    The node number
 *  @param[in]    xi    The \f$ \xi \f$ coordinate in a reference frame
 *  @param[in]    eta    The \f$ \eta \f$ coordinate in a reference frame
 */
double P4::calcShapeFuncLoc(int i, double xi, double eta) const
{
    return (_alpha[i] + _beta[i]*xi + _gamma[i]*eta + _delta[i]*xi*eta)/4.0;
}

Matrix<double,1,2>
P4::calcShapeFuncLocDerLoc(int i, double xi, double eta) const
{
    Matrix<double,2,1> v;
    v.setZero();
    v << (_beta[i] + _delta[i]*eta)/4.0,(_gamma[i] + _delta[i]*xi)/4.0;
    return v;
}

Eigen::Matrix<double,2,2>
P4::calcJacobianMatrix(double xi           , double eta         ,
                       Matrix<double,2,4>& nodesCoordGlob) const
{
    // tmp is used for the following matrix
    // ||dN0/d(xi),dN0/d(eta)
    //   dN1/d(xi),dN1/d(eta)
    //   dN2/d(xi),dN2/d(eta)
    //   dN3/d(xi),dN3/d(eta)||
    Matrix<double,4,2> tmp;

    Matrix<double,1,2> v;
    for (int i=0; i<_nodesNum; ++i)
    {
        v = calcShapeFuncLocDerLoc(i, xi, eta);
        tmp.row(i) = v;
    }

    return nodesCoordGlob*tmp;
}

Eigen::Matrix<double,1,2>
P4::calcShapeFuncGlobDerLoc(int i    , double xi    , double eta    ,
                            Matrix<double,2,4>& nodesCoordGlob) const
{
    Matrix<double,1,2> shapeFuncLocDerLoc;
    shapeFuncLocDerLoc = calcShapeFuncLocDerLoc(i, xi, eta);

    Matrix<double,2,2> jacobianMatrix;
    jacobianMatrix = calcJacobianMatrix(xi, eta, nodesCoordGlob);

    Matrix<double,1,2> v;
    v = shapeFuncLocDerLoc*jacobianMatrix.inverse();

    return v;
}


Eigen::Matrix<double,3,2>
P4::calcBi(int i    , double xi    , double eta     ,
           Matrix<double,2,4>& nodesCoordGlob) const
{
    Matrix<double,1,2> shapeFuncGlobDerLoc;
    shapeFuncGlobDerLoc = calcShapeFuncGlobDerLoc(i, xi, eta, nodesCoordGlob);

    Matrix<double,3,2> Bi;
    Bi << shapeFuncGlobDerLoc(0), 0.0,
          0.0                   , shapeFuncGlobDerLoc(1),
          shapeFuncGlobDerLoc(1), shapeFuncGlobDerLoc(0);
    return Bi;
}


Matrix<double,3,8>
P4::calcB(double xi           , double eta         ,
          Matrix<double,2,4>& nodesCoordGlob) const
{
    Matrix<double,3,2> B0, B1, B2, B3;
    B0 = calcBi(0, xi, eta, nodesCoordGlob);
    B1 = calcBi(1, xi, eta, nodesCoordGlob);
    B2 = calcBi(2, xi, eta, nodesCoordGlob);
    B3 = calcBi(3, xi, eta, nodesCoordGlob);

    Eigen::Matrix<double,3,8> B;
    B << B0, B1, B2, B3;

    return B;
}

Matrix<double,2,2>
P4::calcLocK(int i, int j, Matrix<double,2,4> &nodesCoordGlob) const
{

    Eigen::Matrix<double,2,2> locK;

    double xi, eta, weight;
    Matrix<double,3,2> Bi, Bj;
    // !!!Jacobian matrix is calculated many times
    Matrix<double,2,2> jacobianMatrix;

    locK.setZero();
    Bi.setZero();
    Bj.setZero();
    jacobianMatrix.setZero();

    for (int k=0; k<_quadraturePoints.cols(); ++k)
    {

        xi     = _quadraturePoints(0,k);
        eta    = _quadraturePoints(1,k);
        weight = _quadratureWeights(0,k);

        Bi = calcBi(i, xi, eta, nodesCoordGlob);
        Bj = calcBi(j, xi, eta, nodesCoordGlob);

        jacobianMatrix = calcJacobianMatrix(xi, eta, nodesCoordGlob);

        locK += weight*Bi.transpose()*_D*Bj*jacobianMatrix.determinant();
    }

    return locK;
}

//void P4::updateForce(Eigen::Matrix<double,2,4> &nodesCoordGlob,
//                     Eigen::VectorXd &u                       ,
//                     Eigen::VectorXd &force                   ) const
//{
//    for (int k=0; k<mQuadraturePoints.cols(); ++k)
//    {
//        double xi  = mQuadraturePoints(0,k);
//        double eta = mQuadraturePoints(1,k);
//
//        Eigen::Matrix<double,3,8> B = calcB(xi, eta, nodesCoordGlob);
//
//        Eigen::VectorXd sigma = mD*B*u;
//
//
//        double weight = mQuadratureWeights(0,k);
//        auto jacobianMatrix = calcJacobianMatrix(xi, eta, nodesCoordGlob);
//
//        force -= weight*B.transpose()*sigma*jacobianMatrix.determinant();
//    }
//}

Matrix<double,3,3> P4::getD() const
{
    return _D;
}

