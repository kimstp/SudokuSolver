#include "Sudoku.hpp"

#include <iostream>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;



Sudoku::Sudoku(SudokuSet::SetType* startplate)
{
    for (int r=0; r < 9; r++)
    {
        vector<SudokuSet> row;
        for (int c=0; c < 9; c++)
        {
            if (startplate[r*9+c])
            {
                SudokuSet A(true);
                A.addElement(startplate[r*9+c]);        
                row.push_back(A);
            }
            else
            {
                SudokuSet A;            
                row.push_back(A);
            }
        }
        _plate.push_back(row);
    }
}


Sudoku::~Sudoku()
{
}


void Sudoku::pruneSolution()
{
    bool bChanged = true;
    while (bChanged)
    {
        Sudoku oldPlate(*this);
        std::cout << "Prune solution loop" << std::endl;
        for (int r=0; r < 9; r++)
        {
            for (int c=0; c < 9; c++)
            {
                if (!_plate[r][c].isClosed()) {
                    SudokuSet R(true);
                    R = getClosedSet(r, c);
                    _plate[r][c] = _plate[r][c].difference(R);
                }

                // If set got closed remove it from others
                if (_plate[r][c].isClosed())
                    removeFromOpenSet(r, c);

            }
        }
        
        bChanged = ((*this)!=oldPlate);
    }
}


bool Sudoku::solve()
{
    
    // Main loop
    bool bChanged = true;
    while (bChanged)
    {
        Sudoku oldPlate(*this);
        
        std::cout << std::endl;
        std::cout << "Main solver loop" << std::endl;


        // Initialize and prune the solution plate
        pruneSolution();
        
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
            {

                // Close cells with unique elements in block, row and col
                if (!_plate[r][c].isClosed())
                {
                    SudokuSet U(true);
                    U = uniqueBlockElement(r, c);
                    if (!(U.isEmpty()))
                    {
                        _plate[r][c] = U;
                        removeFromOpenSet(r, c);
                        pruneSolution();
                    }
                }
                
                if (!_plate[r][c].isClosed())
                {
                    SudokuSet U(true);
                    
                    U = uniqueRowElement(r, c);
                    if (!(U.isEmpty()))
                    {
                        _plate[r][c] = U;
                        removeFromOpenSet(r, c);
                        pruneSolution();
                    }
                }

                if (!_plate[r][c].isClosed())
                {
                    SudokuSet U(true);
                    U = uniqueColElement(r, c);
                    if (!(U.isEmpty()))
                    {
                        _plate[r][c] = U;
                        removeFromOpenSet(r, c);
                        pruneSolution();
                    }
                }

                // Identify unique block row / col elements and remove from row / col in other blocks.
                if (!_plate[r][c].isClosed())
                {
                    SudokuSet U(true);
                    U = uniqueInBlockColElement(r, c);
                    if (!(U.isEmpty()))
                    {
                        std::cout << std::endl;
                        std::cout << "uniqueInBlockColElement" << std::endl;
                        removeFromOpenNonBlockColSet(r, c, U);
                        pruneSolution();
                    }
                }

                if (!_plate[r][c].isClosed())
                {
                    SudokuSet U(true);
                    U = uniqueInBlockRowElement(r, c);
                    if (!(U.isEmpty()))
                    {
                        std::cout << std::endl;
                        std::cout << "uniqueInBlockRowElement" << std::endl;
                        removeFromOpenNonBlockRowSet(r, c, U);
                        pruneSolution();
                    }
                }

            }
     
        bChanged = ((*this)!=oldPlate);
        
//        std::cout << std::endl;
//        printPlate();
    }
    
    
    return isSolution();
}




void Sudoku::printPlate() const
{
    for (int r=0; r < 9; r++)
    {
        for (int c=0; c < 9; c++)
        {
            if (_plate[r][c].isClosed())
            {
                cout << (int) _plate[r][c].getSingletonElement() << " ";
            }
            else
            {
                cout << "0 ";
            }
            
            if (fmod(c+1,3)==0.0)
                cout << " ";
        }
        cout << endl;
        
        if (fmod(r+1,3)==0.0)
                cout << endl;
    }
}


void Sudoku::printSolutionSetAt(int r, int c) const
{
    _plate[r][c].printSet();
}
    
SudokuSet Sudoku::getClosedRowSet(int r, int c) const
{
    SudokuSet R(true); // Empty set
    for (int col=0; col < 9; col++)
    {
        if (col != c && _plate[r][col].isClosed())
            R = R.setunion(_plate[r][col]);
    }    
    return R;
}


SudokuSet Sudoku::getClosedColSet(int r, int c) const
{
    SudokuSet C(true); // Empty set
    for (int row = 0; row < 9; row++)
    {
        if (row != r && _plate[row][c].isClosed())
            C = C.setunion(_plate[row][c]);
    }
    return C;
}


