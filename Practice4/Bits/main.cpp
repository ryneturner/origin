//Practice 4:    Binary Representation
//Created by:    Ryne Turner
#include <algorithm>
#include <iostream>

#include "Cards.hpp"

int main()
{
    //Declare a red and black card
    Card test1{Red}, test2{Black};
    
    //Print card to verify this works
    std::cout << test1.getColour() << " " << test2.getColour();
    
    //Declare a Game class object
    Game run;
    
    //Execute the Game of War
    run.gameOfWar(1);
    
    //End program
    return 0;
}
