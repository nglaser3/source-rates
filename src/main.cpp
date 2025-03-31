/*#include "InputParameters.hpp"
#include "DepleteMatrix.hpp"
#include "CRAMSolver.hpp"*/
#include "petscksp.h"

int main(int argc, char **argv)
{
    /*PetscMPIInt size;
    PetscBool flg;
    char temp_name[PETSC_MAX_PATH_LEN];

    PetscCall(PetscInitialize(&argc, &argv, NULL, NULL));
    PetscCallMPI(MPI_Comm_size(PETSC_COMM_WORLD, &size));
    PetscCall(PetscOptionsGetString(NULL, NULL, "-input", temp_name, sizeof(temp_name), &flg));
    
    //Getting inputs from input file
    std::string filename(temp_name);
    InputParameters params(filename);

    //Initializing matrices and solver
    DepleteMatrix matrix(params.getDecayChain(), params.getFlux());
    CRAMSolver CRAM(matrix.getMatrix(), params.getCRAMOrder());

    //Performing the CRAM Solve
    std::vector<PetscReal> d_times(params.getTimeSteps());
    for (auto dt : d_times)
    {
        CRAM.stepSolve(dt);
    }

    CRAM.finalize();

    ~matrix();
    ~CRAM();

    PetscCall(PetscFinalize());*/

    return 0;
}