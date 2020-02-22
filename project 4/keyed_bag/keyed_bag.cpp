//
//  keyed_bag.cpp
//  
//
//  Created by James Grom on 2/8/20.
//

#include "keyed_bag.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <string>

//invariants of the keyed_bag class
//implementation explained: 1 key_type key array, 1 value_type data array
//they are parallel arrays, used keeps track of the number of valid
//elements in the bag
//used is never to exceed CAPACITY
//the valid elements of the bag are stored from 0 to used-1;
//
using namespace std;

namespace coen79_lab4
{
//   static const size_type CAPACITY = _____
//     keyed_bag::CAPACITY is the maximum number of items that a keyed_bag can hold.
const keyed_bag::size_type keyed_bag::CAPACITY;

//constructor for the keyed_bag class:
//   keyed_bag( )
//     Postcondition: The keyed_bag has been initialized as an empty keyed_bag.
keyed_bag::keyed_bag()
{
    used=0;
}

// MODIFICATION MEMBER FUNCTIONS for the keyed_bag class:
//   void erase();
//     Postcondition: This keyed_bag is emptied of all items and keys.
//
void keyed_bag::erase()
{
    used=0;
    return;
}

//   bool erase(const key_type& key);
//     Postcondition: If key was in the keyed_bag, then the key and its value have been removed;
//     otherwise the keyed_bag is unchanged. A true return value indicates that an
//     item was removed; false indicates that nothing was removed.
bool keyed_bag::erase(const key_type& key)
{
    //search the key array for the key gives index
    int index;
    for(index=0;index<used;index++)
    {
        if(keys[index]==key)
        {
            break;
        }
    }
    //if index>=used key was not found
    //handles case of empty array
    if(index>=used)
    {
        return false;
    }
    //if key was found, replace that item's key and data with the last
    //element's in both arrays
    //decrement used
    //index points to the appropriate spot of removed item
    data[index]=data[used-1];
    keys[index]=keys[used-1];
    used--;
    return true;
    
}

//   void insert(const value_type& entry, const key_type& key)
//     Precondition:  size( ) < CAPACITY, and the keyed_bag does not yet contain
//     the given key.
//     Postcondition: A new copy of entry has been added to the keyed_bag with
//     the corresponding key.
//
void keyed_bag::insert(const value_type& entry, const key_type& key)
{
    value_type data_temp=entry;
    key_type key_temp=key;
    //make sure the bag isn't full and the key isn't already present
    assert(used<CAPACITY&& !has_key(key));
    data[used]=data_temp;
    keys[used]=key_temp;
    used++;
    return;
    
}


//   void operator +=(const keyed_bag& addend)
//     Precondition:  size( ) + addend.size( ) <= CAPACITY.
//     The intersection of the keyed_bags' key tables is empty (i.e. the keyed_bags)
//     share no keys.
//     Postcondition: Each item and its key in addend has been added to this keyed_bag.
void keyed_bag::operator +=(const keyed_bag& addend)
{
    assert(size( ) + addend.size( ) <= CAPACITY&&!hasDuplicateKey(addend));
    size_type addend_size=addend.size();
    size_type i;
    for(i=0;i<addend_size;i++)
    {
        //data[used]=addend.data[i];
        //keys[used]=addend.keys[i];
        //used++;
        insert(addend.data[i],addend.keys[i]);
    }
    return;
}


// CONSTANT MEMBER FUNCTIONS for the keyed_bag class:


//   bool has_key(const key_type& key) const
//     Postcondition: The return value is whether or not the given key is in
//     the keyed_bag's list of keys.
bool keyed_bag::has_key(const key_type& key) const
{
    size_type i;
    for(i=0;i<used;i++)
    {
        if(key==keys[i])
        {
            return true;
        }
    }
    return false;
    
}


//value_type get(const key_type& key) const;
//     Precondition: has_key returns true for the given key.
//     Postcondtion: the data value corresponding to the given key is returned.
keyed_bag::value_type keyed_bag::get(const key_type& key) const
{
    assert(has_key(key));
    size_type i;
    for(i=0;i<used;i++)
    {
        if(keys[i]==key)
        {
            break;
        }
    }
    //i points to appropriate index
    return data[i];
}

//   size_type size( ) const
//     Postcondition: The return value is the total number of items in the keyed_bag.
keyed_bag::size_type keyed_bag::size( ) const
{
    return used;
}


//   size_type count(const value_type& target) const
//     Postcondition: The return value is number of times target is in the keyed_bag.
keyed_bag::size_type keyed_bag::count(const value_type& target) const
{
    size_type counter=0;
    size_type i;
    for(i=0;i<used;i++)
    {
        if(data[i]==target)
        {
            counter++;
        }
    }
    return counter;
}

//   bool hasDuplicateKey(const keyed_bag& otherBag) const
//     Postcondition: The return value is true if there is at least one key used by both this bag and the "otherBag". In other words, this function checks if there is any shared key by the two bags.
bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const
{
    size_type i;
    for(i=0;i<used;i++)
    {
        if(otherBag.has_key(keys[i]))
        {
            return true;
        }
    }
    return false;
}

void keyed_bag::print()
{
    for(size_type i=0;i<used;i++)
    {
        cout<<"key: "<<keys[i]<<" "<<"value: "<<data[i]<<endl;
    }
}

// NONMEMBER FUNCTIONS for the keyed_bag class:
//   keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
//     Precondition:  b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY.
//                    The intersection of the keyed_bags' key tables is empty.
//                    (i.e. The two keyed_bag's have no keys in common.)
//     Postcondition: The keyed_bag returned is the union of b1 and b2.

keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2)
{
    assert(b1.size( ) + b2.size( ) <= keyed_bag::CAPACITY&&!b1.hasDuplicateKey(b2));
    keyed_bag ans;
    ans +=b1;
    ans +=b2;
    return ans;
}









}
