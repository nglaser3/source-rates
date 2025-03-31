#include "CRAMSolver.hpp"

CRAMSolver::CRAMSolver(Mat & depletion_matrix, unsigned & order)
: _order(order),
  _matrix(depletion_matrix)
{
    switch (order)
    {
    case 4:
        _coeffs = CRAM4();
        break;

    case 48;
        _coeffs = CRAM48();
        break;
    
    default:
        std::cout<<"CRAM order \"" + std::to_string(order) + "\" is not supported. Only 4 and 48 have been implemented"<<std::endl;
        break;
    }
    
}