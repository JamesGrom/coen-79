//
//  mystring.cpp
//  
//
//  Created by James Grom on 2/11/20.
//

#include <stdio.h>
#include "mystring.h"
#include <iostream>
#include <cassert>
#include <cstring> //string library functions, must use safe versions and no strdup

//invariants of the string class
//all strings are null terminates
//current_length holds the #of characters doesn't include the null character
//allocated holds the amount of space allocated in the heap char array

//will this cause a problem?
using namespace coen79_lab5;

namespace coen79_lab5
{
// default CONSTRUCTOR for the string class:
//   string(const char str[ ] = "") -- default argument is the empty string.
//     Precondition: str is an ordinary null-terminated string.
//     Postcondition: The string contains the sequence of chars from str.
//
string::string(const char str[ ])
{
    current_length=strlen(str); //gets the length of the input string
    allocated=current_length+1;//account for null character allocation
    characters=new char [allocated]; //allocates enough room for array and null character
    strncpy(characters,str,current_length);//points the private member variable characters to the dynamically allocated array
   
}

//   string(char c)
//     Postcondition: The string contains c and then the null character.
//
string::string(char c)
{
    current_length=1;
    allocated=current_length+1;
    characters=new char[allocated];
    characters[0]=c;
    characters[1]='\0';
    
}

//   string(const string& source) -- Copy Constructor.
//     Postcondition: The string becomes a copy of the source string.
//
string::string(const string& source)
{
    current_length=source.current_length;
    allocated=source.allocated;
    characters=new char[allocated];//allocates the same amount of room as was allocated by the source array
    strncpy(characters,source.characters,current_length);//copies the characters from source into the temp array and points the characters pointer to that array
}


// destructor for the string class
//deletes array of characters from the heap
//sets current_length and allocated to 0 to reflect the change
//
string::~string()
{
    delete [] characters;
}


// MODIFICATION MEMBER FUNCTIONS for the string class:
//
//
//
//
//   void operator +=(const string& addend)
//     Postcondition: addend has been catenated to the end of the string.
//
void string::operator +=(const string& addend)
{
    //set the new length appropriately
    current_length+=addend.current_length;
    //allocate new mem only if needed
    if(current_length>=allocated)
    {
        reserve(current_length+1);//account for null character
        //reserve accounts for incrementing allocated member varaible as needed
    }
    //concatonate the appropriate characters
    strncat(characters,addend.characters,addend.current_length);
    return;
}

//     Precondition: addend is an ordinary null-terminated string.
//     Postcondition: addend has been catenated to the end of the string.
//
void string::operator +=(const char addend[])
{
    current_length+=strlen(addend);

    //allocate new memory if needed
    if(current_length>=allocated)
    {
        reserve(current_length+1);
    }
    strncat(characters,addend,strlen(addend));
    return;
}



//     Postcondition: The single character addend has been catenated to the
//     end of the string.
//
void string::operator +=(char addend)
{
    current_length++;//account for added character
    //allocate memory if needed
   // printf("allocated:%lu \n",allocated);
    if(current_length>=allocated)
    {
        //printf("screwup2\n");
        reserve(current_length+1);//account for the null character
    }
    //null is always to be placed at index [current_length]
    characters[current_length-1]=addend;//account for 0 indexing
    characters[current_length]='\0';
    return;
}

//   void reserve(size_t n)
//     Postcondition: All functions will now work efficiently (without
//     allocating new memory) until n characters are in the string.
//
void string::reserve(size_t n)
{
    //make sure it's a valid argument
    assert(!(n<0));
    char *vip=new char[n];//reserve the new memory needed
    //copy the previous string to the new memory
    strncpy(vip,characters,current_length);
    //point characters to this new memory location
    characters=vip;
    //change allocated as needed
    allocated=n;
    return;
}

//postcondition: the calling string is now equal to a copy of the argument string
//
string& string::operator =(const string& source)
{
    //if it's copying itself, then no need to copy
    if(this==&source)
    {
        return *this;
    }
    current_length=source.current_length;
    //not copying itself therefore continue
    //delete the memory to be overwritten so there's no memory leak
    delete [] characters;
    //allocate necessary memory
    characters=new char[source.allocated];//allocate the same amount of space as the source has
    allocated=source.allocated;
    //copy the strings
    strncpy(characters,source.characters,current_length);
    //add a null character
    characters[current_length]='\0';
    return *this;
}


//     Precondtion: position <= length()
//     Postcondition: The source string is inserted into this string before
//     the character at the given index.
//
 void string::insert(const string& source, unsigned int position)
{
    //make sure valid precondition
    assert(position<=length());
    //save the characters to be overwritten
    char backend[current_length-position];
    if(current_length+source.current_length>=allocated)
    {
        reserve(current_length+source.current_length+1);//account for null
    }
    //copy the characters to be overwritten into the backend array
    for(int i=position;i<current_length;i++)
    {
        backend[i-position]=characters[i];
        //doesn't copy null character to backend
    }
    //insert the new string
    for(int i=0; i<source.current_length; i++) {
        characters[position+i] = source.characters[i];
    }
    //insert the backend
    for(int i=0;i<(current_length-position);i++) {
        characters[position+source.current_length+i] = backend[i];
    }
    //increment current length as needed
    current_length+=source.current_length;
    characters[current_length]='\0';
    return;
}

//   void dlt(unsigned int position, unsigned int num)
//     Precondition: (position + num) <= length( ).
//     Postcondition: num characters are deleted from the sequence, starting
//     at index position.
//
void string::dlt(unsigned int position, unsigned int num)
{
    assert((position + num) <= length( ));
    int nextChar = position+num;
    while(characters[nextChar] != '\0') {
        characters[nextChar - num] = characters[nextChar];
        nextChar++;
    }
    current_length -= num;
    characters[current_length] = '\0';
    return;
}


//     Precondition: position < length()
//     Postcondtion: the character at the given position in the string is
//     replaced with c.
//
void string::replace(char c, unsigned int position)
{
    assert(position < length());
    characters[position]=c;
    return;
}

//     Precondition: (position + source.length()) <= length()
//     Postcondtion: the characters in this string starting at position are
//     replaced with those in the source srting.
//
void string::replace(const string& source, unsigned int position)
{
    assert((position + source.length()) <= length());
    //because of precondition no need to allocate new memory
    //copy from source into the array
    for(int i=0;i<source.length();i++)
    {
        characters[position+i] = source.characters[i];
    }
    return;
}



//     Precondition: position < length( ).
//     Postcondition: The value returned is the character at the specified
//     position of the string. A string's positions start from 0 at the start
//     of the sequence and go up to length( )-1 at the right end.
//
char string::operator [ ](size_t position) const
{
    assert(position < length());
    return characters[position];
}


//     Postcondition: The location of the first occurence of the character c
//     within this string is returned. If the string does not contain c, -1 is
//     is returned.
//
int string::search(char c) const
{
    char *p=characters;
    int index=0;
    while(*p!='\0'&&*p!=c)
    {
        p++;
        index++;
    }
    if(*p=='\0')
    {
        return -1;
    }
    return index;
}


//     Postcondition: Returns the index of the start of the first instance of
//     the given substring inside of this string. If the substring is not found,
//     this function returns -1.
//
int string::search(const string& substring) const
{
    bool found;
    //check for substring starting at each position
    for(int i=0;i<current_length;i++)
    {
        found=true;//only turns to false if the substring is not found
        for(int j=0;j<substring.current_length;j++)
        {
            if(characters[i+j]!=substring[j])
            {
                found=false;
                break;
            }
        }
        if(found==true)
        {
            return i;
        }
        
    }
    return -1;
}


//     Postcondition: The count of the occurence of the character c within this
//     string is returned.
//
unsigned int string::count(char c) const
{
    char *p=characters;
    int counter=0;
    while(*p!='\0')
    {
        if(*p==c)
        {
            counter++;
        }
        p++;
    }
    return counter;
    
}


//   ostream& operator <<(ostream& outs, const string& source)
//     Postcondition: The sequence of characters in source has been written
//     to outs. The return value is the ostream outs.

std::ostream& operator <<(std::ostream& outs, const string& source)
{
    outs<<source.characters<<std::endl;
    return outs;
}

bool operator ==(const string& s1, const string& s2)
{
    if(strcmp(s1.characters,s2.characters)==0)
    {
        return true;
    }
    return false;
}

bool operator !=(const string& s1, const string& s2)
{
    if(strcmp(s1.characters,s2.characters)==0)
    {
        return false;
    }
    return true;
}

bool operator > (const string& s1, const string& s2)
{
    int result;
    result=strcmp(s1.characters,s2.characters);
    if(result<=0)
    {
        return false;
    }
    return true;
}

bool operator < (const string& s1, const string& s2)
{
    int result;
    result=strcmp(s1.characters,s2.characters);
    if(result>=0)
    {
        return false;
    }
    return true;
}

bool operator >=(const string& s1, const string& s2)
{
    int result;
    result=strcmp(s1.characters,s2.characters);
    if(result<0)
    {
        return false;
    }
    return true;
}

bool operator <=(const string& s1, const string& s2)
{
    int result;
    result=strcmp(s1.characters,s2.characters);
    if(result>0)
    {
        return false;
    }
    return true;
}

//   string operator +(const string& s1, const string& s2)
//     Postcondition: The string returned is the catenation of s1 and s2.
//
string operator +(const string& s1, const string& s2)
{
    //create an empty new string
    string ans = "";
    ans= s1;
    string str2(s2);
    //concatenate
    ans +=str2;
    return ans;
}
//
string operator +(const string& s1, const char addend[ ])
{
    //create an empty new string
    string ans = "";
    //set equal to s1
    ans = s1;
    //create a string that is a copy of addend
    string str2(addend);
    //concatenate
    ans +=str2;
    //return concatenated string
    return ans;
 
}



//   istream& operator >>(istream& ins, string& target)
//     Postcondition: A string has been read from the istream ins, and the
//     istream ins is then returned by the function. The reading operation
//     skips white space (i.e., blanks, newlines, tabs) at the start of ins.
//     Then the string is read up to the next white space or the end of the
//     file. The white space character that terminates the string has not
//     been read.
std::istream& operator >> (std::istream& ins, string& target)
{
    char temp;
    target="";
    while(!ins.eof()&&isspace(ins.peek()))
    {
        ins.ignore();
    }
    
    while(!ins.eof()&&!isspace(ins.peek()))
    {
        //printf("here\n");
        ins>>temp;
        //printf("her\n");
        target+=temp;
    }
    return ins;
}
}

















