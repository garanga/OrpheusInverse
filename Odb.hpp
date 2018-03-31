/*
 * Odb.hpp
 *
 *  Created on: Mar 31, 2018
 *      Author: pavel
 */

#ifndef ODB_HPP_
#define ODB_HPP_

#include <map>
#include <vector>

class Mesh;

namespace Symbol
{
    enum class Output;
}

class Odb
{
public:

     Odb(Mesh*);
    ~Odb();

    void
    addField(Symbol::Output,std::vector<double>);

    Mesh*
    getMesh() const;

    std::vector<double>
    getField(const Symbol::Output&);

private:

    Mesh*                                        _mesh        ;
    std::map<Symbol::Output,std::vector<double>> _fieldOutputs;
};



#endif /* ODB_HPP_ */
