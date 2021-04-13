#pragma once
using namespace std;

namespace tok {
struct token
{
    enum class type
    {
        number,
        plus,
        minus,
        multi,
        divi,
        lparen,
        rparen
    };
    
    
    
};
struct number
{
    double _value;
};

struct plus
{
    
};

struct minus
{
    
};

struct multi
{
    
};

struct divi
{
    
};

struct lparen
{
    
};

struct rparen
{
    
};
}

namespace exp
{
struct e
{
    virtual auto eval () -> void = 0;
};

template <typename...>
struct factor;

//template <
//struct factor : e
//{
//    virtual auto eval () -> void override
//    {
//
//    }
//};
}




