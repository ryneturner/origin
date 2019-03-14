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
//Overload the << operator to display the Standard card
std::ostream& operator<<(std::ostream& out, Standard c)
{
    return out << c.getRank() << c.getSuit();
}
//Overload the << operator to display the Joker card
std::ostream& operator<<(std::ostream& out, Joker c)
{
    return out << c.getColour();
}
//Overload the << operator to display the card colour
std::ostream& operator<<(std::ostream& out, Colour c)
{
    if(c == Black)
        return out << "Black Joker";
    else
        return out << "Red Joker";
}
//Overload the << operator to display the card kind
std::ostream& operator<<(std::ostream& out, Kind k)
{
    if(k == StandardKind)
        return out << "Standard Card";
    else
        return out << "Joker Card";
}

PlayingCard::PlayingCard() { }

//Get colour
Colour Joker::getColour() const
{
    return colour;
}

//Get kind
Kind PlayingCard::getKind() const
{
    return kind;
}

//Get rank
Rank Standard::getRank() const
{
    return rank;
}

//Get suit
Suit Standard::getSuit() const
{
    return suit;
}

