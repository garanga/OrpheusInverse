/*
 * Model.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#include "Model.hpp"

#include "includes.hpp"

Model::Model(std::string name)
    : _name(name)
{
    _mesh        = nullptr;

    std::cout << "A model is created" << std::endl;
    std::cout << "\t" << "Model name is " << _name << std::endl;
    std::cout << std::endl;
}

Model::~Model()
{
    delete _mesh;
    for (auto it = _constraints.begin(); it != _constraints.end(); ++it)
        delete *it;
    for (auto it = _loads.begin(); it != _loads.end(); ++it)
        delete *it;
}

//void
//Model::createIsotropic(std::string name, double young, double poisson)
//{
//    Isotropic* material = new Isotropic(name, young, poisson);
//    _material = material;
//}

void
Model::importMeshFromK(std::string  path,
                       Material*    material,
                       ElementType* elementType)
{
    _mesh = new Mesh();

    std::ifstream fin;
    fin.open(path);

    int     nid;
    double* coord;
    Node*   node;

    int      eid;
    int*     connectivity;
    Element* element;

    std::string line;
    std::size_t pos ;

    while(std::getline(fin,line))
    {

        // Is the line contains *NODE keyword
        pos = line.find("*NODE");
        if (pos!=std::string::npos) // Bingo
        {
            while(getline(fin,line))
            {
                pos = line.find("*");
//                std::cout << line << std::endl;

                if (pos==std::string::npos)
                {
                    std::istringstream iss(line);
                    std::string par1,par2,par3;

                    coord = new double[2];

                    iss >> par1 >> par2 >> par3;

                    nid      = std::stoi(par1)-1;   // !!!
                    coord[0] = std::stod(par2)  ;
                    coord[1] = std::stod(par3)  ;

                    node = new Node(nid,coord);

                    _mesh->addNode(node);

//                    delete node;
                    coord = nullptr;    // Already deleted in ~Node

                }
                else
                {
                    break;
                }
            }
        }

    }

    fin.clear();
    fin.seekg(0, std::ios::beg);

    // Searching for elements
    while(std::getline(fin,line))
    {

        // Is the line contains *ELEMENT_SHELL keyword
        pos = line.find("*ELEMENT_SHELL");
        if (pos!=std::string::npos) // Bingo
        {
            while(getline(fin,line))
            {
                pos = line.find("*");
//                std::cout << line << std::endl;

                if (pos==std::string::npos)
                {
                    std::istringstream iss(line);
                    std::string par1,par2,par3,par4,par5,par6;

                    connectivity = new int[4];

                    iss >> par1 >> par2 >> par3 >> par4 >> par5 >> par6;

                    eid      = std::stoi(par1);
                    connectivity[0] = std::stod(par3)-1;
                    connectivity[1] = std::stod(par4)-1;
                    connectivity[2] = std::stod(par5)-1;
                    connectivity[3] = std::stod(par6)-1;

                    element = new Element(eid,
                                          connectivity,
                                          material,
                                          elementType);

                    _mesh->addElement(element);

//                    delete element;
                    connectivity = nullptr; // Already deleted in ~Element

                }
                else
                {
                    break;
                }
            }
        }

    }

    fin.close();

}

void
Model::createConstraint(std::string                    name  ,
                        std::vector<int>               region,
                        Symbol::DisplacementConstraint type  ,
                        double*                        value )
{
    auto constraint = new Constraint(name  ,
                                     region,
                                     type  ,
                                     value );
    _constraints.push_back(constraint);
}

void
Model::createConcentratedForce(std::string               name  ,
                               std::vector<int>          region,
                               Symbol::ConcentratedForce type  ,
                               double*                   value )
{
    auto load = new ConcentratedForce(name  ,
                                      region,
                                      type  ,
                                      value );
    _loads.push_back(load);
}







//
//StaticStep*
//Model::createStaticStep(std::string name,
//                        double timeBegin,
//                        double timeEnd,
//                        double timeIncrement,
//                        double loadFactorBegin,
//                        double loadFactorEnd)
//{
//    StaticStep* step = new StaticStep(name, timeBegin, timeEnd, timeIncrement, loadFactorBegin, loadFactorEnd);
//    steps.push_back(step);
//    return step;
//}
//
//void
//Model::setMaterialToPart(std::string materialName, std::string partName)
//{
//    auto materialIt = std::find_if(materials.begin(),materials.end(),
//                      [&materialName](Material* material)
//                      {
//                          return material->getName() == materialName;
//                      });
//
//    auto partIt = std::find_if(parts.begin(),parts.end(),
//                  [&partName](Part* part)
//                  {
//                      return part->getName() == partName;
//                  });
//
//    bool materialFlag = materialIt == materials.end();
//    bool partFlag =  partIt == parts.end();
//
//    if (materialFlag)
//    {
//        std::string message("Material with name <");
//        message += materialName;
//        message += "> not found";
//        // in includes.hpp it is written that
//        // namespace except = OrpheusException;
//        throw except::Exception(Symbol::ExceptionType::NOMATERIAL,
//                                message);
//    }
//
//    if (partFlag)
//    {
//        std::string message("Part with name <");
//        message += partName;
//        message += "> not found";
//        throw except::Exception(Symbol::ExceptionType::NOPART,
//                                message);
//    }
//
//    (*partIt)->setMaterial((*materialIt));
//
//    std::cout << materialName << " is set to " << partName << std::endl;
//
//}
//
//std::string
//Model::getName() const
//{
//    return _name;
//}
//
///*


Mesh*
Model::getMesh() const
{
    return _mesh;
}

std::vector <Constraint*>
Model::getConstraints() const
{
    return _constraints;
}

std::vector <Load*>
Model::getLoads() const
{
    return _loads;
}



//
//StaticStep*
//Model::getStatciStep(std::string name)
//{
//    auto it = std::find_if(steps.begin(),steps.end(),
//              [&name](StaticStep* step)
//              {
//                  return step->getName() == name;
//              });
//    return *it;
//}