SudokuSet Sudoku::getClosedBlockSet(int r, int c) const
{
    SudokuSet B(true); // Empty set
    
    BlockLimits lim = findBlock(r,c);
    
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        for (int col = lim.colmin; col < lim.colmax; col++)
        {
            if (!((row == r) && (col == c)) && _plate[row][col].isClosed())
                B = B.setunion(_plate[row][col]);
        }
    
    return B;
}


SudokuSet Sudoku::getClosedSet(int r, int c) const
{
    SudokuSet R(true); // Empty set
    
    R = getClosedBlockSet(r, c);
    R = getClosedRowSet(r, c).setunion(R);
    R = getClosedColSet(r, c).setunion(R);
    
    return R;
}



SudokuSet Sudoku::getOpenRowSet(int r, int c) const
{
    SudokuSet R(true);  // Empty set
    for (int col=0; col < 9; col++)
    {
        if (col != c && !(_plate[r][col].isClosed()))
            R = R.setunion(_plate[r][col]);
    }
    
    return R;
}


SudokuSet Sudoku::getOpenColSet(int r, int c) const
{
    SudokuSet C(true);  // Empty set
    for (int row = 0; row < 9; row++)
    {
        if (row != r && !(_plate[row][c].isClosed()))
            C = C.setunion(_plate[row][c]);
    }
    
    return C;
}


    
SudokuSet Sudoku::getOpenBlockSet(int r, int c) const
{
    SudokuSet B(true);
    
    BlockLimits lim = findBlock(r,c);
    
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        for (int col = lim.colmin; col < lim.colmax; col++)
        {
            if (!((row == r) && (col == c)) && !(_plate[row][col].isClosed()))
                B = B.setunion(_plate[row][col]);
        }
    
    return B;
}


SudokuSet Sudoku::getOpenSet(int r, int c) const
{
    SudokuSet R(true); // Empty set
    
    R = getOpenBlockSet(r, c);
    R = getOpenRowSet(r, c).setunion(R);
    R = getOpenColSet(r, c).setunion(R);
    
    return R;
}


void Sudoku::removeFromOpenRowSet(int r, int c)
{
    for (int col=0; col < 9; col++)
    {
        if (col != c && !(_plate[r][col].isClosed()))
            _plate[r][col] = _plate[r][col].difference(_plate[r][c]);
    }    
}


void Sudoku::removeFromOpenColSet(int r, int c)
{
    for (int row = 0; row < 9; row++)
    {
        if (row != r && !(_plate[row][c].isClosed()))
            _plate[row][c] = _plate[row][c].difference(_plate[r][c]);
    }
}

void Sudoku::removeFromOpenBlockSet(int r, int c)
{
    BlockLimits lim = findBlock(r,c);
    
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        for (int col = lim.colmin; col < lim.colmax; col++)
        {
            if (!((row == r) && (col == c)) && !(_plate[row][col].isClosed()))
                _plate[row][col] = _plate[row][col].difference(_plate[r][c]);
        }    
}


void Sudoku::removeFromOpenSet(int r, int c)
{
    removeFromOpenBlockSet(r, c);
    removeFromOpenRowSet(r, c);
    removeFromOpenColSet(r, c);
}


void Sudoku::removeFromOpenNonBlockRowSet(int r, int c, SudokuSet const &U)
{
    BlockLimits lim = findBlock(r,c);

    for (int col = 0; col < 9; col++)
        if ((col < lim.colmin || col >= lim.colmax) && !(_plate[r][col].isClosed()))
            _plate[r][col] = _plate[r][col].difference(U);
}

void Sudoku::removeFromOpenNonBlockColSet(int r, int c, SudokuSet const &U)
{
    BlockLimits lim = findBlock(r,c);

    for (int row = 0; row < 9; row++)
        if ((row < lim.rowmin || row >= lim.rowmax) && !(_plate[row][c].isClosed()))
            _plate[row][c] = _plate[row][c].difference(U);
}


Sudoku::BlockLimits Sudoku::findBlock(int r, int c) const
{
    BlockLimits lim;
    
    if (r < 3)
    {
        lim.rowmin = 0;
        lim.rowmax = 3;
    }
    else if (r < 6)
    {
        lim.rowmin = 3;
        lim.rowmax = 6;
    }
    else
    {
        lim.rowmin = 6;
        lim.rowmax = 9;
    }
    
    if (c < 3)
    {
        lim.colmin = 0;
        lim.colmax = 3;
    }
    else if (c < 6)
    {
        lim.colmin = 3;
        lim.colmax = 6;
    }
    else
    {
        lim.colmin = 6;
        lim.colmax = 9;
    }

    return lim;
}



