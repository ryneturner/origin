#include "reddit.hpp"

#include <iostream>
#include <string>

//Precondition:     This function takes in the title, author, and boolean component of the data.
//Postcondition:    This function simply sets the parameters equal to the Struct variables.
Data::Data(std::string Title, std::string Author, bool TrueOrFalse)
{
    title = Title;
    author = Author;
    trueOrFalse = TrueOrFalse;
}

//Precondition:     This function takes in no parameters.
//Postcondition:    This function prints out the necessary data read from the input.
void Reddit::display()
{
    for(long counter = data.size() - 1; counter > 0; --counter)
    {
        Data d = data.at(counter);
        std::cout << "Title:  " << d.title << std::endl << "Author: " << d.author << std::endl;
    }
}

//Precondition:     This function takes in a string variable.
//Postcondition:    This function returns the string variable after parsing.
std::string Reddit::remove(std::string str)
{
    str.pop_back();
    str.erase(str.begin());
    
    return str;
}

//Precondition:     This function takes in a json::Value* variable.
//Postcondition:    This function creates the strings of the title, author, and boolean component.
Reddit::Reddit(json::Value* v)
{
    int counter = 0;
    
    while(v->direct("\"data\"")->direct("\"children\"")->index(counter) != nullptr)
    {
        std::string title = remove(v->direct("\"data\"")->direct("\"children\"")->index(counter)->direct("\"data\"")->direct("\"title\"")->getString());
        std::string author = remove(v->direct("\"data\"")->direct("\"children\"")->index(counter)->direct("\"data\"")->direct("\"author\"")->getString());
        bool t = v->direct("\"data\"")->direct("\"children\"")->index(counter)->direct("\"data\"")->direct("\"stickied\"")->getBool();
        
        Data displayData(title, author, t);
        data.insert(data.begin(), displayData);
        
        ++counter;
    }
}
