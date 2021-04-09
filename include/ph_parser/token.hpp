#pragma once
using namespace std;



struct token
{
    enum type
    {
        number,
        plus,
        minus,
        mult,
        div,
        lparen,
        rparen
    };
    
    friend ostream& operator<< (ostream& os, token const& t)
    {
        return os << "token: " << t.m_text;
    }
    
    type m_type;
    string m_text;
};
