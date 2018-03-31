/*
 * Solver.hpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#ifndef SOLVER_HPP_
#define SOLVER_HPP_

#include "Eigen/Dense"
#include "Eigen/Sparse"
using namespace Eigen;

#include <vector>

class Mesh;
class Constraint;
class Load;
class Odb;

class Solver
{
public:

     explicit
     Solver(Mesh*, std::vector<Constraint*>, std::vector<Load*>);
    ~Solver();

    void
    solve(Odb*);

private:

    Mesh*                    _mesh       ;
    std::vector<Constraint*> _constraints;
    std::vector<Load*>       _loads;

    int _nodesNum;

    SparseMatrix<double>
    calcGlobK() const;

    void
    applyLoads(std::vector<Load*>&, VectorXd&);

    void
    applyConstraints(std::vector<Constraint*>&,
                     SparseMatrix<double>&    ,
                     VectorXd&                 );
};


#endif /* SOLVER_HPP_ */
