//
//  question3.cpp
//  Lab 1
//
//  Created by jgrom on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <iomanip>
using namespace std;
int main(int argc,const char*argv[])
{
    if(argc<2) //stops program if filename is missing
    {
        cout<<"missing filename\n";
        return 0;
    }
    string filename = argv[1]; //saves the filename of the textfile
    ifstream in_file; //creates in_file object
    in_file.open(filename); //opens the textfile
    string tempstring; //creates a string object
    int i,j,counter=0;
    while(in_file && in_file.peek()!=EOF) //scans the text file until the end/until nothing left
    {
        i=0;
        j=0;
        in_file>>tempstring; //saves a word to the string from the textfile
        while(tempstring[i]!='\0') //scans the string till it reaches null character
        {
            if(isalpha(tempstring[i])) //only enters if it's an alphanumeric character
            {
                tempstring[i]=toupper(tempstring[i]);//makes all letters of the 10+character word uppercase
                j++; //counts each character of the word
            }
            i++;
        }
        if(j>=10) //if the word has more than 10 characters, it is printed
        {
            printf( "%s \n",tempstring.c_str());
        }
        
    }
    return 0;
}
