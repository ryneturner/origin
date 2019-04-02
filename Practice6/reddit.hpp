#pragma once

#include "json.hpp"

#include <iostream>
#include <string>
#include <vector>

//Struct to print data tags
struct Data
{
    bool trueOrFalse = false;
    std::string title = "", author = "";
    
    Data(std::string Title, std::string Author, bool TrueOrFalse);
};

//Struct to remove unnecessary components and display titles/authors
struct Reddit
{
    std::string remove(std::string);
    std::vector<Data> data;
    
    void display();
    Reddit(json::Value *v);
};
