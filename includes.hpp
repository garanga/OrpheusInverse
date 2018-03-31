/*
 * includes.hpp
 *
 *  Created on: Mar 10, 2018
 *      Author: pavel
 */

#ifndef INCLUDES_HPP_
#define INCLUDES_HPP_

#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Symbol.hpp"

#include "Model.hpp"

#include "MaterialLib/Material.hpp"
#include "MaterialLib/Isotropic.hpp"

#include "Mesh.hpp"
#include "Node.hpp"
#include "Element.hpp"

#include "Element.hpp"
#include "ElementLib/P4.hpp"

#include "Constraint.hpp"

#include "Load.hpp"
#include "ConcentratedForce.hpp"
#include "ConcentratedForce.hpp"

#include "Job.hpp"
#include "Solver.hpp"

#include "Odb.hpp"

#include "Eigen/Dense"
#include "Eigen/Sparse"
using namespace Eigen;

#endif /* INCLUDES_HPP_ */
