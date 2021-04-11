#pragma once
#include "common.hpp"
#include <boost/preprocessor/variadic/to_tuple.hpp>

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


namespace ph {

struct exp
{
//    virtual double eval () = 0;
    exp () = default;
};
#define TOKENS \
    ph::number_t, \
    ph::plus_t, \
    ph::minus_t, \
    ph::multi_t, \
    ph::divi_t, \
    ph::lparen_t, \
    ph::rparen_t, \
    ph::factor_t <ph::number_t>, \
    ph::term_t, \
    ph::expression_t

#define MY_LIST \
    X (number_t) \
    X (plus_t) \
    X (minus_t) \
    X (multi_t) \
    X (divi_t) \
    X (lparen_t) \
    X (rparen_t) \
    X (factor_t <number_t>) \
    X (term_t) \
    X (expression_t)

using number_t = double;

struct plus_t
{
    
};
struct minus_t
{
    
};
struct multi_t
{
    
};
struct divi_t
{
    
};
struct lparen_t
{
    
};
struct rparen_t
{
    
};

//template <typename...>
struct expression_t
{
    explicit expression_t () = default;
};

template <typename...>
struct factor_t;

template <>
struct factor_t <number_t>
{
    number_t m_number;
    
    template <typename Variant>
    factor_t (Variant&& vari) : m_number (get <number_t> (forward <Variant> (vari)))
    {
        
    }
};

template <>
struct factor_t <minus_t, number_t>
{
    number_t m_number;
    
    template <typename Variant>
    factor_t (Variant&& vari) : m_number (get <number_t> (forward <Variant> (vari)) * -1)
    {
        
    }
};


struct term_t
{
    explicit term_t () = default;
};




/**
  1  <expression> ::= <term>
  2                |  <expression> '+' <term>
  3                |  <expression> '-' <term>
  4  <term> ::= <factor>
  5          |  <term> '*' <factor>
  6          |  <term> '/' <factor>
  7  <factor> ::= <number>
  8            |  '-' <number>
  9            |  '(' <expression> ')'
 10            |  '-' '(' <expression> ')'
 
 
  1  <expression> ::= <term>
  2                |  <expression>  <plus>  <term>
  3                |  <expression>  <minus>  <term>
 
  4  <term>       ::= <factor>
  5                |  <term>  <multi>  <factor>
  6                |  <term>  <divi>  <factor>
 
  7  <factor>     ::= <number>
  8                |  <minus>  <number>
  9                |  <lparen>  <expression>  <rparen>
 10                |  <minus>  <lparen>  <expression>  <rparen>
 
 -4*5+6-(7+8)/97
 
<minus> <number> <multi> <number> <plus> <number> <minus> <lparen> <number> <plus> <number> <rparen> <divi> <number>
 
 
 
 */


template <int...>
struct production_rules;

template <>
struct production_rules <>
{
    bool accept ()
    {
        return false;
    }
};

template <>
struct production_rules <1>
{
    
};
template <>
struct production_rules <2>
{
    
};
template <>
struct production_rules <3>
{
    
};
template <>
struct production_rules <4>
{
    
};
template <>
struct production_rules <5>
{
    
};
template <>
struct production_rules <6>
{
    
};
template <>
struct production_rules <7>
{
        
};
template <>
struct production_rules <8>
{
    
};
template <>
struct production_rules <9>
{
    
};
template <>
struct production_rules <10>
{
    bool accept ()
    {
        
    }
};





using Token = variant <TOKENS>;

#define X(x) \
    template <typename... T> \
    constexpr auto operator== (variant <T...> const& rhs, ph::x const& lhs) -> bool\
    { \
    return visit (overload {[](ph::x const& lhs){return true;}, [](auto const&){return false;}}, rhs); \
    }

    MY_LIST
#undef X

#define X(x) \
    ostream& operator<< (ostream& os, ph::x const& n) \
    { \
        return os << BOOST_PP_STRINGIZE (x); \
    }

    MY_LIST
#undef X

#define get_token(x) \
[](auto&& tokens) -> decltype (auto)\
{ \
    return visit ([](auto&& t) -> decltype (auto) {return forward <decltype (t)> (t);}, forward <decltype (tokens)> (tokens)); \
}(x)





//#define X(x, ext) \
//    ph::x##ext const x {};
//
//    MY_LIST
//#undef X

//constexpr number_t number {};
//constexpr factor_t factor {};
//constexpr term_t term {};
//constexpr expression_t expression {};


}

//using Token = variant <ph::number,
//                       ph::plus_t,
//                       ph::minus_t,
//                       ph::multi_t,
//                       ph::divi_t,
//                       ph::lparen_t,
//                       ph::rparen_t>;

//#define PRIMITIVE_TOKENS ph::number_t, \
//ph::plus_t, \
//ph::minus_t, \
//ph::multi_t, \
//ph::divi_t, \
//ph::lparen_t, \
//ph::rparen_t
//
//#define ADVANCED_TOKENS ph::factor_t, \
//ph::term_t, \
//ph::expression_t
//
//#define TOKENS PRIMITIVE_TOKENS, \
//ADVANCED_TOKENS





template <typename T, typename... U>
ostream& operator<< (ostream& os, variant <T, U...> const& v)
{
    visit ([&os]<typename V>(V const& t){os<<t;}, v);
    return os;
}


