//FILE: sequence.cpp
//CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
//
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
//INVARIANT for the sequence class
//  1. The number of items in the sequence is stored in the member variable "many_nodes"
//
//  2. For an empty sequence, we do not care what is stored in any of data and head_ptr
//      and tail_ptr point to NULL; for a non-empty sequence, the items stored in the
//      sequence can be accessed using head_ptr and tail_ptr and we don't care what is
//      stored in the rest of the data.
//
//  3. If there is a current item, then it lies in *cursor; if there is no
//     current item, then cursor* equals NULL.
//
//  4. If there is a previous item, then it lies in precursor*.  If there is no previous
//       item, then precursor equals NULL.


#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }
//here and below implementation was done by james grom
//destructor
sequence::~sequence()
{
    list_clear(head_ptr);
}

//     Postcondition: The precursor and cursor are adjusted such that the first
//     item in the sequence becomes the current item (but if the sequence is
//     empty, then there is no current item).
void sequence::start()
{
    //point the cursor to the first node
    cursor=head_ptr;
    precursor=NULL;
    return;
}

//   void end( )
//     Postcondition: The precursor and cursor are adjusted such that the last
//     item in the sequence becomes the current item (but if the sequence is
//     empty, then there is no current item).
void sequence::end()
{
    if(many_nodes==0)
    {
        cursor=NULL;
        precursor=NULL;
        return;
    }
    if(many_nodes==1)
    {
        cursor=head_ptr;
        precursor=NULL;
        return;
    }
    precursor=head_ptr;
    cursor=tail_ptr;
    while(precursor->link()!=tail_ptr)
    {
        precursor=precursor->link();
    }
    return;
}
 
//Precondition: is_item returns true.
//Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item
void sequence::advance()
{
    if(is_item())
    {
        //case where cursor is the last item
        if(cursor->link()==NULL)
        {
            precursor=cursor;
            cursor=NULL;
            return;
        }
        precursor=cursor;
        cursor=cursor->link();
        return;
    }
}

//Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
void sequence::insert(const value_type& entry)
{
    // adress case of empty list
    if(cursor==NULL||precursor==NULL)
    {
        list_head_insert(head_ptr,entry);
        precursor=NULL;
        cursor=head_ptr;
    }
    //insert normally
    else
    {
        list_insert(precursor,entry);
        cursor=precursor->link();
    }
    //account for the added node and make sure tail pointer is valid
    many_nodes++;
    tail_ptr=head_ptr;
    while(tail_ptr->link()!=NULL)
    {
        tail_ptr=tail_ptr->link();
    }
    return;
}

//Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
void sequence::attach(const value_type& entry)
{
    //if cursor doesn't point to anything
    if(cursor==NULL)
    {
        //if list is empty
        if(many_nodes==0)
        {
            list_head_insert(head_ptr, entry);
            tail_ptr=head_ptr;
            precursor=NULL;
            cursor=head_ptr;
        }
        //if list is not empty
        else
        {
            list_insert(tail_ptr,entry);
            precursor=tail_ptr;
            tail_ptr=tail_ptr->link();
            cursor=tail_ptr;
        }
    }
    //if valid cursor
    else
    {
        list_insert(cursor,entry);
        precursor=cursor;
        cursor=cursor->link();
    }
    many_nodes++;
    tail_ptr=head_ptr;
    while(tail_ptr!=NULL&&tail_ptr->link()!=NULL)
        tail_ptr=tail_ptr->link();
    return;
}

//assignment op
void sequence::operator =(const sequence& source)
{
    //copy the data
    list_copy(source.head_ptr,head_ptr,tail_ptr);
    //update necessary pointers
    if(source.cursor==NULL)
        cursor=NULL;
    if(source.precursor==NULL)
        precursor=NULL;
    if(source.head_ptr==NULL)
        head_ptr=NULL;
    
    //find the cursor and precursor and copy them to the assigned list
    node *s=source.head_ptr;
    node *p=head_ptr;
    
    while(s!=NULL)
    {
        if(s==source.precursor)
            precursor=p;
        if(s==source.cursor)
            cursor=p;
        if(s->link()!=NULL)
            tail_ptr=s;
       // cout<< "loc"<<endl;
        s=s->link();
        //cout<<"alpha";
        p=p->link();
    }
    many_nodes=source.many_nodes;
    return;
}


//Precondition: is_item returns true.
//Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
void sequence::remove_current()
{
    assert(is_item());
    //case to remove first element
    if(cursor==head_ptr)
    {
        head_ptr=cursor->link();
        delete cursor;
        cursor=head_ptr;
        precursor=NULL;
    }
    else
    {
        list_remove(precursor);
        cursor=precursor->link();
    }
    //account for removed node and account for tail
    many_nodes--;
    tail_ptr=head_ptr;
    while(tail_ptr!=NULL&&tail_ptr->link()!=NULL)
        tail_ptr=tail_ptr->link();
    return;
}

sequence::size_type sequence::size() const
{
    return many_nodes;
}

bool sequence::is_item() const
{
    if(cursor==NULL)
        return false;
    return true;
}
sequence::value_type sequence::current() const
{
    assert(is_item());
    return cursor->data();
    
}


}
