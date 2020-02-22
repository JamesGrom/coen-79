//
//  random.cpp
//  
//
//  Created by James Grom on 1/24/20.
//

#include "random.h"
#include<iostream>
#include<cassert>

using namespace std;

namespace coen79_lab2
{
//default constructor for the rand_gen object
rand_gen::rand_gen()
{
    seed=1;
    multiplier=40;
    increment=725;
    modulus=729;
}
//rand_gen constructor that allows for hardcoded inputs
rand_gen::rand_gen(int new_seed,int new_multiplier,int new_increment,int new_modulus)
{
    seed=new_seed;
    multiplier=new_multiplier;
    increment=new_increment;
    modulus=new_modulus;
}
//function to set the seed
void rand_gen::set_seed(int new_seed)
{
    seed=new_seed;
    return;
}
//function to generate the next seed and the random number
int rand_gen::next()
{
    int new_seed=((multiplier*seed+increment)%modulus);
    seed=new_seed;
    return new_seed;
}
//prints the info about the current rand_gen object
void rand_gen::print_info() const
{
    printf("Seed: %d \n",seed);
    printf("Multiplier: %d \n",multiplier);
    printf("Increment: %d \n",increment);
    printf("Modulus %d \n",modulus);
    return;
}


}
