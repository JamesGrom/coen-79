//
//FILE: node.cpp
// James Grom lab 6
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//
//
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
//
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
    //Precondition: head_ptr is the head pointer of a linked list.
    //Postcondition: The value returned is the number of nodes in the linked list.
    size_t list_length(const node* head_ptr)
    // Library facilities used: cstdlib
    {
    //create a temp node  to traverse list
	const node *cursor;
        //holds list size
	size_t answer;
        //initialize list size
	answer = 0;
        //count number of nodes
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
	    ++answer;
        //return number of nodes
	return answer;
    }
    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: A new node containing the given entry has been added at
    //     the head of the linked list; head_ptr now points to the head of the new,
    //     longer linked list.
    void list_head_insert(node*& head_ptr, const node::value_type& entry)
    {
    	head_ptr = new node(entry, head_ptr);
    }
    
//   void list_insert(node* previous_ptr, const node::value_type& entry)
//     Precondition: previous_ptr points to a node in a linked list.
//     Postcondition: A new node containing the given entry has been added
//     after the node that previous_ptr points to.
    void list_insert(node* previous_ptr, const node::value_type& entry)
    {
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link( ));
    	previous_ptr->set_link(insert_ptr);
    }

   
    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: The pointer returned points to the first node containing
    //     the specified target in its data member. If there is no such node, the
    //     null pointer is returned.
    node* list_search(node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }


        //     Precondition: head_ptr is the head pointer of a linked list.
        //     Postcondition: The pointer returned points to the first node containing
        //     the specified target in its data member. If there is no such node, the
        //     null pointer is returned.
    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
    {
    	const node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }
    
    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     position > 0.
    //     Postcondition: The pointer returned points to the node at the specified
    //     position in the list. (The head node is position 1, the next node is
    //     position 2, and so on). If there is no such position, then the null
    //     pointer is returned.
    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    //     Precondition: head_ptr is the head pointer of a linked list, and
    //     position > 0.
    //     Postcondition: The pointer returned points to the node at the specified
    //     position in the list. (The head node is position 1, the next node is
    //     position 2, and so on). If there is no such position, then the null
    //     pointer is returned.
    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
    {
    	const node *cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link( );

    	return cursor;
    }

    //   void list_head_remove(node*& head_ptr)
    //     Precondition: head_ptr is the head pointer of a linked list, with at
    //     least one node.
    //     Postcondition: The head node has been removed and returned to the heap;
    //     head_ptr is now the head pointer of the new, shorter linked list.
    void list_head_remove(node*& head_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link( );
    	delete remove_ptr;
    }
    
    //     Precondition: previous_ptr points to a node in a linked list, and this
    //     is not the tail node of the list.
    //     Postcondition: The node after previous_ptr has been removed from the
    //     linked list.
    void list_remove(node* previous_ptr)
    {
    	node *remove_ptr;

    	remove_ptr = previous_ptr->link( );
    	previous_ptr->set_link( remove_ptr->link( ) );
    	delete remove_ptr;
    }
    
    //     Precondition: head_ptr is the head pointer of a linked list.
    //     Postcondition: All nodes of the list have been returned to the heap,
    //     and the head_ptr is now NULL.
    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
    {
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    //   void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    //     Precondition: source_ptr is the head pointer of a linked list.
    //     Postcondition: head_ptr and tail_ptr are the head and tail pointers for
    //     a new list that contains the same items as the list pointed to by
    //     source_ptr. The original list is unaltered.

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
    {
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// create head node pointer for new list
    	list_head_insert(head_ptr, source_ptr->data( ));
    	tail_ptr = head_ptr;

    	// Copy nodes at tail pointer
    	source_ptr = source_ptr->link( );
    	while (source_ptr != NULL)
    	{
    	    list_insert(tail_ptr, source_ptr->data( ));
    	    tail_ptr = tail_ptr->link( );
    	    source_ptr = source_ptr->link( );
    	}
    }

//the following have been implemented by James Grom

//    Precondition: start_ptr and end_ptr are pointers to nodes on the same
//    linked list, with the start_ptr node at or before the end_ptr node
//    Postcondition: head_ptr and tail_ptr are the head and tail pointers for a
//    new list that contains the items from start_ptr up to but not including
//    end_ptr.  The end_ptr may also be NULL, in which case the new list
//    contains elements from start_ptr to the end of the list.
void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
{
    //check if creating an empty list
    if(start_ptr==NULL||start_ptr==end_ptr)
    {
        head_ptr=NULL;
        tail_ptr=NULL;
        return;
    }
    //case where start==end has been handled
    //create a new_list andy copy the data from start pointer into the first node
    node *new_list=new node(start_ptr->data());
    //have the old_list reference pont to the starting point
    node *old_list=start_ptr;
    //set head_ptr = to the new_list
    head_ptr=new_list;
    //traverse the old list from start_p to end_p stop traversal if old_list is or points to Null
    while(old_list!=NULL&&old_list!=end_ptr&&old_list->link()!= end_ptr)
    {
        //move old_list pointer to the next node
        old_list=old_list->link();
        //to prevent double insertion insert after oldlist has been incremented
        list_insert(new_list,old_list->data());
        //move new_list pointer
        new_list=new_list->link();
    }
    //newlist is now pointing to the last node in the newly created list
    tail_ptr=new_list;
    return;
}


//     Precondition: head_ptr is the head pointer of a linked list.
//     Postcondition: The return value is the count of the number of times
//     target appears as the data portion of a node on the linked list.
//     The linked list itself is unchanged.
size_t list_occurrences(node* head_ptr, const node::value_type& target)
{
    size_t count=0;
    const node *p=head_ptr;
    while(p!=NULL)
    {
        //count if u've found an occurence
        if(p->data()==target)
        {
            count++;
        }
        p=p->link();
    }
    return count;
}



//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0 and position <= list_length(head_ptr)+1.
//     Postcondition: A new node has been added to the linked list with entry
//     as the data. The new node occurs at the specified position in the list.
//     (The head node is position 1, the next node is position 2, and so on.)
//     Any nodes that used to be after this specified position have been
//     shifted to make room for the one new node.
void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position)
{
    assert(position>0);
    assert(position <= list_length(head_ptr)+1);
    //position can refer to NULL (eg list_length(head_ptr)+1
    
    //if position is at the head call head insert function
    if(position==1)
    {
        list_head_insert(head_ptr,entry);
        return;
    }
    //point previous to the node before to be inserted
    node *previous=head_ptr;
    int i=1;
    //move previous to i-1, stop traversing the list if at the end
    while(previous!=NULL)
    {
        if(i==position-1)
        {
            list_insert(previous,entry);
            return;
        }
        else{
            previous=previous->link();
            i++;
        }
    }
    //previous should now point to node at position -1
    //now insert into list at appropriate location
    list_insert(previous,entry);
    return;
}


