#include <catch2/catch.hpp>
#include <ph_parser/lexer.hpp>
#include <ph_parser/token.hpp>
#include <ph_parser/expression.hpp>
#include <ph_parser/parser.hpp>
#include <ph_type_list/type_list.hpp>
#include <variant>
#include <ph_time/timer.hpp>
#include <ph_macros/macros.hpp>
#include <ph_vari/vari.hpp>
#include <ph_type/type.hpp>
//#include <phany/phany.hpp>
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






auto factorize () -> parser
{
//    cout << "factor..." << endl;
    
//    auto& token = co_await type_list <number_t, rparen_t>;
begin:
    {
        auto& token = co_await type_list <TOKENS>;
        
        if (token == type <number_t>)
        {
//            co_return *t;
            co_return token;
            
        } else if (token == type <minus_t>)
        {
            cout << "minus" << endl;

            goto minus;
            
        } else if (token == type <lparen_t>)
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


        if (token == type <number_t>)
        {
//            cout << token << endl;
//            cout << "baaaa" << endl;
//            factor_t <minus_t, number_t> f {token};
//            factor_t <minus_t, number_t> f2 {move (f)};
//            f2 = move (f);
            co_return factor_t <minus_t, number_t> {token};

        } else
        {
            goto minus_lparen;
        }
    }
    
lparen:
    {
        auto& token = co_await type_list <expression_t>;
        goto lparen_expression;
    }
    
lparen_expression:
    {
        auto& token = co_await type_list <rparen_t>;
        cout << "yaaaaaaaay" << endl;
    }

    
    
minus_lparen:
    {
        auto& token = co_await type_list <expression_t>;
        goto minus_lparen_expression;
    }
    
minus_lparen_expression:
    {
        auto& token = co_await type_list <expression_t>;
        cout << "yaaaaaaaay" << endl;
    }
    
    
    
    
//    cout << "...factor" << endl;
}

auto term () -> parser
{
//    cout << "term..." << endl;
begin:
    {
        
        auto m_factor = co_await factorize ();
    
        if (m_factor == type <factor_t <number_t>>)
        {
            
        } else if (m_factor == type <factor_t <minus_t, number_t>>)
        {
        } else if (m_factor == type <factor_t <lparen_t, expression_t, rparen_t>>)
        {
        } else if (m_factor == type <factor_t <minus_t, lparen_t, expression_t, rparen_t>>)
        {
        }
        
        else
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
    co_return number_t{};
//    co_return var <TOKENS> {in_place_type_t<number_t>{}};
}



struct A
{
    A (){cout << "A ()" << endl;}
    ~A (){cout << "~A ()" << endl;}

};

struct B
{
    B (){cout << "B ()" << endl;}
    ~B (){cout << "~B ()" << endl;}
};

struct C
{
    C (){cout << "C ()" << endl;}
    ~C (){cout << "~C ()" << endl;}
};









//template <typename T>
//struct var <T>
//{
//    vari <T> value;
//
//};






//template <typename T, typename... U>
//union variable
//{
//    vari <T, U...> _value;
//};

//template <typename... T>
//requires requires ()
//{
//    requires (sizeof... (T) > 0);
////    requires ((is_assignable_v<U, P> || ...));
//}
//using var = vari <0, T...>;





auto run () -> int
{
    
    
    
//    var <A, B, C> k;
//    k = A{};
//    k = C{};
//    cout << "==============" << endl;

//    k = B {};
//    cout << "==============" << endl;
//    return 0;
    
//    bool aa = typeid (int) == int{};
    
//    variant <TOKENS> v {number_t{}};
//    factor_t <minus_t, number_t> m_factor {v};
//    term_t <factor_t <minus_t, number_t>> m {m_factor};

    
//    return 0;
  
    
//    return;
//    vector <Token> tokens = lex ("-4*5+6-(7+8)/97");
    vector <var <TOKENS>> tokens = lex <var <TOKENS>>  ("-4*5+6-(7+8)/97");
//    vector <Token> tokens = lex ("-*f+-(--------/6+++++++");
//    return 0;
    
//    for (auto const& v : tokens)
//        cout << v << endl;
//    parse2 (tokens);
    parser p = parse ();
    p.parse (tokens [0]);
    cout << "======================" << endl;
//
    p.parse (tokens [1]);
    cout << "======================" << endl;
    return 0;
//
//    p.parse (tokens [2]);
//    cout << "======================" << endl;
//
//    p.parse (tokens [3]);
//    cout << "======================" << endl;
//    p.parse (tokens [4]);
//
//    return 0;
//    for (auto const& token : tokens)
//    {
//        p.parse (token);
//
//    }
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

