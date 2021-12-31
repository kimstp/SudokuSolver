#include "SudokuSet.hpp"
#include <iostream>

SudokuSet::SudokuSet()
{
    // Initialize the set to be filled
    _card = 9;
    for (int elem=1; elem <= _card; elem++)
    {
        _setarray[elem] = 1;
    }
}


SudokuSet::SudokuSet(bool bEmpty)
{
    if (bEmpty)
    {
        _card = 0;
        for (int elem=1; elem <= 9; elem++)
        {
            _setarray[elem] = 0;
        } 
    } 
    else
    {
        // Initialize the set to be filled
        _card = 9;
        for (int elem=1; elem <= _card; elem++)
        {
            _setarray[elem] = 1;
        }

    }
}

SudokuSet::SudokuSet(SudokuSet const &B)
{
    _card = B._card;
    for (SetType elem=1; elem <= 9; elem++)
        _setarray[elem] = B._setarray[elem];
}

SudokuSet::~SudokuSet()
{
}


void SudokuSet::addElement(SetType elem)
{
    _setarray[elem] = 1;
    _card += 1;
}

void SudokuSet::removeElement(SetType elem)
{
    _setarray[elem] = 0;
    _card -= 1;
}


bool SudokuSet::hasElement(SetType elem) const
{
    if (_setarray[elem])
        return true;
    else
        return false;
}

bool SudokuSet::isClosed() const
{
    if (_card == 1)
        return true;
    else
        return false;
}

bool SudokuSet::isEmpty() const
{
    return (_card == 0);
}

SudokuSet::SizeType SudokuSet::cardinality() const
{
    return _card;
}

void SudokuSet::printSet() const
{
    std::cout << "{ ";
    
    for (int elem=1; elem <= 9; elem++)
    {
        if (_setarray[elem])
            std::cout << elem << " ";
            
    }
    std::cout <<  " }" << std::endl;
}
 
 
SudokuSet::SetType SudokuSet::getSingletonElement() const
{
    SudokuSet::SetType r = 0;
    if (isClosed())
    {
        for (int elem=1; elem <= 9; elem++)
        {
            if (_setarray[elem])
            {
                r = elem;
                break;
            }
        } 
    }
    return r;
}

SudokuSet SudokuSet::setunion(SudokuSet const &B) const
{
    SudokuSet R(true);
    for (SetType elem=1; elem <= 9; elem++)
    {
        if (hasElement(elem) || B.hasElement(elem))
            R.addElement(elem);
    }
    return R;
}

SudokuSet SudokuSet::intersection(SudokuSet const &B) const
{
    SudokuSet R(true);
    for (SetType elem=1; elem <= 9; elem++)
    {
        if (_setarray[elem] && B.hasElement(elem))
            R.addElement(elem);
    }
    return R;
}


SudokuSet SudokuSet::difference(SudokuSet const &B) const
{
    SudokuSet R(*this);
    for (SetType elem=1; elem <= 9; elem++)
    {
        if (_setarray[elem] && B.hasElement(elem))
            R.removeElement(elem);
    }    
    return R;
}

bool SudokuSet::operator==(SudokuSet const &B) const
{
    bool retval = true;
    for (SetType elem=1; elem <= 9; elem++)
    {
        if (_setarray[elem] != B._setarray[elem])
            retval = false;
    }
    return retval;
}

bool SudokuSet::operator!=(SudokuSet const &B) const
{
    return !((*this) == B);
}
