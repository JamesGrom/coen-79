//
//  poly.cpp
//  
//
//  Created by James Grom on 2/8/20.
//

#include <cmath>
#include <ios>
#include "poly.h"
#include <stdio.h>
#include <iomanip>
#include <cassert>
#include <climits>
//invariants and implementation of the polynomial class explained
//      current degree always holds the greatest index with non-zero coeffictient, if the polynomial doesn't have a degree, set current degree to 0
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.

using namespace std;

namespace coen79_lab4
{

// MEMBER CONSTANTS
//   const static size_t MAXIMUM_DEGREE
//     The size of the maximum exponent permitted for a polynomial.
//static const unsigned int polynomial::MAXIMUM_DEGREE

// CONSTRUCTOR for the polynomial class
//   polynomial(double c = 0.0, unsigned int exponent = 0)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE
//     POSTCONDITION: This polynomial has been created with all zero
//     coefficients, except for coefficient c for the specified exponent.
//     When used as a default constructor (using default values for
//     both arguments), the result is a polynomial with all zero
//     coefficients.
polynomial::polynomial(double c, unsigned int exponent)
{
    assert(exponent <= MAXIMUM_DEGREE);
    for(unsigned int i=0;i<=MAXIMUM_DEGREE;i++)
    {
        coef[i]=0;
    }
    coef[exponent]=c;
    current_degree=exponent;
}

// HELPER MEMBER FUNCTIONS for the polynomial class
//   void update_current_degree()
//     POSTCONDITION: The current degree is set to the highest exponent
//      with a non-zero coeficient.
void polynomial::update_current_degree()
{
    current_degree=0;
    for(unsigned int i=1;i<=MAXIMUM_DEGREE;i++)
    {
        if(coef[i]!=0)
        {
            current_degree=i;
        }
    }
    return;
}


// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void assign_coef(double coefficient, unsigned int exponent)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Sets the coefficient for the specified exponent.
void polynomial::assign_coef(double coefficient, unsigned int exponent)
{
    assert(exponent<=MAXIMUM_DEGREE);
    coef[exponent]=coefficient;
    update_current_degree();
    return;
}

//   void add_to_coef(double amount, unsigned int exponent)
//     PRECONDITION: exponent <= MAXIMUM_DEGREE.
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
void polynomial::add_to_coef(double amount, unsigned int exponent)
{
    assert(exponent<=MAXIMUM_DEGREE);
    coef[exponent]+=amount;
    update_current_degree();
    return;
}
//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
void polynomial::clear( )
{
    for(unsigned int i=0;i<=MAXIMUM_DEGREE;i++)
       {
           coef[i]=0;
       }
    update_current_degree();
    return;
}
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   polynomial antiderivative( ) const
//     PRECONDITION: degree( ) < MAXIMUM_DEGREE
//     POSTCONDITION: The return value is the antiderivative (indefinite integral)
//     of this polynomial.
//     NOTE: The return polynomial always has a constant term of zero.
polynomial polynomial::antiderivative() const
{
    assert(degree( ) < MAXIMUM_DEGREE);
    polynomial ans;
    
    
    for (int i=degree()+1;i>0;i--)
    {
        ans.coef[i]=coef[i-1]/i;
       // ans.coef[i + 1] = coef[i] / (i + 1);
    }
    ans.update_current_degree();
    ans.coef[0]=0;
    return ans;
}

//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//     NOTE: For exponents > MAXIMUM_DEGREE, the return value is always zero.
double polynomial::coefficient(unsigned int exponent) const
{
    if (exponent > MAXIMUM_DEGREE)
    {
        return 0;
    }
    return coef[exponent];
}

//   double definite_integral(double x0, double x1) const
//     POSTCONDITION: Returns the value of the definite integral computed from
//     x0 to x1.  The answer is computed analytically.
double polynomial::definite_integral(double x0, double x1) const
{
    polynomial ans=antiderivative();
    double yeild=ans.eval(x1)-ans.eval(x0);
    return yeild;
}

//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero (even
//     though, technically, this polynomial does not have a degree).
unsigned int polynomial::degree( ) const
{
    return current_degree;
}

//   polynomial derivative( ) const
//     POSTCONDITION: The return value is the first derivative of this
//     polynomial.
polynomial polynomial::derivative( ) const
{
    polynomial ans;
    for (int i = 1; i <= degree(); i++)
    {
        ans.coef[i - 1] = coef[i] * i;
    }

    ans.update_current_degree();
    return ans;
}

//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
double polynomial::eval(double x) const
{
    double ans= 0;
    for (int i = 0; i <= degree(); i++) {
        ans += coef[i] * pow(x, i);
    }
    return ans;
}

//   bool is_zero( ) const
//     POSTCONDITION: The return value is true if and only if the polynomial
//     is the zero polynomial.
bool polynomial::is_zero( ) const
{
    if(current_degree==0&&coef[0]==0)
    {
        return true;
    }
    return false;
}

//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
unsigned int polynomial::next_term(unsigned int e) const
{
    unsigned int i;
    for( i=e+1;i<=MAXIMUM_DEGREE;i++)
    {
        if(coef[i]!=0)
        {
            break;
        }
    }
    if(i>MAXIMUM_DEGREE)
        return 0;
    return i;
}

//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
unsigned int polynomial::previous_term(unsigned int e) const
{
    for(int i=e-1;i>=0;i--)
    {
        if(coef[i]!=0)
        {
            return (double)i;
        }
    }
    return UINT_MAX;
}


// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
double polynomial::operator() (double x) const
{
    return eval(x);
}


// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
polynomial operator +(const polynomial& p1, const polynomial& p2)
{
    polynomial ans;
    for(int i=0;i<=polynomial::MAXIMUM_DEGREE;i++)
    {
        ans.coef[i]=p1.coef[i] + p2.coef[i];;
    }
    ans.update_current_degree();
    return ans;
}


//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.


polynomial operator -(const polynomial& p1, const polynomial& p2)
{
    polynomial ans;
    for(int i=0;i<=polynomial::MAXIMUM_DEGREE;i++)
    {
        ans.coef[i]=p1.coef[i] - p2.coef[i];;
    }
    ans.update_current_degree();
    return ans;
}

//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     PRECONDITION: p1.degree( ) + p2.degree( ) <= MAXIMUM_DEGREE.
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
polynomial operator *(const polynomial& p1, const polynomial& p2)
{
    //assert(p1.degree()+p2.degree()<=MAXIMUM_DEGREE);
    polynomial ans;
    int index;
    for (int i = 0; i <= p1.degree(); i++)
    {
        for (int j = 0; j <= p2.degree(); j++)
        {
            index= i + j;
            ans.coef[index] += p1.coef[i] * p2.coef[j];
        }
    }
    ans.update_current_degree();
    return ans;
}
           
// NON-MEMBER OUTPUT FUNCTIONS for the polynomial Class
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//     The format of the polynomial when printed should be as follows:
//              -2.5x^2 - 4x + 5.9
//     1) There should be exactly 1 space between the numbers and the operators.
//     2) The constant coeficient should be printed by itself: 5.3, not 5.3x^0
//     3) The first coeficient chould be followed by a plain x: 4x, not 4x^1
//     4) The highest degree's coeficient should have a sign: -2.5x^2, but the
//          following values should all be separated by appropriate operators
//          and then printed unsigned: -2.5x^2 - 4x...
//     5) If you manipulate any settings of the outstream inside of this,
//          such as the precision, they should be restored to what they were
//          at the start of the function before returning.
ostream& operator << (ostream& out, const polynomial& p)
{
    std::streamsize ss = std::cout.precision();
    double temp=0;
    out<<std::fixed;
    out<<std::setprecision(1);
    //handle zero polynomial
    if(p.is_zero())
    {
        out << 0.0;
        return out;
    }
    else if(p.degree()==0&&p.coefficient(0)!=0)
    {
    out<< p.coefficient(0);
        return out;
    }
    for(int i=p.degree();i>=0;i--)
    {
        temp=p.coefficient(i);
        if(temp!=0)
        {
            if(i==1&&i!=p.degree())
            {
                if(temp<0)
                {
                    if(temp==1)
                    {
                        out<< " - ";
                    }
                    else
                    {
                        out<< " - "<< abs(temp);
                    }
                }
                else
                {
                    if(temp==1)
                    {
                        out<< " + ";
                    }
                    else
                    {
                        out<< " + "<< abs(temp);
                    }
                    
                }
                out<< "x";
            }
            else if ( i==0)
            {
                if(temp<0)
                {
                    out<< " - "<< abs(temp);
                }
                else
                {
                    out<< " + "<< abs(temp);
                }
            }
            else if (i==p.degree())
            {
                if(temp==1)
                {
                    if(i==1)
                        out<< "x";
                else
                    out << "x^"<< i;
                }
                else
                {
                    if(i==1)
                        out<<temp<<"x";
                    else
                        out<< temp << "x^" << i;
                }
                
            }
            else
            {
                if(temp<0)
                {
                    if(temp==1)
                    {
                        out<< " - ";
                    }
                    else
                    {
                        out<< " - "<< abs(temp);
                    }
                }
                else
                {
                    if(temp==1)
                    {
                        out<< " + ";
                    }
                    else
                    {
                        out<< " + "<< abs(temp);
                    }
                }
                out << "x^" << i;
            }
            
        }
        
    }
    out<<std::setprecision(ss);
    //out<<std::defaultfloat;
    
    return out;
}
// The value semantics (copy constructor and assignment operator) are valid for
// the polynomial class.


}
