#pragma once

#include <assert.h>
#include <deque>
#include <iosfwd>
#include <iostream>

//LSB
enum Rank
{
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Knave,
    Queen,
    King
};

//MSB
enum Suit
{
    Diamonds,
    Clubs,
    Hearts,
    Spades
};

//Colour only matters for Joker cards
enum Colour
{
    Black,
    Red
};

//Distinguish between Standard and Joker cards
enum Kind
{
    StandardKind,
    JokerKind
};

class Card
{
public:
    Card(Rank r, Suit s) : bits((unsigned)s << 4 | (unsigned)r) { } //Casting for unsigned integers
    Card(Colour c) : bits((unsigned)(1) << 6 | (unsigned)c << 7) { }
    Rank getRank() const { return(Rank) (0b00001111 & bits); } //LSB of 8-bit number
    Suit getSuit() const { return(Suit) ((0b11110000 & bits) >> 4); } //MSB of 8-bit number
    bool operator==(Card c) { return bits == c.bits; }  //Overload operators with bits
    bool operator!=(Card c) { return !(bits == c.bits); }
    friend bool operator<(Card a, Card b) { return a.getRank() < b.getRank(); }
    friend bool operator>(Card a, Card b) { return b.getRank() < a.getRank(); }
    friend bool operator<=(Card a, Card b) { return !(b.getRank() < a.getRank()); }
    friend bool operator>=(Card a, Card b) { return !(a.getRank() < b.getRank()); }
    Colour getColour() const
    {
        if(((bits >> 6) & 0b1) == 1)
            return (Colour) ((bits >> 7) & 0b1);
        else
            return (Colour) - 1;
    }
    
private:
    Rank rank;
    Suit suit;
    unsigned char bits;
};

//Joker class that can retrieve the colour of the card
class Joker
{
    Colour colour;
    
public:
    Joker(Colour c) : colour(c) { }
    Colour getColour() const { return colour; }
};

//PlayingCardUnion between a Standard card and a Joker card
union PlayingCardUnion
{
    Card standardCard;
    Joker jokerCard;
    
    PlayingCardUnion(Rank r, Suit s) : standardCard(r, s) { }
    PlayingCardUnion(Colour c) : jokerCard(c) { }
};

//PlayingCard class using a tagged union
class PlayingCard
{
    Kind kind;
    PlayingCardUnion playingCardUnion;
    
public:
    PlayingCard(Rank r, Suit s) : kind(StandardKind), playingCardUnion(r, s) { }
    PlayingCard(Colour c) : kind(JokerKind), playingCardUnion(c) { }
    bool isStandardCard() const { return kind == StandardKind; }
    bool isJokerCard() const { return kind == JokerKind; }
    //Get function for rank
    Rank getRank() const
    {
        assert(isStandardCard());
        
        return playingCardUnion.standardCard.getRank();
    }
    //Get function for suit
    Suit getSuit() const
    {
        assert(isStandardCard());
        
        return playingCardUnion.standardCard.getSuit();
    }
    //Get function for colour
    Colour getColour() const
    {
        assert(isJokerCard());
        
        return playingCardUnion.jokerCard.getColour();
    }
    //Get function for Standard card
    Card getStandardCard() const
    {
        assert(isStandardCard());
        
        return playingCardUnion.standardCard;
    }
    //Get function for Joker card
    Joker getJokerCard() const
    {
        assert(isJokerCard());
        
        return playingCardUnion.jokerCard;
    }
    //Overload the << opeartor to display the suit of the card
    friend std::ostream& operator<<(std::ostream& out, Suit s)
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
    friend std::ostream& operator<<(std::ostream& out, Rank r)
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
    friend std::ostream& operator<<(std::ostream& out, Card c)
    {
        return out << c.getRank() << c.getSuit();
    }
};

//Game class used for Game of War
class Game
{
public:
    Game() = default;
    void gameOfWar(int);
    
private:
    int Player1, Player2;
};

//Able to remove cards off of the front and back of the deck
struct Deck : std::deque<Card> {
    using std::deque<Card>::deque;
};

//Overloading ostream operators
std::ostream& operator<<(std::ostream& out, Suit s);
std::ostream& operator<<(std::ostream& out, Rank r);
std::ostream& operator<<(std::ostream& out, Card c);
std::ostream& operator<<(std::ostream& out, Deck const& d);
inline std::ostream& operator<<(std::ostream& out, Colour colour)
{
    if(colour == Black)
        out << "Black Joker";
    else if(colour == Red)
        out << "Red Joker";
    
    return out;
}
