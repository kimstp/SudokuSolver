#ifndef _SUDOKUSET_H_
#define _SUDOKUSET_H_


class SudokuSet
{
public:
    /* Auxillary types */
    typedef unsigned char SetType;
    typedef unsigned char SizeType;

public:
    /* Constructors and destructors */
    
    /* Initialize the set to be complete with elements 1 to 9. */
	SudokuSet();
    
    /* Initialize the set to be either empty (TRUE) or complete with elements 1 to 9 (FALSE). */
    SudokuSet(bool empty);
    SudokuSet(SudokuSet const &B); // Copy constructor
	virtual ~SudokuSet();
    
    
    /* Public methods */
    void addElement(SetType elem);
    void removeElement(SetType elem);
    bool hasElement(SetType elem) const;
    
    /* A set is said to be closed if cardinality is 1 */
    bool isClosed() const;
    
    /* Return true if set is empty */
    bool isEmpty() const;
    
    /* Return cardinality of the set */
    SizeType cardinality() const;
    
    /* Print the set to std::cout */
    void printSet() const;
    
    /* If set is closed (cardinality is 1) return the element.
       Otherwise return 0.
     */
    SetType getSingletonElement() const;
    
    
    /* Set operations */
    SudokuSet setunion(SudokuSet const &B) const;
    SudokuSet intersection(SudokuSet const &B) const;
    SudokuSet difference(SudokuSet const &B) const;
    
    /* Comparison operators */
    bool operator==(SudokuSet const &B) const;
    bool operator!=(SudokuSet const &B) const;
    
    
private:

    /* Private data */
    SetType _setarray[10]; // Set representation
    
    SizeType _card; // Cardinality (size of set)
    
};

#endif //_SUDOKUSET_H_
