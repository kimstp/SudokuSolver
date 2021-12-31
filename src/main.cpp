#include <iostream>
#include "Sudoku.hpp"

/*
SudokuSet::SetType testplate[9*9] = {7,0,3, 0,1,0, 0,8,0,
                                     0,0,0, 0,4,0, 0,0,0,
                                     9,6,2, 0,0,8, 0,0,0,
                                     
                                     0,7,9, 0,0,0, 0,0,1,
                                     0,0,5, 3,0,1, 2,0,0,
                                     3,0,0, 0,0,0, 6,9,0,
                                     
                                     0,0,0, 2,0,0, 4,3,5,
                                     0,0,0, 0,6,0, 0,0,0,
                                     0,3,0, 0,5,0, 8,0,9};

SudokuSet::SetType testplate_solution[9*9] = {7,0,3, 0,1,0, 0,8,0,
    0,0,0, 0,4,0, 0,0,0,
    9,6,2, 0,0,8, 0,0,0,
    
    0,7,9, 0,0,0, 0,0,1,
    0,0,5, 3,0,1, 2,0,0,
    3,0,0, 0,0,0, 6,9,0,
    
    0,0,0, 2,0,0, 4,3,5,
    0,0,0, 0,6,0, 0,0,0,
    0,3,0, 0,5,0, 8,0,9};
*/


// Easy
/*
SudokuSet::SetType testplate[9*9] = {0,0,0, 0,1,6, 0,0,2,
                                     0,0,0, 9,5,0, 0,6,7,
                                     0,0,0, 0,0,0, 0,0,8,
 
                                     0,7,0, 0,3,0, 0,8,0,
                                     5,4,0, 1,0,0, 9,0,3,
                                     3,0,0, 0,0,0, 0,1,5,
    
                                     0,0,0, 0,2,0, 0,4,0,
                                     0,1,0, 5,0,3, 8,0,0,
                                     8,2,9, 0,6,4, 0,0,0};

SudokuSet::SetType testplate_solution[9*9] = {7,9,8, 3,1,6, 4,5,2,
                                              2,3,4, 9,5,8, 1,6,7,
                                              1,6,5, 2,4,7, 3,9,8,
    
                                              9,7,1, 6,3,5, 2,8,4,
                                              5,4,6, 1,8,2, 9,7,3,
                                              3,8,2, 4,7,9, 6,1,5,
    
                                              6,5,3, 8,2,1, 7,4,9,
                                              4,1,7, 5,9,3, 8,2,6,
                                              8,2,9, 7,6,4, 5,3,1};
*/


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

SudokuSet::SetType testplate_solution[9*9] = {4,1,5, 8,9,7, 6,2,3,
                                              9,3,2, 4,1,6, 8,7,5,
                                              8,6,7, 2,5,3, 1,4,9,
    
                                              6,5,1, 7,2,8, 3,9,4,
                                              2,4,8, 3,6,9, 7,5,1,
                                              3,7,9, 5,4,1, 2,8,6,
    
                                              5,9,3, 1,7,2, 4,6,8,
                                              1,2,4, 6,8,5, 9,3,7,
                                              7,8,6, 9,3,4, 5,1,2};
*/

// Hard
/*
SudokuSet::SetType testplate[9*9] = {0,0,0, 0,0,0, 0,0,0,
                                     8,9,6, 0,5,0, 0,0,0,
                                     0,0,1, 8,0,0, 0,5,3,
 
                                     0,3,0, 0,0,8, 2,0,7,
                                     1,0,0, 9,0,0, 5,0,0,
                                     0,2,0, 0,0,4, 9,0,6,
    
                                     0,0,2, 7,0,0, 0,6,9,
                                     6,7,4, 0,2,0, 0,0,0,
                                     0,0,0, 0,0,0, 0,0,0};

 SudokuSet::SetType testplate_solution[9*9] = {7,5,3, 2,1,6, 8,9,4,
                                               8,9,6, 4,5,3, 7,2,1,
                                               2,4,1, 8,9,7, 6,5,3,
 
                                               4,3,9, 5,6,8, 2,1,7,
                                               1,6,7, 9,3,2, 5,4,8,
                                               5,2,8, 1,7,4, 9,3,6,
 
                                               3,1,2, 7,8,5, 4,6,9,
                                               6,7,4, 3,2,9, 1,8,5,
                                               9,8,5, 6,4,1, 3,7,2};
*/
/*
// Hard 2 - problem case for the solver
SudokuSet::SetType testplate[9*9] = {0,4,0, 8,0,0, 0,0,0,
                                    0,0,0, 0,0,0, 0,0,0,
                                    2,0,1, 0,0,5, 0,7,0,

                                    6,0,0, 0,3,0, 0,0,4,
                                    3,0,2, 0,5,6, 0,0,1,
                                    0,0,0, 0,7,8, 0,0,0,
   
                                    1,0,8, 0,0,3, 5,0,9,
                                    4,0,6, 0,0,0, 0,0,8,
                                    0,0,3, 0,0,0, 0,0,0};

// Human solution contains an error!
SudokuSet::SetType testplate_solution[9*9] = {7,4,9, 8,6,2, 3,1,5,
                                              8,6,5, 3,1,7, 4,9,2,
                                              2,3,1, 9,4,5, 8,7,6,

                                              6,8,7, 1,3,9, 2,5,4,
                                              3,9,2, 4,5,6, 7,8,1,
                                              5,1,4, 2,7,8, 9,6,3,

                                              1,7,8, 6,2,3, 5,4,9,
                                              4,5,6, 7,9,1, 3,2,8,
                                              9,2,3, 5,8,4, 1,6,7};


*/
// Hard 3 - solvable by solver
SudokuSet::SetType testplate[9*9] ={0,0,6, 0,0,0, 5,3,0,
                                    0,8,9, 2,5,0, 0,0,7,
                                    0,0,0, 0,0,7, 0,0,0,

                                    0,2,7, 0,0,0, 0,0,0,
                                    6,3,0, 0,0,0, 0,7,5,
                                    0,0,0, 0,0,0, 4,8,0,
   
                                    0,0,0, 1,0,0, 0,0,0,
                                    4,0,0, 0,2,3, 6,9,0,
                                    0,6,3, 0,0,0, 8,0,0};

// Human partial solution
SudokuSet::SetType testplate_solution[9*9] = {7,0,6, 0,0,0, 5,3,2,
                                              3,8,9, 2,5,6, 1,4,7,
                                              0,0,0, 0,0,7, 9,6,8,

                                              8,2,7, 0,0,0, 3,1,9,
                                              6,3,4, 0,0,0, 2,7,5,
                                              0,0,0, 0,0,0, 4,8,6,

                                              0,0,0, 1,6,4, 7,0,3,
                                              4,7,5, 8,2,3, 6,9,1,
                                              1,6,3, 0,0,0, 8,0,4};



int main()
{
    Sudoku game(testplate);
    Sudoku human_solution(testplate_solution);
    
    std::cout << std::endl;
    std::cout << "Input plate: " << std::endl;
    game.printPlate();
    
    bool retval = game.solve();
    
    std::cout << std::endl;
    if (retval)
        std::cout << "Solution found " << std::endl;
    else
        std::cout << "Solution not found " << std::endl;
    
    std::cout << std::endl;
    std::cout << "Solution: " << std::endl;
    game.printPlate();
    
    std::cout << std::endl;
    std::cout << "Solution fits human solution: " << std::endl;
    if (game == human_solution)
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
    
    std::cout << std::endl;
    std::cout << "Human solution is correct: " << std::endl;
    if (human_solution.isSolution())
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;

    return 0;
}