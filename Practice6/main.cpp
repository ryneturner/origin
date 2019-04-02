//Practice 6:    JSON Input from Reddit
//Created by:    Ryne Turner

#include "json.hpp"
#include "reddit.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <typeinfo>

int main()
{
    std::istreambuf_iterator<char> first(std::cin);
    std::istreambuf_iterator<char> last;
    std::string s(first, last);
    
    json::Value* sub = json::parse(s);
    
    Reddit reddit(sub);
    reddit.display();
    
    return 0;
}
