#include <catch2/catch.hpp>
#include <ph_parser/lexer.hpp>
#include <ph_parser/token.hpp>
#include <ph_parser/expression.hpp>
#include <ph_parser/parser.hpp>
#include <ph_type_list/type_list.hpp>
#include <variant>
using namespace std;




/**
            
 
 
      +            *
1            5           +
                    2        1
 
    
     +
1             *          +
        5           2         1
 

 */

int loops {0};

//parser parse ()
//{
//    int m_loop = loops;
//    ++loops;
//
//    begin:
//
//
//
//    has_lhs:
//    co_return 3;
//}



void parse2 (vector <variant <TOKENS>> const& tokens)
{
    for (auto const& token : tokens)
    {
        cout << token << endl;
    }
}



auto factor () -> parser
{
    cout << "factor..." << endl;
    
//    auto& token = co_await type_list <ph::number_t, ph::rparen_t>;
begin:
    {
        auto& token = co_await type_list <ph::number_t, ph::minus_t, ph::lparen_t>;
        
        if (token == ph::number_t {})
        {
            co_return token;
            
        } else if (token == ph::minus_t {})
        {
//            cout << "minus" << endl;

            goto minus;
            
        } else
        {
//            cout << "number" << endl;
            goto lparen;
        }
    }

minus:
    {
        auto& token = co_await type_list <ph::number_t, ph::lparen_t>;


        if (token == ph::number_t {})
        {
            cout << token << endl;
            co_return ph::factor_t <ph::minus_t, ph::number_t> {token};

        } else
        {
            goto minus_lparen;
        }
    }
    
lparen:
    {
        auto& token = co_await type_list <ph::expression_t>;
        goto lparen_expression;
    }
    
lparen_expression:
    {
        auto& token = co_await type_list <ph::rparen_t>;
        cout << "yaaaaaaaay" << endl;
    }

    
    
minus_lparen:
    {
        auto& token = co_await type_list <ph::expression_t>;
        goto minus_lparen_expression;
    }
    
minus_lparen_expression:
    {
        auto& token = co_await type_list <ph::expression_t>;
        cout << "yaaaaaaaay" << endl;
    }
    
    
    
    
    cout << "...factor" << endl;
}

auto term () -> parser
{
    cout << "term..." << endl;

    auto& m_factor = co_await factor ();
    auto& token = co_await type_list <TOKENS>;
    cout << m_factor << endl;
    cout << token << endl;
    cout << "...term" << endl;
    co_return ph::number_t {};
}

auto expression () -> parser
{
//    cout << "expression..." << endl;
    
    co_await term ();
//    cout << "...expression" << endl;
    co_return ph::number_t {};
}

auto parse () -> parser
{
    for (;;)
    {
        cout << "parse..." << endl;
        co_await expression();
//        auto& a = co_await get_top_from_stack;

    }
    co_return variant <TOKENS> {in_place_type_t<ph::number_t>{}};
}









auto run () -> int
{

    
    
    
  
    
//    return;
//    vector <ph::Token> tokens = lex ("-4*5+6-(7+8)/97");
    vector <ph::Token> tokens = lex ("-4*5+6-(7+8)/97");
//    vector <ph::Token> tokens = lex ("-*f+-(--------/6+++++++");

//    parse2 (tokens);
    parser p = parse ();
    p.parse (tokens [0]);
    p.parse (tokens [1]);
    p.parse (tokens [2]);
    p.parse (tokens [3]);
    cout << "======================" << endl;
   
    return 0;
    for (auto const& token : tokens)
    {
        p.parse (token);

    }
    return 0;
    
    
//    vector <token> tokens = lex ("1+2+3+7+4");
//    []{
//        vector <token> tokens = lex ("1+5+1");
//        parser p = loop ();
//
//    //    p.resume ();
//        for (auto const& i : tokens)
//            p.parse (i);
//
//        expression * res = p.get_value();
//        assert (res->eval() == 7);
//    }();
//
//    []{
//        vector <token> tokens = lex ("-5-5");
//        parser p = loop ();
//
//    //    p.resume ();
//        for (auto const& i : tokens)
//            p.parse (i);
//
//        expression * res = p.get_value();
//        assert(res->eval() == -10);
//    }();
//
//    []{
//        vector <token> tokens = lex ("1+5+2*2");
//        parser p = loop ();
//
//    //    p.resume ();
//        for (auto const& i : tokens)
//            p.parse (i);
//
//        expression * res = p.get_value();
//        assert(res->eval() == 10);
//    }();
//
//    []{
//        vector <token> tokens = lex ("1+5*2+1");
//        parser p = loop ();
//
//    //    p.resume ();
//        for (auto const& i : tokens)
//            p.parse (i);
//
//        expression * res = p.get_value();
//        cout << res->eval() << endl;
////        assert(res->eval() == 12);
//    };
    
//    vector <token> tokens__ = lex ("-4*5+6-(7+8)/97");
    
    
//    if (auto* a = get_if<int>(&d))
//        cout << "tjo" << endl;
    
    
    
    
    
//    variant <ph::expression, ph::term, ph::factor, ph::number> d {in_place_type <ph::term>};
    
    
    
    
    
//        cout << i << endl;
    
    
//    auto* root = new binary_expression;
//    root -> m_lhs = new number {0};
//    root -> m_type = binary_expression::add;
//    int i {0};
//    auto* tree = parse (tokens, root, i);
//
//    cout << tree -> eval() << endl;
    cout << endl;
}

