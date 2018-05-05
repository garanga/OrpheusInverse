#include "includes.hpp"
#include "Vtk/exportToVtp.h"

    /*
    std::cout << "To use a part with vtk one should do the following: \n"
              << "1. install vtk \n"
              << "   (the headers shold be in /usr/local/include/vtk-**)"
              << "    the shared libs in /usr/local/lib"
              << "2. add the headers path to Project -> Properties "
              << "3. add the following libs in Project -> Properties:"
              << "   vtkCommonCore-7.1"
              << "   vtkRenderingCore-7.1"
              << "   vtkCommonDataModel-7.1"
              << "   vtkCommonExecutionModel-7.1"
              << "   vtkIOXML-7.1"
              << "   vtkRenderingOpenGL2-7.1"
              << "   vtkInteractionStyle-7.1"
              << "Note, that my vtk version is 7.1"
              << "4. add LD_LIBRARY_PATH = /usr/local/lib to"
              << "   Project -> Properies -> Environment"
              <<std::endl;
     */

int main()
{

    std::string modelName    = "BaseModel";
    std::string materialName = "Steel";
    std::string meshName     = "LS_PrePostMesh";
    std::string jobName      = "FirstJob";


//    try
//    {

    Model* model = new Model(modelName);

    // Base material
    Material* material1;
    material1 = new Isotropic(materialName, 200.0e9, 0.25);

    // Element Type
    Symbol::ElementType elementTypeSymbol;
    elementTypeSymbol = Symbol::ElementType::P4;

    std::string path = "LS_PrePost200.k";

    model->importMeshFromK(path,material1,elementTypeSymbol);
    Mesh* mesh = model->getMesh();

    Material* material2;
    material2 = new Isotropic("Void", 2.0e9, 0.25);

    ElementSet* elementSet;
    elementSet = mesh->getElementSet("ElementSet_1");

    std::vector<int> set;
    set = elementSet->getSet();

    for (auto it=set.begin(); it<set.end(); ++it)
    {
        if (*it!=-1)
        {
            mesh->getElement(*it)->getType()->modfMaterial(material2);
        }

    }

    // Boundary conditions

    std::vector<int> region;
    double*          value ;

//    region.push_back(0);
    region.push_back(0);
    value = new double[2];
    value[0] = 0.0;
    value[1] = 0.0;

    model->createConstraint("Constraint-1",
                            region,
                            Symbol::DisplacementConstraint::UXY,
                            value);

    region.clear();


//    region.push_back(230);
    region.push_back(20300);
    value = new double[2];
    value[0] = 0.0;
    value[1] = 0.0;

    model->createConstraint("Constraint-2",
                            region,
                            Symbol::DisplacementConstraint::UY,
                            value);

    region.clear();


//    region.push_back(210);
    region.push_back(20100);
    value = new double[2];
    value[0] =-200.0e6;
    value[1] =   0.0  ;

    model->createConcentratedForce("Load-1",
                                   region,
                                   Symbol::ConcentratedForce::FX,
                                   value);

    region.clear();


//    region.push_back(440);
    region.push_back(40400);
    value = new double[2];
    value[0] = 200.0e6;
    value[1] =   0.0  ;

    model->createConcentratedForce("Load-2",
                                   region,
                                   Symbol::ConcentratedForce::FX,
                                   value);

    region.clear();



    Job* job = new Job(jobName, model);
    Odb* odb = job->submit();

    std::cout << odb->getField(Symbol::Output::U)[2*20100  ] << std::endl;
    std::cout << odb->getField(Symbol::Output::U)[2*20100+1] << std::endl;

    exportToVtp(odb);

    return 0;
}
