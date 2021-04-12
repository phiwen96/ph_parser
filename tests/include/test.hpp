#include <catch2/catch.hpp>
#include <ph_parser/lexer.hpp>
#include <ph_parser/token.hpp>
#include <ph_parser/expression.hpp>
#include <ph_parser/parser.hpp>
#include <ph_type_list/type_list.hpp>
#include <variant>
#include <phany/phany.hpp>
using namespace std;
using namespace ph;





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



auto factorize () -> parser
{
//    cout << "factor..." << endl;
    
//    auto& token = co_await type_list <number_t, rparen_t>;
begin:
    {
        any& token = co_await type_list <TOKENS>;
        
        if (token.type () == typeid (number_t))
        {
//            co_return *t;
            co_return any_cast <number_t> (token);
            
        } else if (token.type () == typeid (minus_t))
        {
            cout << "minus" << endl;

            goto minus;
            
        } else if (token.type () == typeid (lparen_t))
        {
//            cout << "number" << endl;
            goto lparen;
        } else
        {
            cout << "WHAAAAAAT" << endl;
            co_return token;
        }
    }

minus:
    {
        auto& token = co_await type_list <number_t, lparen_t>;


        if (token.type () == typeid (number_t))
        {
//            cout << token << endl;
//            cout << "baaaa" << endl;
//            factor_t <minus_t, number_t> f {token};
//            factor_t <minus_t, number_t> f2 {move (f)};
//            f2 = move (f);
            co_return factor_t <minus_t, number_t> {any_cast <number_t> (token)};

        } else
        {
            goto minus_lparen;
        }
    }
    
lparen:
    {
        any& token = co_await type_list <expression_t>;
        goto lparen_expression;
    }
    
lparen_expression:
    {
        any& token = co_await type_list <rparen_t>;
        cout << "yaaaaaaaay" << endl;
    }

    
    
minus_lparen:
    {
        any& token = co_await type_list <expression_t>;
        goto minus_lparen_expression;
    }
    
minus_lparen_expression:
    {
        any& token = co_await type_list <expression_t>;
        cout << "yaaaaaaaay" << endl;
    }
    
    
    
    
//    cout << "...factor" << endl;
}

auto term () -> parser
{
//    cout << "term..." << endl;
begin:
    {
        
        any m_factor = co_await factorize ();
        
        if (auto* f = any_cast <factor_t <void>> (&m_factor))
        {
            f -> kiss ();
        } else
        {
            cout << ":(" << endl;
        }
    }
    co_return number_t {};
}

auto expression () -> parser
{
//    cout << "expression..." << endl;
    
    co_await term ();
//    cout << "...expression" << endl;
    co_return number_t {};
}

auto parse () -> parser
{
    for (;;)
    {
//        cout << "parse..." << endl;
        co_await expression();
//        auto& a = co_await get_top_from_stack;

    }
    co_return variant <TOKENS> {in_place_type_t<number_t>{}};
}









auto run () -> int
{
 
//    bool aa = typeid (int) == int{};
    
//    variant <TOKENS> v {number_t{}};
//    factor_t <minus_t, number_t> m_factor {v};
//    term_t <factor_t <minus_t, number_t>> m {m_factor};

    
//    return 0;
  
    
//    return;
//    vector <Token> tokens = lex ("-4*5+6-(7+8)/97");
    vector <any> tokens = lex ("-4*5+6-(7+8)/97");
//    vector <Token> tokens = lex ("-*f+-(--------/6+++++++");

//    parse2 (tokens);
    parser p = parse ();
    p.parse (tokens [0]);
    cout << "======================" << endl;

    p.parse (tokens [1]);
    cout << "======================" << endl;
    return 0;

    p.parse (tokens [2]);
    cout << "======================" << endl;

    p.parse (tokens [3]);
    cout << "======================" << endl;
    p.parse (tokens [4]);

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
    
    
    
    
    
//    variant <expression, term, factor, number> d {in_place_type <term>};
    
    
    
    
    
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

