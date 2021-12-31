#include <iostream>
#include "Sudoku.hpp"

using namespace std;

// Easy

SudokuSet::SetType testplate[9*9] = {0,0,0, 0,1,6, 0,0,2,
                                     0,0,0, 9,5,0, 0,6,7,
                                     0,0,0, 0,0,0, 0,0,8,
    
                                     0,7,0, 0,3,0, 0,8,0,
                                     5,4,0, 1,0,0, 9,0,3,
                                     3,0,0, 0,0,0, 0,1,5,
    
                                     0,0,0, 0,2,0, 0,4,0,
                                     0,1,0, 5,0,3, 8,0,0,
                                     8,2,9, 0,6,4, 0,0,0};


// Medium
/*
SudokuSet::SetType testplate[9*9] = {0,0,5, 0,0,0, 0,0,3,
    0,3,0, 0,1,0, 8,7,0,
    0,6,0, 2,0,0, 0,4,0,
    
    0,0,0, 7,2,0, 0,9,0,
    0,0,8, 0,0,0, 0,0,1,
    0,0,0, 5,4,0, 0,8,0,
    
    0,9,0, 1,0,0, 0,6,0,
    0,2,0, 0,8,0, 9,3,0,
    0,0,6, 0,0,0, 0,0,2};
*/



// Hard
SudokuSet::SetType hardtestplate[9*9] = {0,0,0, 0,0,0, 0,0,0,
    8,9,6, 0,5,0, 0,0,0,
    0,0,1, 8,0,0, 0,5,3,
    
    0,3,0, 0,0,8, 2,0,7,
    1,0,0, 9,0,0, 5,0,0,
    0,2,0, 0,0,4, 9,0,6,
    
    0,0,2, 7,0,0, 0,6,9,
    6,7,4, 0,2,0, 0,0,0,
    0,0,0, 0,0,0, 0,0,0};

SudokuSet::SetType hardtestplate_solution[9*9] = {7,5,3, 2,1,6, 8,9,4,
    8,9,6, 4,5,3, 7,2,1,
    2,4,1, 8,9,7, 6,5,3,
    
    4,3,9, 5,6,8, 2,1,7,
    1,6,7, 9,3,2, 5,4,8,
    5,2,8, 1,7,4, 9,3,6,
    
    3,1,2, 7,8,5, 4,6,9,
    6,7,4, 3,2,9, 1,8,5,
    9,8,5, 6,4,1, 3,7,2};




int main()
{
    
    int passedtests = 0; // 0 for true and 1 for failed (false) - unix style return error code

    
    Sudoku game(testplate);
    
    std::cout << std::endl;
    std::cout << "Testing findBlock " << std::endl;
    
    Sudoku::BlockLimits lim = game.findBlock(0, 3);
    std::cout << std::endl;
    std::cout << "rowmin = " << (int) lim.rowmin << " rowmax = " << (int) lim.rowmax;
    std::cout << " colmin = " << (int) lim.colmin << " colmax = " << (int) lim.colmax;
    std::cout << std::endl;

    lim = game.findBlock(8, 8);
    std::cout << std::endl;
    std::cout << "rowmin = " << (int) lim.rowmin << " rowmax = " << (int) lim.rowmax;
    std::cout << " colmin = " << (int) lim.colmin << " colmax = " << (int) lim.colmax;
    std::cout << std::endl;

    lim = game.findBlock(4, 8);
    std::cout << std::endl;
    std::cout << "rowmin = " << (int) lim.rowmin << " rowmax = " << (int) lim.rowmax;
    std::cout << " colmin = " << (int) lim.colmin << " colmax = " << (int) lim.colmax;
    std::cout << std::endl;
    
    std::cout << std::endl;
    std::cout << "Testing getClosedSet " << std::endl;
    game.getClosedSet(0, 3).printSet();
    
    

    std::cout << std::endl;
    std::cout << "Testing pruneSolution " << std::endl;
    
    game.printSolutionSetAt(0, 3);
    std::cout << std::endl;
    game.printSolutionSetAt(1, 5);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 3);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 4);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 5);

    game.pruneSolution();

    std::cout << std::endl;
    game.printPlate();
    
    std::cout << std::endl;
    std::cout << " Block 2 " << std::endl;
    
    std::cout << std::endl;
    game.printSolutionSetAt(0, 3);
    std::cout << std::endl;
    game.printSolutionSetAt(1, 5);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 3);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 4);
    std::cout << std::endl;
    game.printSolutionSetAt(2, 5);
    
    std::cout << std::endl;
    std::cout << " Block 9 " << std::endl;
    std::cout << std::endl;
    game.printSolutionSetAt(7, 7);
    
    
    std::cout << std::endl;
    std::cout << "Testing getOpenBlockSet " << std::endl;
    game.getOpenBlockSet(0, 3).printSet();


    Sudoku hardgame(hardtestplate);
    hardgame.solve();
    
    std::cout << std::endl;
    std::cout << "Testing uniqueInBlockRowElement " << std::endl;
    hardgame.printPlate();
    hardgame.printSolutionSetAt(0, 4);
    hardgame.printSolutionSetAt(4, 4);
    hardgame.printSolutionSetAt(5, 4);
    hardgame.printSolutionSetAt(5, 3);
    hardgame.uniqueInBlockRowElement(4, 4).printSet();

    std::cout << std::endl;
    std::cout << "Testing uniqueInBlockColElement " << std::endl;
    hardgame.printPlate();
    hardgame.printSolutionSetAt(0, 4);
    hardgame.printSolutionSetAt(4, 4);
    hardgame.printSolutionSetAt(5, 4);
    hardgame.printSolutionSetAt(5, 3);
    
    SudokuSet U(true);
    U = hardgame.uniqueInBlockColElement(4, 4);
    U.printSet();
    hardgame.removeFromOpenNonBlockColSet(4, 4, U);
    hardgame.printSolutionSetAt(0, 4);
    hardgame.printSolutionSetAt(3, 4);
    hardgame.printSolutionSetAt(4, 4);
    hardgame.printSolutionSetAt(5, 4);
    hardgame.printSolutionSetAt(6, 4);
    hardgame.printSolutionSetAt(8, 4);

    
    return passedtests;
}

