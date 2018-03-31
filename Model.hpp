/*
 * Model.hpp
 *
 *  Created on: Jan 17, 2017
 *      Author: pavel
 */

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <string>
#include <vector>

class Material;
class ElementType;
class Mesh;
class Constraint;
class Load;

namespace Symbol
{
    enum class DisplacementConstraint;
    enum class ConcentratedForce;
}

class Model
{
public:

    //! Specialized constructor
     Model(std::string);
    ~Model();

//    // A method for creating a Material object
//    void
//    createIsotropic(std::string, double, double);

    // A method for importing a Mesh from LS-PrePost k-file
    void
    importMeshFromK(std::string,Material*,ElementType*);

    void
    createConstraint(std::string                   ,
                     std::vector<int>              ,
                     Symbol::DisplacementConstraint,
                     double*                       );

    void
    createConcentratedForce(std::string              ,
                            std::vector<int>         ,
                            Symbol::ConcentratedForce,
                            double*                   );



//
//    //! A method for creating a StaticStep object
//    StaticStep*
//    createStaticStep(std::string, double, double, double, double, double);
//
//    void
//    setMaterialToPart(std::string, std::string);
//
//    std::string
//    getName() const;
//
//    /*
//    Body*
//    getBody(std::string);
//    */
//
//    Part*
//    getPart(std::string);
//
    Material*
    getMaterial() const;

    ElementType*
    getElementType() const;

    Mesh*
    getMesh() const;

    std::vector <Constraint*>
    getConstraints() const;

    std::vector <Load*>
    getLoads() const;


private:

    std::string               _name;
    Mesh*                     _mesh;
    std::vector <Constraint*> _constraints;
    std::vector <Load*>       _loads;

};

#endif /* MODEL_HPP_ */
