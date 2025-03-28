#include "pugixml.hpp"

#include <string>
#include <vector>

class Isotope
{
public:

    Isotope(PetscInt id, pugi::xml_node & node, PetscReal flux);

/*Basic Getter Functions*/
    /* Matrix Filling*/
    PetscInt* getRowID() const
    {return this->_row_id};

    PetscInt getNumCols() const
    {return this->_num_cols};

    PetscInt* getColIDs() const
    {return this->_col_ids};

    PetscReal* getValues() const
    {return this->_insert_values}; 

    /*File Reading*/
    std::string getMyName() const
    {return this->_my_name};

    std::vector<std::string> getChildrenNames() const
    {return this->_children_names};

    std::vector<PetscReal> getChildrenCoeffs() const
    {return this->_coeffs_to_children};

/*Called by Matrix class to fill in relevant data*/
    /**
     * Push back _parent_ids and _parent_values
     * with the id and coefficient, respectively.
     * @param id the ID of the parent
     * @param value the coefficient from parents to me
     */
    void setParentData(PetscInt id, PetscReal value);

    /**
     * Finalizes the Isotope. This puts all dynamic data
     * into the static arrays required by Petsc Matrices.
     */
    void finalize();

protected:

    /**
     * Pulls the data out of the xml node
     * @param node the xml node to read from
     */
    void readNode(pugi::xml_node & node);

    /**
     * Interfaces with NJOY21 to find the
     * reaction rates (n,x) for transmute
     * type reactions. Pushes back _coeffs_to_children
     * and _children_names with the reaction rate
     * coefficients and names respectively. 
     * @param flux the neutron flux to evaluate 
     * the reaction rates at
     */
    void getReactionRates(PetscReal flux);

    PetscInt _id;

    std::string _my_name;
    
    std::vector<std::string> _children_names;

    std::vector<PetscReal> _coeffs_to_children;

    std::vector<PetscInt> _parent_ids;

    std::vector<PetscReal> _parent_values;

    /*Static arrays for petsc*/

    PetscInt* _row_id;

    PetscInt _num_cols;

    PetscInt* _col_ids;

    PetscReal* _insert_values;
};
