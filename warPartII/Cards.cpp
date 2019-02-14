#include "Cards.hpp"

#include <iostream>
#include <random>

//Overload the << opeartor to display the suit of the card
std::ostream& operator<<(std::ostream& out, Suit s)
{
    switch(s)
    {
        case Diamonds:
            return out << "D";
        case Clubs:
            return out << "C";
        case Hearts:
            return out << "H";
        case Spades:
            return out << "S";
    }
}

//Overload the << operator to display the rank of the card
std::ostream& operator<<(std::ostream& out, Rank r)
{
    switch(r)
    {
        case Ace:
            return out << "A";
        case Two:
            return out << "2";
        case Three:
            return out << "3";
        case Four:
            return out << "4";
        case Five:
            return out << "5";
        case Six:
            return out << "6";
        case Seven:
            return out << "7";
        case Eight:
            return out << "8";
        case Nine:
            return out << "9";
        case Ten:
             return out << "T";
        case Knave:
            return out << "J";
        case Queen:
            return out << "Q";
        case King:
            return out << "K";
    }
}

//Overload the << operator to display the entire card
std::ostream& operator<<(std::ostream& out, Card c)
{
    return out << c.getRank() << c.getSuit();
}

//Precondition:     This function takes in an integer so that it can be called in main().
//Postcondition:    This function returns void and plays the Game of War in the correct card order.
void Game::gameOfWar(int trial)
{
    //Declare counters for Player 1 and Player 2
    int Player1 = 0, Player2 = 0;
    
    //Declare the set of 52 cards to relate suit and rank
    Deck d
    {
        {Ace, Diamonds},
        {Two, Diamonds},
        {Three, Diamonds},
        {Four, Diamonds},
        {Five, Diamonds},
        {Six, Diamonds},
        {Seven, Diamonds},
        {Eight, Diamonds},
        {Nine, Diamonds},
        {Ten, Diamonds},
        {Knave, Diamonds},
        {Queen, Diamonds},
        {King, Diamonds},
        
        {Ace, Hearts},
        {Two, Hearts},
        {Three, Hearts},
        {Four, Hearts},
        {Five, Hearts},
        {Six, Hearts},
        {Seven, Hearts},
        {Eight, Hearts},
        {Nine, Hearts},
        {Ten, Hearts},
        {Knave, Hearts},
        {Queen, Hearts},
        {King, Hearts},
        
        {Ace, Clubs},
        {Two, Clubs},
        {Three, Clubs},
        {Four, Clubs},
        {Five, Clubs},
        {Six, Clubs},
        {Seven, Clubs},
        {Eight, Clubs},
        {Nine, Clubs},
        {Ten, Clubs},
        {Knave, Clubs},
        {Queen, Clubs},
        {King, Clubs},
        
        {Ace, Spades},
        {Two, Spades},
        {Three, Spades},
        {Four, Spades},
        {Five, Spades},
        {Six, Spades},
        {Seven, Spades},
        {Eight, Spades},
        {Nine, Spades},
        {Ten, Spades},
        {Knave, Spades},
        {Queen, Spades},
        {King, Spades},
    };
    
    //Declares a random integer in order to shuffle
    std::random_device rng;
    std::minstd_rand prng(rng());
    std::shuffle(d.begin(), d.end(), prng);
    
    //Print the cards out in the order after first shuffle
    //The cards will be displayed in four rows
    for(int counter = 0; counter < 52; ++counter)
    {
        if(counter % 13 == 0)
            std::cout << std::endl;
        
        std::cout << d[counter] << " ";
    }
    
    std::cout << std::endl << std::endl;
    
    //The for loop iterates through 52 cards
    for(int counter = 0, index = 0, war = 0; counter < 52; counter += 2, ++index)
    {
        //If Player 1 is greater than Player 2
        if(d[counter] > d[counter + 1])
        {
            std::cout << "Player 1 wins Round " << index - war + 1 << std::endl;
            
            Player1 += 2;
        } //If Player 2 is greater than Player 1
        else if(d[counter] < d[counter + 1])
        {
            std::cout << "Player 2 wins Round " << index - war + 1 << std::endl;
            
            Player2 += 2;
        }  //When Player 1 and Player 2 have a card of the same rank, a game of war is played
        else
        {
            std::cout << "WAR!" << std::endl;
            
            //Reshuffled cards
            //This could be improved to only reshuffle the remaining cards
            std::shuffle(d.begin(), d.end(), prng);
            
            //Three cards are played face down and one face up per player, resulting in a "war" of 10 cards
            if(d[counter + 7] > d[counter + 8])
            {
                std::cout << "Player 1 wins the war " << std::endl;
                
                //If there are less than ten cards remaining, the player wins the remaining cards
                if(10 <= (52 - (Player1 + Player2)))
                    Player1 += 10;
                else
                    Player1 += (52 - (Player1 + Player2));
            }
            else
            {
                std::cout << "Player 2 wins the war " << std::endl;
                
                //If there are less than ten cards remaining, the player wins the remaining cards
                if(10 <= (52 - (Player1 + Player2)))
                    Player2 += 10;
                else
                    Player2 += (52 - (Player1 + Player2));
            }
            
            if(counter != 0)
                ++war;
            
            counter += 10;
        }
        
        //std::cout << counter << std::endl;
    }
    
    //Displays total points for Player 1 and Player 2
    std::cout << std::endl << "Total Points for Player 1: " << Player1 << std::endl;
    std::cout << "Total Points for Player 2: " << Player2 << std::endl;
    
    //Determines the total points per player.  If there is a tie, the game must be rerun
    if(Player1 > Player2)
        std::cout << "Player 1 wins!" << std::endl << std::endl;
    else if(Player1 < Player2)
        std::cout << "Player 2 wins!" << std::endl << std::endl;
    else if(Player1 == Player2)
        std::cout << "The war never ended!  Play again!" << std::endl << std::endl;
}
