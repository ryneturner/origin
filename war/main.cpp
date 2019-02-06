//Project 1:    Game of War
//Created by:   Ryne Turner
#include <array>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>

//Use enumerated variables within the struct to denote the suit and rank of each of the 52 cards in the deck
struct Card
{
    int ranking;
    enum Suit {diamonds, clubs, hearts, spades} suit;
    enum Rank {ace = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, knave = 11, queen = 12, king = 13};
    
    //Ace of Spades
    Card() { ranking = 1; suit = spades; };
    Card(Suit, int);
};

//Use class to create the randomGenerator variable that can be used in std::random_shuffle
class Random
{
public:
    int operator() (int);
    
} randomGenerator;

//Initialize variables and functions to build deck
class Deck
{
    int cardNumber;
    Card cardsArray[52];
    
public:
    Deck();
    void shuffle() { std::random_shuffle(&cardsArray[0], &cardsArray[52], randomGenerator); }
    Card retrieve();
    bool checkDeck() { return (cardNumber <= 0); }
};

//Tools to grab cards, count the total cards per player and overall, and the current score
class Players
{
    int score, loseCard;
    Card playerCards[3];
    
public:
    Players();
    Players(Deck &);
    Card retrieve();
    void increment(int add) { score += add; };
    int totalCards() { return score; };
    void switchCard(Deck &);
};

//Precondition:     This takes in a Suit and an int variable in its parameters
//Postcondition:    This allocates new values to the suit and ranking
Card::Card(Suit newSuit, int newRank)
{
    suit = newSuit;
    ranking = newRank;
}

//Precondition:     This takes in the maximum integer variable and using srand to initially seed the random number generator
//Postcondition:    This return the value within the specified range
int Random::operator() (int maximum)
{
    //Seed a random variable for std::random_shuffle
    srand(static_cast<unsigned int>(time(NULL)));
    
    int value = rand();
    
    return (value % maximum);
}

//Precondition:     This takes in no parameters
//Postcondition:    This builds a deck from the numeric assigned values of the cards and their corresponding suit
Deck::Deck()
{
    cardNumber = 0;
    
    for(int counter = 1; counter <= 13; ++counter)
    {
        Card card1(Card::diamonds, counter),
        card2(Card::clubs, counter),
        card3(Card::hearts, counter),
        card4(Card::spades, counter);
        
        cardsArray[cardNumber++] = card1;
        cardsArray[cardNumber++] = card2;
        cardsArray[cardNumber++] = card3;
        cardsArray[cardNumber++] = card4;
    }
}

//Precondition:     This takes in no parameters
//Postcondition:    This retrieves a card from the deck or returns the default value
Card Deck::retrieve()
{
    if(!checkDeck())
        return cardsArray[--cardNumber];
    else
    {
        Card aceOfSpades(Card::spades, 1);
        return aceOfSpades;
    }
}

//Precondition:     This takes in no parameters and is used to grab the cars from the deck
//Postcondition:    This returns a random card value from the playerCards array
Card Players::retrieve()
{
    loseCard = randomGenerator(3);
    return playerCards[loseCard];
}

//Precondition:     This takes in a class reference to the deck
//Postcondition:    In conjunction with Card Deck::retrieve(), this initializes the variables for retrieval
Players::Players(Deck & myDeck)
{
    score = 0;
    
    for(int counter = 0; counter < 3; ++counter)
        playerCards[counter] = myDeck.retrieve();
    
    loseCard = 0;
}

//Precondition:     This takes in a class reference to the deck
//Postcondition:    This grabs a new card for the player
void Players::switchCard(Deck& myDeck)
{
    playerCards[loseCard] = myDeck.retrieve();
}

