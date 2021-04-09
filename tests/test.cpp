#include <catch2/catch.hpp>
#include <ph_parser/lexer.hpp>
#include <ph_parser/token.hpp>
#include <ph_parser/expression.hpp>
#include <ph_parser/parser.hpp>
using namespace std;




/**
            
 
 
        +
                +
1            2       3
 */

int loops {0};

parser loop ()
{
    int m_loop = loops;
    ++loops;
    


    begin:
    {
        for (;;)
        {
            cout << m_loop << "::" << "begin..." << endl;
            token& tok = co_await (int[]) {token::type::number};
            cout << m_loop << "::" << tok << endl;
            cout << m_loop << "::" << "...begin" << endl;

            goto has_lhs;
        }
    }
    
    
    has_lhs:
    {
        for (;;)
        {
            cout << m_loop << "::" << "has_lhs..." << endl;

            token& tok = co_await (int[]) {token::type::plus, token::type::minus, token::type::mult, token::type::div};
            co_await loop ();
            cout << m_loop << "::" << "...begin" << endl;

//            cout << "hi" << endl;
        }
    }
}

TEST_CASE ("hej")
{
    
//    vector <token> tokens = lex ("1+2+3+7+4");
    vector <token> tokens = lex ("1+7+");
    parser p = loop ();
//    p.resume ();
    for (auto const& i : tokens)
        p.parse (i);
//        cout << i << endl;
    
    
//    auto* root = new binary_expression;
//    root -> m_lhs = new number {0};
//    root -> m_type = binary_expression::add;
//    int i {0};
//    auto* tree = parse (tokens, root, i);
//
//    cout << tree -> eval() << endl;
    
}
