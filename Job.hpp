/*
 * Job.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: pavel
 */

#ifndef JOB_HPP_
#define JOB_HPP_

#include <string>

class Model;
class Odb;

class Job
{
public:

    Job(std::string, Model*);
   ~Job();

   Odb*
   submit();

private:

    std::string _name ;
    Model*      _model;
};


#endif /* JOB_HPP_ */
