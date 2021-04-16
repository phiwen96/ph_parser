#pragma once
#include "common.hpp"
#include <boost/preprocessor/variadic/to_tuple.hpp>
#include <ph_vari/vari.hpp>
#include <ph_type/type.hpp>

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
    ph::factor_t <ph::minus_t, ph::number_t>, \
    ph::factor_t <ph::lparen_t, ph::expression_t, ph::rparen_t>, \
    ph::factor_t <ph::minus_t, ph::lparen_t, ph::expression_t, ph::rparen_t>, \
    ph::term_t <ph::factor_t <ph::number_t>>, \
    ph::term_t <ph::factor_t <ph::minus_t, ph::number_t>>, \
    ph::term_t <ph::factor_t <ph::lparen_t, ph::expression_t, ph::rparen_t>>, \
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
    X (factor_t <minus_t, number_t>) \
    X (factor_t <lparen_t, expression_t, rparen_t>) \
    X (factor_t <minus_t, lparen_t, expression_t, rparen_t>) \
    X (term_t <factor_t <number_t>>) \
    X (term_t <factor_t <minus_t, number_t>>) \
    X (term_t <factor_t <lparen_t, expression_t, rparen_t>>) \
    X (expression_t)

using number_t = double;

struct plus_t
{
    
};
constexpr plus_t plus {};
struct minus_t
{
    
};
constexpr minus_t minus {};
struct multi_t
{
    
};
constexpr multi_t multi {};
struct divi_t
{
    
};
constexpr divi_t divi {};
struct lparen_t
{
    
};
constexpr lparen_t lparen {};
struct rparen_t
{
    
};
constexpr rparen_t rparen {};

//template <typename...>
struct expression_t
{
    explicit expression_t () = default;
};

template <typename...>
struct factor_t;

template <typename...>
struct term_t;

template <>
struct factor_t <void>
{
    virtual void kiss () = 0;
};

template <>
struct factor_t <number_t> : factor_t <void>
{
    number_t m_number;
    factor_t () = default;
    template <typename Variant>
    factor_t (Variant&& vari) : m_number (forward <Variant> (vari))
    {
        
    }
    
    virtual void kiss ()
    {
        cout << "kiss" << endl;
    }
};

template <>
struct factor_t <minus_t, number_t> : factor_t <void>
{
    number_t m_number;
    factor_t () = default;
    
    
    template <typename... T>
    factor_t (var <T...> const& vari) : m_number (vari)
    {
        
    }
    factor_t (number_t&& number) : m_number {move (number)}
    {
        
    }
    factor_t (number_t const& number) : m_number {number}
    {
        
    }
    
    virtual void kiss ()
    {
        cout << "kiss" << endl;
    }
    
//    template <typename... T>
//    operator term_t <T...> () &&
//    {
//        return m_number;
//    }
};

template <>
struct factor_t <lparen_t, expression_t, rparen_t> : factor_t <void>
{
    number_t m_number;
    factor_t () = default;
    template <typename Variant>
    factor_t (Variant&& vari) : m_number (forward <Variant> (vari) * -1)
    {
        
    }
    virtual void kiss ()
    {
        cout << "kiss" << endl;
    }
};

template <>
struct factor_t <minus_t, lparen_t, expression_t, rparen_t> : factor_t <void>
{
    number_t m_number;
    
    factor_t () = default;
    
    template <typename Variant>
    factor_t (Variant&& vari) : m_number (get <number_t> (forward <Variant> (vari)) * -1)
    {
        
    }
    
    factor_t (factor_t&& other) : m_number {move (other.m_number)}
    {
        
    }
    
    factor_t (factor_t const& other) : m_number {other.m_number}
    {
        
    }
    
    factor_t& operator= (factor_t const& other)
    {
        m_number = other.m_number;
        return *this;
    }
    virtual void kiss ()
    {
        cout << "kiss" << endl;
    }
};

template <typename... T>
factor_t <T...> const factor {};

#define FACTORS \
factor_t <number_t>, \
factor_t <minus_t, number_t>, \
factor_t <lparen_t, expression_t, rparen_t>, \
factor_t <minus_t, lparen_t, expression_t, rparen_t>

//template <template <typename...> typename>
//struct term_t;



//template <>
//struct term_t <>//<factor_t>
//{
//    variant <
////    TOKENS
////    ph::number_t,
////    ph::plus_t,
////    ph::minus_t,
////    ph::multi_t,
////    ph::divi_t,
////    ph::lparen_t,
////    ph::rparen_t,
//    ph::factor_t <ph::number_t>,
//    ph::factor_t <ph::minus_t, ph::number_t>,
//    ph::factor_t <ph::lparen_t, ph::expression_t, ph::rparen_t>,
//    ph::factor_t <ph::minus_t, ph::lparen_t, ph::expression_t, ph::rparen_t>
////    ph::term_t,
////    ph::expression_t
//    > m_vari;
//
//
//
////    template <typename Variant>
////    term_t (Variant&& vari) : m_vari (forward <Variant> (vari))
////    {
////
////    }
//};



template <>
struct term_t <factor_t <number_t>>
{
    factor_t <number_t> m_vari;
    
//    term_t (auto&& v) : m_vari (forward <decltype (v)> (v))
//    {
//        cout << "tjo" << endl;
//    }
    
//    term_t () = default;
};

template <>
struct term_t <factor_t <minus_t, number_t>>
{
    factor_t <minus_t, number_t> m_vari;
    
    term_t (auto&& v) : m_vari (forward <decltype (v)> (v))
    {
        cout << "tjo" << endl;
    }
    
//    term_t () = default;
};

template <>
struct term_t <factor_t <lparen_t, expression_t, rparen_t>>
{
    using Factor = factor_t <lparen_t, expression_t, rparen_t>;
    Factor m_vari;
    
    term_t () = default;
//    term_t ()
};

//template <typename... T>





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










using Token = variant <TOKENS>;

#define X(...) \
    template <typename... T> \
    constexpr auto operator== (variant <T...> const& rhs, ph::__VA_ARGS__ const& lhs) -> bool\
    { \
    return visit (overload {[](ph::__VA_ARGS__ const& lhs){return true;}, [](auto const&){return false;}}, rhs); \
    }

    MY_LIST
#undef X

#define X(...) \
    ostream& operator<< (ostream& os, ph::__VA_ARGS__ const& n) \
    { \
        return os <<  #__VA_ARGS__; \
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


