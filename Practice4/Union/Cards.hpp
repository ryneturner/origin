#pragma once

#include <deque>
#include <iosfwd>
#include <assert.h>

//LSB
enum Rank
{
    Ace,    //0001
    Two,    //0010
    Three,  //0011
    Four,   //0100
    Five,   //0101
    Six,    //0110
    Seven,  //0111
    Eight,  //1000
    Nine,   //1001
    Ten,    //1010
    Knave,  //1011
    Queen,  //1100
    King    //1101
};

//MSB
enum Suit
{
    Diamonds,   //0001
    Clubs,      //0010
    Hearts,     //0100
    Spades      //1000
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

//Card class where each card is represented by SSSS RRRR
class Card
{
public:
    Card(Rank r, Suit s) : bits((unsigned)s << 4 | (unsigned)r) { } //Casting for unsigned integers
    Rank getRank() const { return(Rank) (0b00001111 & bits); } //LSB of 8-bit number
    Suit getSuit() const { return(Suit) ((0b11110000 & bits) >> 4); } //MSB of 8-bit number
    bool operator==(Card c) { return bits == c.bits; }  //Overload operators with bits
    bool operator!=(Card c) { return !(bits == c.bits); }
    friend bool operator<(Card a, Card b) { return a.getRank() < b.getRank(); }
    friend bool operator>(Card a, Card b) { return b.getRank() < a.getRank(); }
    friend bool operator<=(Card a, Card b) { return !(b.getRank() < a.getRank()); }
    friend bool operator>=(Card a, Card b) { return !(a.getRank() < b.getRank()); }
    
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
