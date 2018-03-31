/*
 * exportToVtp.hpp
 *
 *  Created on: Mar 24, 2017
 *      Author: pavel
 */

#ifndef TESTIMPORTTOVTP_H_
#define TESTIMPORTTOVTP_H_

#include "../includes.hpp"

#include "includesVtk.h"

void
exportToVtp(Odb* odb)
{

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid =
            vtkSmartPointer<vtkUnstructuredGrid>::New();


    std::vector<Node*> nodes;
    nodes = odb->getMesh()->getNodes();

    vtkSmartPointer<vtkPoints> points =
            vtkSmartPointer<vtkPoints>::New();

    for (auto it=nodes.begin(); it<nodes.end(); ++it)
    {
        double* coord;
        coord = (*it)->getCoord();
        points->InsertNextPoint(coord[0], coord[1], 0.0);
        delete [] coord;
    }

    unstructuredGrid->SetPoints(points);


    std::vector<Element*> elements;
    elements = odb->getMesh()->getElements();

    vtkSmartPointer<vtkCellArray> cellArray =
            vtkSmartPointer<vtkCellArray>::New();

    for (auto it=elements.begin(); it<elements.end(); ++it)
    {
        int* connect;
        connect = (*it)->getConnect();

        vtkSmartPointer<vtkQuad> quad = vtkSmartPointer<vtkQuad>::New();
        for (int i=0; i<(*it)->getType()->getNodesNum(); ++i)
        {
            quad->GetPointIds()->SetId(i,connect[i]);
        }

        cellArray->InsertNextCell(quad);
    }

    unstructuredGrid->SetCells(VTK_QUAD, cellArray);


    vtkSmartPointer<vtkDoubleArray> field =
        vtkSmartPointer<vtkDoubleArray>::New();
    field->SetName("U");
    field->SetNumberOfComponents(2);
    field->SetNumberOfTuples(odb->getMesh()->getNodesNum());

    for (int i=0; i<odb->getMesh()->getNodesNum(); ++i)
    {
        double touple[2];
        touple[0] = odb->getField(Symbol::Output::U)[2*i  ];
        touple[1] = odb->getField(Symbol::Output::U)[2*i+1];
        field->SetTuple(i,touple);
    }

    unstructuredGrid->GetPointData()->AddArray(field);


    // Write file
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    writer->SetFileName("odb.vtu");
    writer->SetInputData(unstructuredGrid);
    writer->SetDataModeToAscii();
    writer->Write();

}



/* Programable filter

scaleFactor = 1000

pdi = self.GetInput ()
pdo = self.GetOutput()

pdo.ShallowCopy(pdi)

pointsNum = input.GetNumberOfPoints()
newPoints = vtk.vtkPoints()

for i in range(0, pointsNum):
    coord = pdi.GetPoint(i)
    x, y, z = coord[:3]
    dx = input.GetPointData().GetArray(0).GetValue(2*i  )
    dy = inptu.GetPointData().GetArray(0).GetValue(2*i+1)
    dz = 0
    x += scaleFactor*dx
    y += scaleFactor*dy
    z += scaleFactor*dz
    newPoints.InsertPoint(i, x, y, z)

pdo.SetPoints(newPoints)
*/



#endif /* TESTIMPORTTOVTP_H_ */
