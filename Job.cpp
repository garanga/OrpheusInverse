/*
 * Job.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: pavel
 */

#include "Job.hpp"

#include "includes.hpp"

#include <iostream>
#include <string>
#include <time.h>

Job::Job(std::string name, Model* model)
    : _name(name), _model(model)
{
    std::cout << "A job is created" << std::endl;
    std::cout << "\t" << "Job name is " << _name << std::endl;
    std::cout << std::endl;
}


Job::~Job()
{
}

Odb*
Job::submit()
{

    std::cout << "Job " << _name << " is submitted for analysis" << std::endl;
    std::cout << "Please wait ... ";
    std::cout << std::endl;

    Solver* solver = new Solver(_model->getMesh()       ,
                                _model->getConstraints(),
                                _model->getLoads()       );

    time_t time1;
    time(&time1);

    Odb* odb = new Odb(_model->getMesh());

    solver->solve(odb);

    time_t time2;
    time(&time2);

    std::cout << "Job " << _name << " is completed" << std::endl;
    std::cout << "Time for job execution is " << time2-time1 << "s" << std::endl;

    return odb;

}
