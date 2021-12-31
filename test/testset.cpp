#include <iostream>
#include "SudokuSet.hpp"

using namespace std;

int main() 
{
    
    int passedtests = 0; // 0 for true and 1 for failed (false) - unix style return error code
    SudokuSet A, B;
    SudokuSet C(true);
    SudokuSet D;
    SudokuSet E(false);
    
    cout << "#A = " <<  (int) A.cardinality() << endl;
    cout << "#B = " <<  (int) B.cardinality() << endl;
    cout << "#C = " <<  (int) C.cardinality() << endl;
    
    cout << "A = ";
    A.printSet();
    
    
    cout << "#D = " <<  (int) D.cardinality() << endl;
    D = A.difference(B);
    cout << "#D = " <<  (int) D.cardinality() << endl;
    
    C.addElement(1);
    C.addElement(3);

    cout << "C = ";
    C.printSet();

    D.addElement(2);
    D.addElement(3);
    cout << "D = ";
    D.printSet();

    
    
    A=C.setunion(D);
    cout << "#A = " <<  (int) A.cardinality() << endl;
    cout << "A = ";
    A.printSet();
    
    
    A=C.intersection(D);
    cout << "#A = " <<  (int) A.cardinality() << endl;
    cout << "A = ";
    A.printSet();

    
    A = C.difference(A);
    cout << "#A = " <<  (int) A.cardinality() << endl;
    cout << "A = ";
    A.printSet();

    
    return passedtests;
}

