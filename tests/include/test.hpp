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
    
    auto& token = co_await type_list <ph::number_t, ph::rparen_t>;
    
    if (token == ph::number_t {})
    {
        cout << "number" << token << endl;
    } else if (token == ph::rparen_t {})
    {
        cout << "rparen" << endl;
    }
    
    auto& a = co_await get_token;
    
    cout << "...factor" << endl;
    co_return 2;

}

auto term () -> parser
{
    cout << "term..." << endl;

    co_await factor ();
    cout << "...term" << endl;
    co_return 2;
}

auto expression () -> parser
{
    cout << "expression..." << endl;
    
    co_await term ();
    cout << "...expression" << endl;
    co_return 2;
}

auto parse () -> parser
{
    for (;;)
    {
        cout << "parse..." << endl;
        co_await expression();
//        auto& a = co_await get_top_from_stack;

    }
    co_return 2;
}









auto run () -> int
{

    
    
    
  
    
//    return;
//    vector <ph::Token> tokens = lex ("-4*5+6-(7+8)/97");
//    vector <ph::Token> tokens = lex ("-4*5+6-(7+8)/97");
    vector <ph::Token> tokens = lex ("-*f+-(--------/6+++++++");

//    parse2 (tokens);
    parser p = parse ();
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

