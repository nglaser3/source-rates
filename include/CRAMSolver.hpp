#pragma once

#include "CRAMCoefficients.hpp"
#include "DepleteMatrix.hpp"

#include "petscmat.h"
#include "petscksp.h"

enum CRAMSolveOrder
{
    order4 = 4, 
    order48 = 48
}


class CRAMSolver
{
public:

    CRAMSolver(Mat & depletion_matrix, CRAMSolveOrder & order);

    ~CRAMSolver();

    void stepSolve(PetscReal delta_t);

protected:

    void storeResultsInner();

    void finalize();

    unsigned _order;

    Mat _matrix;

    CRAMCoefficients _coeffs;

    KSP ksp;

    Vec _n_initial, _n_current, _exact;
};

