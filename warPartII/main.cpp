//Project 1:    Game of War Part II
//Created by:   Ryne Turner
#include <algorithm>
#include <iostream>

//All of the classes were placed in one set of Cards files in order to simplify the design
//Much of this code was built upon the better implementaion of Part I demonstrated in class
#include "Cards.hpp"

int main()
{
    //Declare a Game class object
    Game run;
    
    //Execute the Game of War
    run.gameOfWar(1);
    
    //End program
    return 0;
}
