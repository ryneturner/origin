
//Practice 5:    Hierarchical Representation of Playing Cards
//Created by:    Ryne Turner
#include <algorithm>
#include <iostream>

#include "Cards.hpp"

int main()
{
    //Ability to print cards
    Standard standardCard(Knave, Spades);
    std::cout << standardCard.getSuit() << "    " << standardCard.getRank() << std::endl;
    std::cout << standardCard << std::endl;
    
    //Return the colour of cards
    Joker jokerCardBlack(Black), jokerCardRed(Red);
    std::cout << jokerCardBlack << "    " << jokerCardBlack.getColour() << "    " << jokerCardRed.getColour() << std::endl;
    
    //Query if the card is a standard card or a joker card
    PlayingCard cardExampleStandard(StandardKind), cardExampleJoker(JokerKind);
    std::cout << cardExampleStandard.getKind() << "   " << cardExampleJoker.getKind() << std::endl;
    
    //End program
    return 0;
}
