//
//  sequence1.cpp
//  
//
//  Created by James Grom on 1/30/20.
//

//invariants of the sequence class

//number of items stored in the sequence is =member variable used
//for an empty sequence, what's stored in data array is irrelevant
//for a non-empty sequence, items are stored from data[0] to data[used-1]
//we don't care what's stored in the rest of the data
//if there's a current item, then it lies in data[current_index]
//if there is no current item, then current index contains the same value as used




#include "sequence1.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

namespace coen79_lab3
{

const sequence::size_type sequence::CAPACITY;

//constructor for the sequence class
//initializes the sequence as an empty sequence
sequence::sequence()
{
    used=0;
    current_index=used;
    //data array is allocated automatically?
}

//copy constructor for the sequence class
sequence::sequence(const sequence& s)
{
    used=s.used;
    current_index=s.current_index;
    size_type i;
    //copy all the elements of the sequence
    for(i=0;i<used;i++)
    {
        data[i]=s.data[i];
    }
}

//sets current_index=0, the start of the sequence
void sequence::start()
{
    //no need to account for empty sequence
    //if empty, used =0 and current_index=used
    current_index=0;
    return;
}

//sets current_index=used-1, the last element in the sequence
void sequence::end()
{
    current_index=used-1;
    //account for the empty case
    if(current_index<0)
    {
        current_index=used;
    }
    return;
}

//sets current_index to the last position in the sequence array
void sequence::last()
{
    //regaurdless of the number of items in the sequence
    current_index= CAPACITY-1;
    return;
}

//increments the current_index by 1 unless aleady at the end of the sequence
void sequence::advance()
{
    assert(is_item()==true);
    current_index++;
    return;
    
}

//decrements the current_index unless it's already at 0
void sequence::retreat()
{
    //if current index is already at the front of the sequence don't decrement
    if((current_index-1)<0)
    {
        return;
    }
    current_index--;
    return;
}

//insert the value before the current value
//also set current_index = to the index of the new value
void sequence::insert(const value_type& entry)
{
    assert(used<CAPACITY);
    sequence::value_type temp=entry;
    //if current_index is pointing to nothing, then we can use insert_front
    if(is_item()==false)
    {
        insert_front(temp);
        return;
    }
    size_type j;
    
    //handle case of inserting to the first index
    //flag used to help us handle this case
    //this is necessary cause j is a size_type so it overflows to a + value not -1
    int flag=0;
    for(j=used-1;j>=current_index;j--)
    {
        data[j+1]=data[j];
        //if j is about to overflow cause it can't go -
        if(j==0)
        {
            flag=1;
            break;
        }
        
    }
    //account for decremented condition of leaving the for loop
    if(flag==0)
    {
        j++;
    }
    data[j]=temp;
    used++;
    //current_index points to the correct value
    return;
}


void sequence::attach(const value_type& entry)
{
    assert(size()<CAPACITY);
    value_type temp=entry;
    //handle empty or end case
    if((current_index==size()-1)||current_index==0)
    {
        //you're attaching to
        //an empty sequence
        //or
        //the last item in the sequence
        data[used]=temp;//inserts into last item in the sequence
        current_index=used;//current_index is now the new item
        used++;//account for the increase in items
        return;
    }
    //handle attatching to a middle item in the sequence
    size_type j;
    for(j=used-1;j>=current_index+1;j--)
    {
        data[j+1]=data[j];
    }
    j++;
    //j now points to desired location of temp
    data[j]=temp;
    used++;
    current_index=j;//change current index to point to new item
    return;
}

void sequence::remove_current()
{
    assert(is_item()==true);
    current_index++;
    //then this item is the last in the list
    if(is_item()==false)
    {
        used--;
        return;
    }
    current_index--;
    size_type j=current_index;
    //shift the sequence to fill gap of removed element
    for(;current_index<used-1;advance())
    {
        data[current_index]=data[current_index+1];
    }
    used--;
    current_index=j;
    return;
}

void sequence::insert_front(const value_type& entry)
{
    assert(size()<CAPACITY);
    current_index=0;
    data[current_index]=entry;
    used++;
    return;
}

//insert to the end of the sequence by using used as the index
//current_index should refer back to the new element added when finished
void sequence::attach_back(const value_type& entry)
{
    assert(size()<CAPACITY);
    value_type temp=entry;
    data[used]=temp;
    current_index=used;
    used++;
    return;
}

//remove front by setting current_index=0
void sequence::remove_front()
{
    assert(is_item()==true);
    current_index=0;
    remove_current();
    return;
}

//adds items to the sequence that called it
void sequence::operator +=(const sequence& rhs)
{
    size_type i;
    sequence temp(rhs);
    temp.start();
    //traverse the addend sequence adding items to the calling sequence
    for(i=0;i<temp.used;i++)
    {
        attach_back(temp.current());
        temp.advance();
    }
    return;
}

//return number of items in the seqeunce
sequence::size_type sequence::size() const
{
    return used;
    
}

//return true if current_index refers to a valid item
//return false if current_index refers to an invalid item
bool sequence::is_item() const
{
    if(current_index<used && current_index>=0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

// return value current_index is refering to
sequence::value_type sequence::current() const
{
    assert(is_item()==true);
    return data[current_index];
}

//using int index instead of a size_type??
sequence::value_type sequence::operator[](int index) const
{
    return data[index];
    
}

//compute the mean of the items in the sequence
sequence::value_type sequence::mean() const
{
    value_type sum=0;
    size_type i;
    //get the summation of elements in the sequence
    for(i=0;i<used;i++)
    {
        sum+=data[i];
    }
    return sum/used;
}


//this function calulates the variance and takes
//the square root to get the standard deviation
//returns the standard deviation of the items in the sequence
sequence::value_type sequence::standardDeviation() const
{
    value_type m=mean();
    value_type m2=m*m;
    //(^E[x]^2)
    value_type e=0;
    value_type sum=0;
    size_type y=0;
    for(y=0;y<used;y++)
    {
        sum+=(data[y]*data[y]);
    }
    e=sum/used;
    e=e-m2;
    e=sqrt(e);
    return e;
}

//returns an object with all of the items in both sequences in
//proper orientation (lhs then rhs)
sequence operator +(const sequence& lhs, const sequence& rhs)
{
    sequence sum=lhs;
    sum+=rhs;
    return sum;
}

//computes the sum of all the elements in the argument sequence
sequence::value_type summation(const sequence& s)
{
    sequence::value_type sum=0;
    sequence s2(s);
    sequence::size_type i;
    s2.start();
    //traverse the copy to add each element
    for(i=0;i<s2.size();i++)
    {
        sum+=s2.current();
        s2.advance();
    }
    return sum;
}

}


