//
//  question1.cpp
//  Lab 1
//
//  Created by jgrom on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
using namespace std; //set the default to std
int main ( int argc,const char *argv[])
{
    cout<<"question 1, type something \n";
    string words;
    getline(cin,words); //take input from the keyboard and set = to string
    int i=0,j=0,k=0;
    //itterate through the string and only count a character if it's alpha
    while(words[k]!='\0')
    {
        j++; //counts total number of elements in the string
        if(isalnum(words[k]))
            i++; //i counts number of alphanumeric characters
        k++; //itterates to the next character in the string
    }
    j=j-i; //j now tracks the number of non-alphanumeric characters
    printf("%s has %d alphanumeric characters and %d non-alphanumeric characters\n",words.c_str(),i,j);
    return 0;
    
}