SudokuSet Sudoku::uniqueRowElement(int r, int c) const
{
    SudokuSet U(_plate[r][c]); // Copy of cell elements set
    
    U = U.difference(getOpenRowSet(r, c));
    
    if (U.cardinality() == 1)
        return U; // Return unique element
    else
        return SudokuSet(true); // Return empty set
}


SudokuSet Sudoku::uniqueColElement(int r, int c) const
{
    SudokuSet U(_plate[r][c]); // Copy of cell elements set
    
    U = U.difference(getOpenColSet(r, c));
    
    if (U.cardinality() == 1)
        return U; // Return unique element
    else
        return SudokuSet(true); // Return empty set
}



SudokuSet Sudoku::uniqueBlockElement(int r, int c) const
{
    SudokuSet U(_plate[r][c]); // Copy of cell elements set
    
    SudokuSet O(true);
    O = getOpenBlockSet(r, c);
    U = U.difference(O);
    
    if (U.cardinality() == 1)
        return U; // Return unique element
    else
        return SudokuSet(true); // Return empty set
}


SudokuSet Sudoku::uniqueInBlockRowElement(int r, int c) const
{
    SudokuSet U(true), R(true), B(true);

    // Get open block set excluding this row
    BlockLimits lim = findBlock(r,c);

    // Get the open set for the row including this cell (assuming it is open).
    for (int col = lim.colmin; col < lim.colmax; col++)
        if (!(_plate[r][col].isClosed()))
            R = R.setunion(_plate[r][col]);
    
    // Get the open block set excluding the row    
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        for (int col = lim.colmin; col < lim.colmax; col++)
            if ((row != r) && !(_plate[row][col].isClosed()))
                B = B.setunion(_plate[row][col]);
    
    // The set is unique if it is only present in the row and not in the block
    U = R.difference(B);
    return U;
}


SudokuSet Sudoku::uniqueInBlockColElement(int r, int c) const
{
    SudokuSet U(true), C(true), B(true);

    // Get open block set excluding this row
    BlockLimits lim = findBlock(r,c);

    // Get the open block set for this col including this cell (assuming it is open).
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        if (!(_plate[row][c].isClosed()))
            C = C.setunion(_plate[row][c]);
    
    // Get the open block set excluding the col
    for (int row = lim.rowmin; row < lim.rowmax; row++)
        for (int col = lim.colmin; col < lim.colmax; col++)
            if ((col != c) && !(_plate[row][col].isClosed()))
                B = B.setunion(_plate[row][col]);
    
    // The set is unique if it is only present in the row and not in the block
    U = C.difference(B);
    return U;
}


bool Sudoku::isSolution() const
{
    bool bAllClosed = isAllClosed();
    bool bSum = (closedElemSum() == 405);
    
    return (bSum && bAllClosed) && isConstraintsSatisfied();
}



bool Sudoku::operator==(Sudoku const &B) const
{
    bool bRetval = true;
    for (int r=0; r < 9; r++)
    {
        for (int c=0; c < 9; c++)
        {
            if (_plate[r][c] != B._plate[r][c])
            {
                bRetval = false;
                break;
            }
        }
    }
    
    return bRetval;
}


bool Sudoku::operator!=(Sudoku const &B) const
{
    return !((*this) == B);
}



bool Sudoku::isAllClosed() const
{
    bool bAllClosed = true;
    
    for (int r=0; r < 9; r++)
    {
        for (int c=0; c < 9; c++)
        {
            if (!(_plate[r][c].isClosed())) {
                bAllClosed = false;
                break;
            }
        }
    }
    
    return bAllClosed;
}


int Sudoku::closedElemSum() const
{
    int sum = 0;
    for (int r=0; r < 9; r++)
    {
        for (int c=0; c < 9; c++)
        {
            if (_plate[r][c].isClosed())
                sum += _plate[r][c].getSingletonElement();
        }
    }
    
    return sum;
}

bool Sudoku::isConstraintsSatisfied() const
{
    bool bSatisfied = true;
    for (int r=0; r < 9; r++)
    {
        for (int c=0; c < 9; c++)
        {
            SudokuSet U(true);
            
            U = uniqueBlockElement(r, c);
            if (U.isEmpty() || (_plate[r][c] != U))
            {
                bSatisfied = false;
            }
            
            U = uniqueRowElement(r, c);
            if (U.isEmpty() || (_plate[r][c] != U))
            {
                bSatisfied = false;
            }
            
            U = uniqueColElement(r, c);
            if (U.isEmpty() || (_plate[r][c] != U))
            {
                bSatisfied = false;
            }

        }
    }
    
    return bSatisfied;
}
