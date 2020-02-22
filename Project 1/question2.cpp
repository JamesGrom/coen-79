//
//  question2.cpp
//  Lab 1
//
//  Created by jgrom on 1/10/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int main(int argc,const char *argv[])
{
    int i,j,k;
    for(k=0;k<=5;k++) //5 lines to be created
    {
        cout<<setw(k+1); //sets the initial indentation relative to row number
        for(i=0;i<10;i++)
        {
            cout<<i; //prints digits 0-9
        }
        cout<<setw(k+6); //spaces relative to the row number
        for(i=9;i>=0;i--)
        {
            cout<<i; //prints digits 9-0
        }
        cout<<"\n"; //creates a new line for each row
        
        
        
    }
        
        
    
}
