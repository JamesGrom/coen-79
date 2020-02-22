// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2
{
    //constructor for the statistician class, accounts for the lack of a precondition
    //preventing a call of length() or sum() on an empty statistician object
    statistician::statistician()
    {
        leng=0;
        sm=0.0;
    }
    statistician::statistician(int l,double s,double max, double min)
    {
        leng=l;
        sm=s;
        mx=max;
        mn=min;
    }
    void statistician::next(double a)
    {
        //if this is the first entry to be placed into the object, then it is both the max and min
        if(leng==0)
        {
            mx=a;
            mn=a;
        }
        leng++;
        sm+=a;
        if(a<mn)
        { 
            mn=a;
        }
        if(a>mx)
        {
            mx=a;
        }
        return;
    }
    //returns the number of elements added to the object
    int statistician::length() const
    {
        return leng;
    }
    double statistician::sum() const
    {
        return sm;
    }
    double statistician::mean() const
    {
        double a = (double) leng; //casts length into a double and saves its value into a
        return sm/a;
    }
    double statistician::maximum () const
    {
        return mx;
    }
    double statistician::minimum () const
    {
        return mn;
    }
    void statistician::reset ()
    {
        leng=0;
        sm=0.0;
        return;
    }
    statistician operator +(const statistician& s1, const statistician& s2)
    {
        //creates the statistician object to be returned
        int len1=s1.length();
        int len2=s2.length();
        int len= len1+len2; //new statistician length
        double e;
        double max;
        double min;
        //if s1 is empty but s2 isn't just duplicate s2
        if(len!=0 &&len1==0)
        {
            e=s2.sum();
            max=s2.maximum();
            min=s2.minimum();
            
        }
        //if s2 is empty but s1 usn't just duplicate s1
        else if (len!=0&&len2==0)
        {
            e=s1.sum();
            max=s1.maximum();
            min=s1.minimum();
        }
        else if(len==0)
        {
            return statistician();//you're adding 2 empty statisticians therefore just create a new one
        }
        else //neither statistician is empty therefore preconditions for all functions are valid
        {
            //sum of the new object is the sum of both objects
            e=s2.sum()+s1.sum();
            //max of the new object is the greater of the two maxes of both objects
            if(s2.maximum()>=s1.maximum())
            {
                max=s2.maximum();
            }
            else
            {
                max=s1.maximum();
            }
            //min of the new object is the smaller of the two mins of both objects
            if(s2.minimum()<=s1.minimum())
            {
                min=s2.minimum();
            }
            else
            {
                min=s1.minimum();
            }
        }
        return statistician(len,e,max,min);
    }
    
    statistician operator *(double scale, const statistician& s)
    {
        int len=s.length();
        //if the statistician is empty then the statistician produced 0's out
        if (len==0)
        {
            return statistician();
        }
        if(scale>=0)
        {
        double sum= scale*(s.sum());
        double min= scale*(s.minimum());
        double max= scale*(s.maximum());
        return statistician(len,sum,max,min);
        }
        else
        {
            double sum= scale*(s.sum());
            double max= scale*(s.minimum());
            double min= scale*(s.maximum());
            return statistician(len,sum,max,min);
        }
    }
    
    bool operator ==(const statistician& s1, const statistician& s2)
    {
        int len1=s1.length(),len2=s2.length();
        int flag=len1*len2;
        if(flag==0)
        {
            if(len1==len2)
            {
                return true;//both statisticians are empty therf, they are equal
            }
            else
            {
                return false;//they have a different length
            }
        }
        //here we know that neither statistician is empty so we can call any member function
        double sum1=s1.sum(),sum2=s2.sum();
        double max1=s1.maximum(),max2=s2.maximum();
        double min1=s1.minimum(),min2=s2.minimum();
        if((len1==len2)&&(sum1==sum2)&&(max1==max2)&&(min1==min2))
        {
            //then the statisticians are essetially identical
            return true;
        }
        else
        {
            return false;
        }
        
    }
    
    
}


