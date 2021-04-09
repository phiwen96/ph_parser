#pragma once
#include "token.hpp"
#include "expression.hpp"
using namespace std;




auto parse (vector <token> const& tokens) -> expression *
{
    bool have_lhs {false};
    
    for (auto& tok : tokens)
    {
        auto oper = tok.m_type;
        
        if (oper == token::number)
        {
            double num = stod (tok.m_text);
        }
    }
}
