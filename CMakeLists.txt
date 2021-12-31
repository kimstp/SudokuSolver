CMAKE_MINIMUM_REQUIRED (VERSION 3.19)
PROJECT (Sudoku CXX)


INCLUDE_DIRECTORIES(
  ${Sudoku_SOURCE_DIR}/src
)

SET(SUDOKU_MAIN_SRC
  ${Sudoku_SOURCE_DIR}/src/main.cpp
)

SET(SUDOKU_SRS
  ${Sudoku_SOURCE_DIR}/src/Sudoku.cpp
  ${Sudoku_SOURCE_DIR}/src/SudokuSet.cpp
)


SET(SUDOKU_HEADERS
  ${Sudoku_SOURCE_DIR}/src/Sudoku.hpp
  ${Sudoku_SOURCE_DIR}/src/SudokuSet.hpp
)

ADD_EXECUTABLE(sudoku 
  ${SUDOKU_MAIN_SRC}
  ${SUDOKU_SRS}
  ${SUDOKU_HEADERS}
)


ADD_EXECUTABLE(testset
  ${Sudoku_SOURCE_DIR}/test/testset.cpp
  ${SUDOKU_SRS}
  ${SUDOKU_HEADERS}
)


ADD_EXECUTABLE(testsudoku
  ${Sudoku_SOURCE_DIR}/test/testsudoku.cpp
  ${SUDOKU_SRS}
  ${SUDOKU_HEADERS}
)