//     Precondition: head_ptr is the head pointer of a linked list, and
//     position > 0 and position <= list_length(head_ptr).
//     Postcondition: The node at the specified position has been removed from
//     the linked list and the function has returned a copy of the data from
//     the removed node.
//     (The head node is position 1, the next node is position 2, and so on.)
node::value_type list_remove_at(node*& head_ptr, size_t position)
{
    //ensure valid preconditions
    assert(position>0);
    assert(position<=list_length(head_ptr));
    //create a variable for return value
    node::value_type ret_val=head_ptr->data();
    //if position refers to first node in the list, call remove head
    if(position==1)
    {
        list_head_remove(head_ptr);
        return ret_val;
    }
    //point previous to the node before to be inserted
    node *previous=head_ptr;
    //previous is at position 1 rn
    int i=1;
    //move previous position-1 times
    while(previous!=NULL)
    {
        if(i==(position-1))
        {
            ret_val=previous->link()->data();
            list_remove(previous);
            return ret_val;
        }
        previous=previous->link();
        i++;
        
    }
}

//   node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
//     Precondition: head_ptr is the head pointer of a linked list, and
//     (1 <= start) and (start <= finish) and (finish <= list_length(head_ptr)).
//     Postcondition: The value returned is the head pointer for
//     a new list that contains copies of the items from the start position to
//     the finish position in the list that head_ptr points to.
//     (The head node is position 1, the next node is position 2, and so on.)
//     The list pointed to by head_ptr is unchanged.
node* list_copy_segment(node* head_ptr, size_t start, size_t finish)
{
    //assure valid preconditions
    assert((1<=start)&&(start <= finish)&&(finish <= list_length(head_ptr)));
    //translate into valid paramaters for list_piece
    node *start_ptr=list_locate(head_ptr,start);
    node *end_ptr=list_locate(head_ptr,finish)->link();
    node *useless;
    
    //copy out the referenced piece of the list
    list_piece(start_ptr,end_ptr,head_ptr,useless);
    return head_ptr;
}

//     Precondition: head_ptr is the head pointer of a linked list, and
//     the operator << has been defined for the value_type
//     Postcondition: The value_type of all the nodes in the linked list are printed
void list_print (const node* head_ptr)
{
    while(head_ptr!=NULL)
    {
        cout<<head_ptr->data();
        head_ptr=head_ptr->link();
        if(head_ptr!=NULL)
            cout<<", ";
    }
    cout<<endl;
    return;
}


//     Precondition: head_ptr is the head pointer of a linked list
//     Postcondition: All the duplicates are removed from the linked list
//     Example: If the list contains 1,1,1,2, after running this function the list
//     contains 1,2
void list_remove_dups(node* head_ptr)
{
    node::value_type temp;
    node *p;
    //ensure valid head_ptr to prevent segfault
    if(head_ptr==NULL)
    {
        return;
    }
    temp=head_ptr->data();
    while(head_ptr!=NULL&&head_ptr->link()!=NULL)
    {
        while(list_search(head_ptr->link(),temp)!=NULL)
        {
            //a duplicate has been found
            //find the preceeding node to the one we want to delete
            p=head_ptr;
            
            while(p->link()!=list_search(head_ptr->link(),temp))
            {
                p=p->link();
            }
            //head pointer will never get deleted since only duplicates after the first are deleted
            //remove the node with duplicate value
            list_remove(p);
        }
        head_ptr=head_ptr->link();
    }
    return;
}



//   node* list_detect_loop (node* head_ptr);
//     Precondition: head_ptr is the head pointer of a linked list
//     Postcondition: If there is a loop in the linked list, the returned value
//     is a pointer to the start of the loop. The returned value is NULL if
//     there is no loop in the list
node* list_detect_loop (node* head_ptr)
{
    if(head_ptr==NULL)
        return NULL;
    //create a fast and a slow pointer
    node *fast=head_ptr;
    node *slow=head_ptr;
    bool loop_found=false;
    //use floyd's loop detection algorithm
    while(fast!=NULL&&fast->link()!=NULL)
    {
        fast=fast->link()->link();
        slow=slow->link();
        if(fast==slow)
        {
            loop_found=true;
            break;
        }
    }
    if(loop_found==false)
        return NULL;
    slow=head_ptr;
    while(slow!=fast)
    {
        slow=slow->link();
        fast=fast->link();
    }
    return slow;
}
    
}
