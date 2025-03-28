#include "DepleteMatrix.hpp"

DepleteMatrix::DepleteMatrix(std::string filepath, double flux)
{
    getIsotopesFromFile(filepath, flux);

    setNNZ();

    PetscCall(MatCreateSeqAIJ(/*MPI Comm*/ PETSC_COMM_SELF, //single thread
                              /*# Rows*/ _num_isos,
                              /*# Cols*/ _num_isos,
                              /*nz*/ 0, // set to 0, bypass nz to nnz
                              /*nnz*/ this->_nnz,
                              /*Mat*/ &_depl_matrix));
    fillDepleteMatrix();
}

void
DepleteMatrix::getIsotopesFromFile(std::string filepath, double flux)
{
    std::cout<<"Opening file \"" + filepath + "\""<<std::endl;
    pugi::xml_document doc;

    if (!doc.load_file(filepath))
    {
        std::cout<<"Could not open file \"" + filepath + "\", please ensure 
        this is in the correct XML format!";
    }

    std::cout<<"Succesfully opened \"" + filepath + "\", starting to read"<<std::endl;
    
    unsigned num_nodes = 0;
    for (auto & node : doc.child("depletion_chain"))
    {
        num_nodes += 1;
        
        Isotope current_isotope(node, flux);
        this->_isotopes.pushback(current_isotope);
    }

    if (!(num_nodes > 0))
    {
        throw std::invalid_argument("\"" + filepath + "\" does not have the
            correct format. The root should be \"depletion_chain\" and is not!");
    }

    std::cout<<"Succesfully read " + std::to_string(num_nodes) + " Isotopes"<<std::endl;
}

void
DepleteMatrix::setNNZ()
{
    int nnz[this->_isotopes.size()];

    for (int i = 0; i < _isotopes.size(); i++)
    {
        nnz[i] = _isotopes.at(i).getNumCols();
    }

    this->_nnz = nnz;
}

void
DepleteMatrix::fillDepleteMatrix()
{
    for (auto isotope : this->_isotopes)
    {
        PetscCall( MatSetValues(/*Mat*/ this->_matrix, 
                                /*Num Rows*/ 1,
                                /*Row Indices*/ isotope.getRowID(), //this should be arr of len num cols
                                /*Num Cols*/ isotope.getNumCols(),
                                /*Col Indices*/ isotope.getColIDs(),
                                /*Values*/ isotope.getValues(),
                                /*Insert Mode*/ INSERT_VALUES) );
    }
    PetscCall(MatAssemblyBegin(this->_matrix, MAT_FINAL_ASSEMBLY));
    PetscCall(MatAssemblyEnd(this->_matrix, MAT_FINAL_ASSEMBLY));
}

Mat
DepleteMatrix::getMatrix()
{
    return this->_matrix;
}