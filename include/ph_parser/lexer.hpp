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
                    result.push_back (token {token::type::number, num.m_number});
                    num.m_power = 0;
                    num.m_number.clear ();
                }
            }
            
            if (c == '+')
            {
                result.push_back (token {token::type::plus, "+"});
            }
            else if (c == '-')
            {
                result.push_back (token {token::type::minus, "-"});
            }
            else if (c == '(')
            {
                result.push_back (token {token::type::lparen, "("});
            }
            else if (c == ')')
            {
                result.push_back (token {token::type::rparen, "+"});
            }
        }
    }
    
    if (num.m_power > 0)
    {
        result.push_back (token {token::type::number, num.m_number});
    }
    
    return result;
}
