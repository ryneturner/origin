#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace json
{
    struct Value;
    struct Null;
    struct Bool;
    struct Number;
    struct String;
    struct Array;
    struct Object;
    
    struct Visitor
    {
        virtual void visit(Null const& n) { }
        virtual void visit(Bool const& b) { }
        virtual void visit(Number const& n) { }
        virtual void visit(String const& s) { }
        virtual void visit(Array const& a) { }
        virtual void visit(Object const& o) { }
    };
    
    int size(Value const& v);
    int height(Value const& v);
    
    struct Value
    {
        virtual ~Value() = default;
        virtual void accept(Visitor& vis) const = 0;
        
        virtual Value* direct(std::string str) const
        {
            Value* val;
            
            return val;
        }
        
        virtual Value* index(int index)
        {
            Value* val;
            
            return val;
        }
        
        //Must be able to point to getString()
        //There is a compiler error if this is not included
        virtual std::string getString() const
        {
            return "";
        }
        
        virtual bool getBool() const
        {
            return false;
        }
    };
    
    struct Null : Value
    {
        void accept(Visitor& vis) const
        {
            return vis.visit(*this);
        }
    };
    
    struct Bool : Value
    {
        Bool(bool b) : value(b) { }
        void accept(Visitor& vis) const
        {
            return vis.visit(*this);
        }
        
        bool value;
        
        bool getBool()
        {
            return value;
        }
    };
    
    struct Number : Value
    {
        Number(double n) : value(n) { }
        
        void accept(Visitor& vis) const
        {
            return vis.visit(*this);
        }
        
        double value;
    };
    
    struct String : Value, std::string
    {
        void accept(Visitor& vis) const
        {
            return vis.visit(*this);
        }
        
        using std::string::string;
        
        std::string getString() const
        {
            return *this;
        }
    };
    
    struct Array : Value, std::vector<Value*>
    {
        using std::vector<Value*>::vector;
        
        void accept(Visitor& vis) const
        {
            return vis.visit(*this);
        }
        
        Value* index(int index)
        {
            std::vector<Value*>::iterator counter = begin() + index;
            
            return *counter;
        }
    };
    
    struct Object : Value, std::unordered_map<std::string, Value*>
    {
        using std::unordered_map<std::string, Value*>::unordered_map;
        
        void accept(Visitor& vis) const override
        {
            return vis.visit(*this);
        }
        
        Value* direct(std::string str) const override
        {
            for(auto ptr = begin(); ptr != end(); ++ptr)
                if(ptr->first == str)
                    return ptr->second;
            
            return 0;
        }
    };
    
    Value* parse(std::string const& str);
}

