#pragma once

#include "Isotope.hpp"

#include "petscmat.h"
#include "pugixml.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class DepleteMatrix
{
public:

    DepleteMatrix(std::string filepath, double flux);

    Mat const getMatrix()
    {return this->_matrix};

protected:

    void getIsotopesFromFile(std::string filepath, double flux);

    void setNNZ();

    void fillDepleteMatrix();
    std::vector<Isotope> _isotopes;
    
    PetscInt* _nnz;

    Mat _matrix;
};


