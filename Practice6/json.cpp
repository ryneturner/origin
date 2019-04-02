#include "json.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

namespace json
{
    bool is_eof(const char* first, const char* last)
    {
        return first == last;
    }
    
    bool is_punctuation(const char* first, const char* last)
    {
        if(is_eof(first, last))
            return false;
        
        switch(*first)
        {
            default:
                return false;
            case '[':
            case ']':
            case '{':
            case '}':
            case ':':
            case ',':
                return true;
        }
    }
    
    bool is_space(const char* first, const char* last)
    {
        if(is_eof(first, last))
            return false;
        
        return std::isspace(*first);
    }
    
    bool is_delimiter(const char* first, const char* last)
    {
        return is_eof(first, last) || is_space(first, last) || is_punctuation(first, last);
    }
    
    bool match_literal(const char*& first, const char* last, const char* word)
    {
        auto q = word;
        
        while(!is_eof(first, last) && *q != '\0' && *first == *q)
        {
            ++first;
            ++q;
        }
        
        if(*q !='\0')
            throw std::runtime_error("invalid literal");
        if(!is_delimiter(first, last))
            throw std::runtime_error("invalid literal");
        
        return true;
    }
    
    void skip_space(const char*& first, const char* last)
    {
        while(is_space(first, last))
            ++first;
    }
    
    struct space_guard
    {
        space_guard(const char*& f, const char* l) : first(f), last(l)
        {
            skip_space(first, last);
        }
        ~space_guard() { skip_space(first, last); }
        
        const char*& first;
        const char* last;
    };
    
    Value* parse_value(const char*& first, const char* last);
    
    Bool* parse_true(const char*& first, const char* last)
    {
        match_literal(first, last, "true");
        
        return new Bool(true);
    }
    
    Bool * parse_false(const char*& first, const char* last)
    {
        match_literal(first, last, "false");
        
        return new Bool(false);
    }
    
    Null* parse_null(const char*& first, const char* last)
    {
        match_literal(first, last, "null");
        
        return new Null();
    }
    
    String* parse_string(const char*& first, const char* last)
    {
        const char* start = first++;
        
        while(!is_eof(first, last) && *first != '"')
        {
            if(*first == '\\')
                ++first;
            
            ++first;
        }
        
        assert(*first == '"');
        ++first;
        
        return new String(start, first);
    }
    
    Number* parse_number(const char*& first, const char* last)
    {
        const char* start = first++;
        
        while(!is_eof(first, last) && !is_delimiter(first, last))
            ++first;
        
        std::string str(start, first);
        std::stringstream ss(str);
        double d;
        
        ss >> d;
        
        if(!ss)
            throw std::runtime_error("invalid number");
        
        return new Number(d);
    }
    
    Array* parse_array(const char*& first, const char* last)
    {
        Array* arr = new Array();
        
        ++first;
        space_guard g1(first, last);
        
        if(*first == ']')
        {
            ++first;
            
            return arr;
        }
        
        while(true)
        {
            Value* v = parse_value(first, last);
            arr->push_back(v);
            
            if(first == last)
                throw std::runtime_error("invalid array");
            if(*first == ',')
            {
                ++ first;
                
                continue;
            }
            if(*first == ']')
                break;
        }
        
        assert(*first == ']');
        ++first;
        
        return arr;
    }
    
    String* parse_key(const char*& first, const char* last)
    {
        space_guard g(first, last);
        
        return parse_string(first, last);
    }
    
    Object* parse_object(const char*& first, const char* last)
    {
        Object* obj = new Object();
        
        ++first;
        space_guard g1(first, last);
        
        if(*first == '}')
        {
            ++first;
            
            return obj;
        }
        
        while(true)
        {
            String* k = parse_key(first, last);
            
            if(first == last)
                throw std::runtime_error("invalid object");
            if(*first != ':')
                throw std::runtime_error("expected ':'");
            
            ++first;
            
            Value* v = parse_value(first, last);
            
            obj->emplace(*k, v);
            
            if(first == last)
                throw std::runtime_error("invalid array");
            if(*first == ',')
            {
                ++first;
                
                continue;
            }
            if(*first == '}')
                break;
        }
        
        assert(*first == '}');
        ++first;
        
        return obj;
    }
    
    Value* parse_value(const char*& first, const char* last)
    {
        if(is_eof(first, last))
            return nullptr;
        
        space_guard g(first, last);
        
        switch(*first)
        {
            case 't':
                return parse_true(first, last);
            case 'f':
                return parse_false(first, last);
            case 'n':
                return parse_null(first, last);
            case '"':
                return parse_string(first, last);
            case '[':
                return parse_array(first, last);
            case '{':
                return parse_object(first, last);
            case '0': case '1': case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9': case '-':
                return parse_number(first, last);
            default:
                throw std::runtime_error("invalid error");
        }
    }
    
    Value* parse(const std::string& str)
    {
        const char* first = str.c_str();
        const char* last = first + str.size();
        
        return parse_value(first, last);
    }
    
    struct SizeVisitor : Visitor
    {
        void visit(Null const& n) { ret = 1; }
        void visit(Bool const& b) { ret = 1; }
        void visit(Number const& n) { ret = 1; }
        void visit(String const& s) { ret = 1; }
        
        void visit(Array const& a)
        {
            int n = 1;
            
            for(Value* v : a)
                n += size(*v);
            
            ret = n;
        }
        
        void visit(Object const& o)
        {
            int n = 1;
            
            for(auto const& kv : o)
                n += size(*kv.second);
            
            ret = n;
        }
        
        int ret;
    };
    
    int size(Value const& v)
    {
#if 0
        switch virtual(v)
        {
        case Null const* n:
            return 1;
        case Bool const* b:
            return 1;
        case Number const* n:
            return 1;
        case String const* s:
            return 1;
        case Array const* a:
            return 1;
        case Object const* o:
            return 1;
        }
#endif
        
        SizeVisitor vis;
        v.accept(vis);
        
        return vis.ret;
    }
    
    int height(Value const& v)
    {
        struct V : Visitor
        {
            void visit(Null const& n) { ret = 0; }
            void visit(Bool const& b) { ret = 0; }
            void visit(Number const& n) { ret = 0; }
            void visit(String const& s) { ret = 0; }
            
            void visit(Array const& a)
            {
                if(a.empty())
                {
                    ret = 0;
                    
                    return;
                }
                
                auto iter = std::max_element(a.begin(), a.end(), [](Value const* a, Value const* b)
                                             {
                                                 return height(*a) < height(*b);
                                             });
                
                ret = 1 + height(**iter);
            }
            
            void visit(Object const& o)
            {
                if(o.empty())
                {
                    ret = 0;
                    
                    return;
                }
                
                auto iter = std::max_element(o.begin(), o.end(), [](Object::value_type const& a, Object::value_type const& b)
                                             {
                                                 return height(*a.second) < height(*b.second);
                                             });
                
                Value *v = iter->second;
                ret = 1 + height(*v);
            }
            
            int ret;
        };
        
        V vis;
        v.accept(vis);
        
        return vis.ret;
    }
}

