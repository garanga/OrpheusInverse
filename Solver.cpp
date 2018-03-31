/*
 * Solver.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: pavel
 */

#include "Solver.hpp"

#include "includes.hpp"

typedef Triplet<double> T;

Solver::Solver(Mesh*                    mesh       ,
               std::vector<Constraint*> constraints,
               std::vector<Load*>       loads       )
    : _mesh(mesh), _constraints(constraints), _loads(loads)
{
    _nodesNum = _mesh->getNodesNum();
}

Solver::~Solver()
{
    /*
     *
     * Mesh*, std::vector<Constraint*>, std::vector<Load*>
     * will be deleted outside
     *
     */
}

void
Solver::solve(Odb* odb)
{

//    VectorXd u     = VectorXd::Zero(2*_nodesNum);

    // Initialize global stiffness matrix
    SparseMatrix<double> globK(2*_nodesNum,2*_nodesNum);
    globK = calcGlobK();

    // Apply prescribed loads
    VectorXd force = VectorXd::Zero(2*_nodesNum);
    applyLoads(_loads, force);

    // Apply prescribed constraints
    applyConstraints(_constraints, globK, force);

    SparseLU<SparseMatrix<double>> linearEquationsSolver(globK);
    VectorXd sol = linearEquationsSolver.solve(force);

    std::vector<double> fieldValue(sol.data(), sol.data()+sol.rows()*sol.cols());
    odb->addField(Symbol::Output::U,fieldValue);
    fieldValue.clear();

    }

SparseMatrix<double>
Solver::calcGlobK() const
{
    std::vector<T> triplets;

    int*    connect;
    double* coord;
    int     elementNodesNum;
    Matrix<double,2,4> nodesCoordGlob;

    int k,l;

    Matrix<double,2,2> locK;

    std::vector<Node*>    nodes    = _mesh->getNodes();
    std::vector<Element*> elements = _mesh->getElements();

    for (auto it = elements.begin(); it < elements.end(); it++)
    {
        connect         = (*it)->getConnect();
        elementNodesNum = (*it)->getType()->getNodesNum();

        for (int i=0; i<elementNodesNum; i++)
        {
            coord = nodes[connect[i]]->getCoord();
            nodesCoordGlob(0,i) = coord[0];
            nodesCoordGlob(1,i) = coord[1];
        }

        for (int i=0; i<elementNodesNum; i++)
        {
            k = connect[i];
            for (int j=0; j<elementNodesNum; j++)
            {
                l = connect[j];
                locK = (*it)->getType()->calcLocK(i,j,nodesCoordGlob);

                triplets.push_back(T(2*k  ,2*l  ,locK(0,0)));
                triplets.push_back(T(2*k  ,2*l+1,locK(0,1)));
                triplets.push_back(T(2*k+1,2*l  ,locK(1,0)));
                triplets.push_back(T(2*k+1,2*l+1,locK(1,1)));

            }
        }
    }

    SparseMatrix<double> globK(2*_mesh->getNodesNum(), 2*_mesh->getNodesNum());

    globK.setFromTriplets(triplets.begin(), triplets.end());

    return globK;
}

void
Solver::applyLoads(std::vector<Load*>& loads, VectorXd& force)
{
    // Apply prescribed loads
    for (auto it = loads.begin(); it < loads.end(); ++it)
    {
        std::vector<unsigned> indices;
        std::vector<double>   values;

        if (static_cast<int>((*it)->getType()) &
            static_cast<int>(Symbol::ConcentratedForce::FX))
        {
            std::vector<int> region = ((*it)->getRegion());
            for (unsigned i=0; i < region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 0;
            }
            indices.insert(indices.end(),region.begin(),region.end());

            std::vector<double> value(region.size(),(*it)->getValue()[0]);
            values.insert(values.end(),value.begin(),value.end());
        }

        if (static_cast<int>((*it)->getType()) &
            static_cast<int>(Symbol::ConcentratedForce::FY))
        {
            std::vector<int> region = ((*it)->getRegion());
            for (unsigned i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 1;
            }
            indices.insert(indices.end(),region.begin(),region.end());

            std::vector<double> value(region.size(),(*it)->getValue()[1]);
            values.insert(values.end(),value.begin(),value.end());
        }

        for (unsigned int k = 0; k < force.size(); ++k)
        {
            for (unsigned int i = 0; i < indices.size(); ++i)
            {
                if (k == indices[i])
                    force(k) += values[i];
            }
        }
    }
}

void Solver::applyConstraints(std::vector<Constraint*>& constraints,
                              SparseMatrix<double>&     globK      ,
                              VectorXd&                 force       )
{
    for (auto it = constraints.begin(); it < constraints.end(); ++it)
    {
        std::vector<unsigned> indices;
        std::vector<double>   values;

        if (static_cast<int>((*it)->getType()) &
            static_cast<int>(Symbol::DisplacementConstraint::UX))
        {
            std::vector<int> region = ((*it)->getRegion());
            for (unsigned int i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 0;
            }
            indices.insert(indices.end(),region.begin(),region.end());
            std::vector<double> value(region.size(),(*it)->getValue()[0]);
            values.insert(values.end(),value.begin(),value.end());
        }

        if (static_cast<int>((*it)->getType()) &
            static_cast<int>(Symbol::DisplacementConstraint::UY))
        {
            std::vector<int> region = ((*it)->getRegion());
            for (unsigned int i=0; i<region.size(); ++i)
            {
                region[i] *= 2;
                region[i] += 1;
            }
            indices.insert(indices.end(),region.begin(),region.end());
            std::vector<double> value(region.size(),(*it)->getValue()[1]);
            values.insert(values.end(),value.begin(),value.end());
        }

        // Compressed sparse column
        for (unsigned k=0; k<globK.outerSize(); ++k)
        {
            for (SparseMatrix<double>::InnerIterator it(globK,k); it; ++it)
            {

//                std::cout << it.row() << "\t" << it.col() << std::endl;

                for (unsigned i=0; i<indices.size(); ++i)
                {
                    if (it.row() == indices[i])
                        it.valueRef() = it.row() == it.col() ? 200.0e9 : 0.0;
                }
            }
        }

        for (unsigned i=0; i<indices.size(); ++i)
        {
            force(indices[i]) = values[i]*200.0e9;
        }

    }
}
