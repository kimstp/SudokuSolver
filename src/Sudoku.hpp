#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <vector>
#include "SudokuSet.hpp"

class Sudoku
{
//private:
public:
    
    /* Representation of block index limits */
    typedef struct {
        unsigned char rowmin;
        unsigned char rowmax;
        unsigned char colmin;
        unsigned char colmax;
    } BlockLimits;
    
public:
	//Sudoku(); // Default constructor not needed
    
    /* Initialize sudoku plate with content of startplate array (assumed to contain 9*9 elements) */
    Sudoku(SudokuSet::SetType* startplate);
	virtual ~Sudoku();
    
    /* Solve the sudoku plate. Return true if solved. */
    bool solve();
    
    /* Print the current plate */
    void printPlate() const;
    
    /* Print the solution set at cel (r, c) */
    void printSolutionSetAt(int r, int c) const;
    
    
    /* Return set with all closed cell elements in the row of cell (r, c) excluding the cell */
    SudokuSet getClosedRowSet(int r, int c) const;
    
    /* Return set with all closed cell elements in the col of cell (r, c) excluding the cell */
    SudokuSet getClosedColSet(int r, int c) const;
    
    /* Return set with all closed cell elements in the block of cell (r, c) excluding the cell */
    SudokuSet getClosedBlockSet(int r, int c) const;
    
    /* Return set with all closed cell elements in the block, row r and col c of cell (r, c) excluding the cell */
    SudokuSet getClosedSet(int r, int c) const;
    
    /* Return set with all open cell elements in the row r of cell (r, c) excluding the cell */
    SudokuSet getOpenRowSet(int r, int c) const;

    /* Return set with all open cell elements in the col c of cell (r, c) excluding the cell */
    SudokuSet getOpenColSet(int r, int c) const;

    /* Return set with all open cell elements in the block of cell (r, c) excluding the cell */
    SudokuSet getOpenBlockSet(int r, int c) const;
    
    /* Return set with all open cell elements in the block, row r and col c of cell (r, c) excluding the cell */
    SudokuSet getOpenSet(int r, int c) const;
    
    /* Remove the set in cell (r,c) from all non-closed cells in the same row r */
    void removeFromOpenRowSet(int r, int c);
    
    /* Remove the set in cell (r,c) from all non-closed cells in the same col c */
    void removeFromOpenColSet(int r, int c);
    
    /* Remove the set in cell (r,c) from all non-closed cells in the same block */
    void removeFromOpenBlockSet(int r, int c);
    
    /* Remove the set in cell (r,c) from all non-closed cells in the same block, row r, and col c */
    void removeFromOpenSet(int r, int c);
    
    /* Remove the set in U from all non-closed cells in the row r but not in the same block as cell (r,c) */
    void removeFromOpenNonBlockRowSet(int r, int c, SudokuSet const &U);
    
    /* Remove the set in U from all non-closed cells in the col c but not in the same blovk as cell (r,c) */
    void removeFromOpenNonBlockColSet(int r, int c, SudokuSet const &U);


    /* Return unique element of cell (r,c) in the row of the cell.
     If no unique element exist return empty set.
     */
    SudokuSet uniqueRowElement(int r, int c) const;

    /* Return unique element of cell (r,c) in the col of the cell.
     If no unique element exist return empty set.
     */
    SudokuSet uniqueColElement(int r, int c) const;

    /* Return unique element of cell (r,c) in the block of the cell.
       If no unique element exist return empty set.
     */
    SudokuSet uniqueBlockElement(int r, int c) const;
    
    /* Return elements in block row of cell (r,c) which are unique in the block. 
       If no unique element exist return empty set.
     */
    SudokuSet uniqueInBlockRowElement(int r, int c) const;
    
    /* Return elements in block col of cell (r,c) which are unique in the block.
     If no unique element exist return empty set.
     */
    SudokuSet uniqueInBlockColElement(int r, int c) const;
    
    /* Return the index limits of the block that cell (r, c) belongs to */
    BlockLimits findBlock(int r, int c) const;
    
    /* Check if current plate is a valid solution
     * TODO: There is a bug in the check for the game rules. Appears to be in isConstraintSatisfied
     */
    bool isSolution() const;

    /* Prune the sudoku solution set by enforcing the game rules*/
    void pruneSolution();
    
    /* Comparison operators */
    bool operator==(Sudoku const &B) const;
    bool operator!=(Sudoku const &B) const;

private:

    /* Check if all cells of current plate are closed */
    bool isAllClosed() const;
    
    /* Return the sum of all closed elements */
    int closedElemSum() const;
    
    /* Return true if constraints / rules are satisfied (a valid solution) */
    bool isConstraintsSatisfied() const;

    
    /* Representation of a sudoku plate as a 2D array of SudokuSets */
    std::vector< std::vector<SudokuSet> > _plate;
    
};

#endif //_SUDOKU_H_
