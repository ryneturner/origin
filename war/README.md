  Using the simple card game Game of War, abstraction was emphasized as a way to reduce the complexity of the code.
The major divisions of this program were to develop 52 cards using enumeration, a deck of cards that can be
shuffled, verified, and distributed among the players, what actually quantifies a player, and deciding the general rules of
the game.  Game of War has many variants, and the one implemented qualifies aces as low and decides who wins by the greatest
number of cards.  Three extra cards are played when the value of the first player's card is equivalent to the value of the 
second player's card.  When all 52 cards have been played at least once, the game is terminated and a winner is decided.
If the game manages to end in a tie, which is very rare, the game can be compiled again to determine the winner.  Division
of variables into classes, uses constructors, and seeding a random variable/using std::random_shuffle were ways that the 
code became more readable to the user, organizing data in such a way that some of the code can be potentially moved to another
card game if a deck of cards is required.  The code is located in its one file main.cpp.  An improvement that could be 
possible would be the division of this code into multiple .cpp and .hpp files and a few of the tricky array implementations
that were necessary because the program would sometimes exceed the number cards passed to the array.  Another improvement could be using inheritance with std::deques, streamlining the code to allow insertion and deletion at both the beginning and end.
