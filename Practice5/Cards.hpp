#pragma once

#include <assert.h>
#include <deque>
#include <iosfwd>
#include <iostream>

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

//Rank determines winner of War
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

//Distinguish the suit
enum Suit
{
    Diamonds,
    Clubs,
    Hearts,
    Spades
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

//PlayingCard class using a tagged union
class PlayingCard
{
    Kind kind;
    
public:
    PlayingCard();
    PlayingCard(Kind k) : kind(k) { }
    Kind getKind() const;
};

//Joker class that can retrieve the colour of the card
class Joker : PlayingCard //PlayingCard
{
    Colour colour;
    
public:
    Joker(Colour c) : colour(c) { }
    Colour getColour() const;
};

//Standard class that represents the main 52 cards
class Standard : PlayingCard //PlayingCard
{
    Rank rank;
    Suit suit;
    
public:
    Standard(Rank r, Suit s) : rank(r), suit(s) { }
    Rank getRank() const;
    Suit getSuit() const;
};

//Able to remove cards off of the front and back of the deck
struct Deck : std::deque<Standard> {
    using std::deque<Standard>::deque;
};

//Overloading ostream operator
std::ostream& operator<<(std::ostream& out, Suit s);
std::ostream& operator<<(std::ostream& out, Rank r);
std::ostream& operator<<(std::ostream& out, Standard c);
std::ostream& operator<<(std::ostream& out, Joker c);
std::ostream& operator<<(std::ostream& out, Colour c);
std::ostream& operator<<(std::ostream& out, Kind k);
std::ostream& operator<<(std::ostream& out, PlayingCard c);

