#pragma once
#include "token.hpp"
using namespace std;


auto lex (string const& input) -> vector <token>
{
    vector <token> result;
    struct Num
    {
        int m_power {0};
        string m_number;
    } num;
    
    for (auto c : input)
    {
        if (isdigit (c))
        {
            num.m_number += c;
            ++num.m_power;
        }
        else
        {
            if (num.m_power > 0)
            {
                if (c == '.')
                {
                    num.m_number += c;
                    continue;
                }
                else
                {
                    result.push_back (token {token::number, num.m_number});
                    num.m_power = 0;
                    num.m_number.clear ();
                }
            }
            
            if (c == '+')
            {
                result.push_back (token {token::plus, "+"});
            }
            else if (c == '-')
            {
                result.push_back (token {token::minus, "-"});
            }
            else if (c == '(')
            {
                result.push_back (token {token::lparen, "("});
            }
            else if (c == ')')
            {
                result.push_back (token {token::rparen, "+"});
            }
        }
    }
    
    if (num.m_power > 0)
    {
        result.push_back (token {token::number, num.m_number});
    }
    
    return result;
}
