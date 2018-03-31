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

    Material* material;
    material = new Isotropic(materialName, 200.0e9, 0.25);

    ElementType* elementType;
    elementType = new P4(material->getYoung(), material->getPoisson());

    std::string path = "LS_PrePost200.k";

    model->importMeshFromK(path,material,elementType);

//    Mesh* mesh = model->getMesh();
//    std::cout << mesh->getNodes().size() << std::endl;
//    std::cout << mesh->getElements().size() << std::endl;

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

    exportToVtp(odb);

//    std::vector<double> disp = odb->getField(Symbol::Output::U);
//
//    for (auto it=disp.begin(); it<disp.end(); std::advance(it,2))
//    {
//        std::cout << *(it) << "\t" << *(it+1) << std::endl;
//    }





//        mdb->createJob(jobName, model);
//

//


//    }
//
//    catch (OrpheusException::Exception& exception)
//    {
//        std::cout << "Exception occur \n";
//        std::cout << exception.what() << std::endl;
//    }



    //
//    delete mdb;
//
////    std::cout << "Finish" << std::endl;
//
//    // Test vtk visualization and vtp export
////    importToVtp("Job_1-Output.txt");

    return 0;
}