//Precondition:     This takes in an ostream variable and a reference to the currentCard
//Postcondition:    This uses to switch statements to output the value of the suit and the rank, returning the ostream parameter variable
std::ostream& operator<< (std::ostream& output, Card& currentCard)
{
    switch(currentCard.ranking)
    {
            //Ace is considered the card with the lowest value in this game.  Games of War have many different variations.
        case 1:
            output << "Ace ";
            break;
        case 2:
            output << "2 ";
            break;
        case 3:
            output << "3 ";
            break;
        case 4:
            output << "4 ";
            break;
        case 5:
            output << "5 ";
            break;
        case 6:
            output << "6 ";
            break;
        case 7:
            output << "7 ";
            break;
        case 8:
            output << "8 ";
            break;
        case 9:
            output << "9 ";
            break;
        case 10:
            output << "10 ";
            break;
        case 11:
            output << "Knave ";
            break;
        case 12:
            output << "Queen ";
            break;
        case 13:
            output << "King ";
            break;
    }
    
    switch(currentCard.suit)
    {
        case Card::Suit::diamonds:
            std::cout << "of Diamonds";
            break;
        case Card::Suit::clubs:
            std::cout << "of Clubs";
            break;
        case Card::Suit::hearts:
            std::cout << "of Hearts";
            break;
        case Card::Suit::spades:
            std::cout << "of Spades";
            break;
    }
    
    return output;
}

int main()
{
    //Shuffle the deck
    Deck deck;
    deck.shuffle();
    
    //Initialize two players for the Players class
    Players P1(deck);
    Players P2(deck);
    
    do
    {
        //P1 grabs the card and flips
        Card one = P1.retrieve();
        
        std::cout << "P1 flips " << one << std::endl;
        
        //P2 grabs the card and flips
        Card two = P2.retrieve();
        
        std::cout << "P2 flips " << two << std::endl;
        
        //The if statement compares the rank of the card
        //If it is one on the first round, both cards are gathered by the winning player
        if(one.ranking > two.ranking)
        {
            P1.increment(2);
            
            std::cout << "P1 wins match" << std::endl << std::endl;
        }
        else if(one.ranking < two.ranking)
        {
            P2.increment(2);
            
            std::cout << "P2 wins match" << std::endl << std::endl;
        }//If both cards played have the same rank, the players go to war
        else if(one.ranking == two.ranking)
        {
            std::cout << "War!" << std::endl;
            
            //Execute at least once
            do
            {
                //New cards are retrieved by both players
                one = P1.retrieve();
                two = P2.retrieve();
                
                //The new cards are compared
                if(one.ranking > two.ranking)
                {
                    //Three cards are placed face down in the case of war
                    //Another card is flipped to determine who wins all of the cards
                    //The player that wins the war takes all ten cards played during that round, or whatever is remaaining.  The player with the most cards wins!
                    if((52 - (P1.totalCards() + P2.totalCards())) >= 10)
                        P1.increment(10);
                    else
                        P1.increment(52 - (P1.totalCards() + P2.totalCards()));
                    
                    std::cout << "P1 wins the war!" << std::endl << std::endl;
                }
                else if(one.ranking < two.ranking)
                {
                    if((52 - (P1.totalCards() + P2.totalCards())) >= 10)
                        P2.increment(10);
                    else
                        P2.increment(52 - (P1.totalCards() + P2.totalCards()));
                    
                    std::cout << "P2 wins the war!" << std::endl << std::endl;
                }
                
            } while(one.ranking == two.ranking);
        }
        
        //New cards are retrieved from the deck
        P1.switchCard(deck);
        P2.switchCard(deck);
    } while(!deck.checkDeck() && (P1.totalCards() + P2.totalCards()) < 52); //The total number of cards should not exceed 52
    
    //Display the player's score
    std::cout << "P1's number of Cards: " << P1.totalCards() << std::endl << "P2's number of Cards: " << P2.totalCards() << std::endl;
    
    //Determine the winner
    if(P1.totalCards() > P2.totalCards())
        std::cout << "P1 wins!" << std::endl;
    else if(P1.totalCards() < P2.totalCards())
        std::cout << "P2 wins!" << std::endl;
    else if(P1.totalCards() == P2.totalCards())
        std::cout << "The war never ended!  Play again!" << std::endl;
    
    return 0;
}

