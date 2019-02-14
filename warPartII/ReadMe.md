This update to the game of war uses many of the implementations in lecture to efficiently create a deck of cards base on
the enumerated rank and suit, a clear improvement from the last version of the code.  This streamlined version drastically
simplified running the game of war, which was about 100 lines of code located in one very basic class.  Bit shifting with 
8-bit integers was used in the getRank() and getSuit() operators.  Again in this assignment, the suit does not matter, so 
only the four least significant bits are relevant to determining the outcome of the game.  The enumerated values are then
ordered by their bit values.  The game is played in a realistic order depending on the original shuffling of the cards,
with each player drawing a card per round.  The Game class encapsulates the gameOfWar() function so that the rest of the
program can be used to run other card games as well.
