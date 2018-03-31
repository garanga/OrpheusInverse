/*
 * SymbolicConstants.hpp
 *
 *  Created on: Feb 1, 2017
 *      Author: pavel
 */

#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

namespace Symbol
{

    enum class DisplacementConstraint
    {
        UX = 1 << 0,
        UY = 1 << 1,
        UXY = UX | UY
    };

    enum class ConcentratedForce
    {
        FX = 1 << 0,
        FY = 1 << 1,
        FXY = FX | FY
    };

    enum class Output
    {
        U = 1
    };

}
#endif /* SYMBOL_HPP_ */
