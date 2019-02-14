#pragma once

#include <deque>
#include <iosfwd>

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
