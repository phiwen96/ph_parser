#pragma once
#include "token.hpp"
#include "expression.hpp"
#include <ph_coroutines/co_promise.hpp>
#include <ph_coroutines/i_was_co_awaited_and_now_i_am_suspending.hpp>
#include <experimental/coroutine>
#include <ph_vari/vari.hpp>
#include <ph_type/type.hpp>
using namespace std;
using namespace experimental;



//struct lexer
//{
//    using value_type = ph::expression_t*;
//    using initial_suspend_awaitable_type = suspend_never;
//    using final_suspend_awaitable_type = i_was_co_awaited_and_now_i_am_suspending;
//
//
//
//    struct promise_type : co_promise <lexer>
//    {
//
//        operator coroutine_handle <promise_type> ()
//        {
//            return coroutine_handle <promise_type>::from_promise (*this);
//        }
//
//        token::type m_looking_for_token;
//        token m_found_token;
//        function <bool(int)> m_ok;
//        promise_type* m_current = this;
//        promise_type* m_parent {nullptr};
//
////        binary_expression* m_value {new binary_expression {binary_expression::number}};
////        expression* m_rhs;
//
////        auto yield_value (expression* lhs)
////        {
////            m_lhs = lhs;
////            return suspend_never {};
////        }
//
//        auto yield_value (struct value* value)
//        {
//            m_value -> m_lhs = value;
//            return suspend_never {};
//        }
//        auto yield_value (binary_expression::type t)
//        {
//            m_value -> m_type = t;
//            return suspend_never {};
//        }
////        auto yield_value (struct binary_expression* exp)
////        {
////            exp -> m_lhs = m_value;
////            m_value = exp;
////
////            return suspend_never {};
////        }
//
//        auto final_suspend () noexcept
//        {
//
//            struct i_was_co_awaited
//            {
//                auto await_ready () noexcept -> bool
//                {
//                    return false;
//                }
//
//                /**
//                 @param my_handle is a handle to this function
//
//                 @return a handle to the function that co_awaited us.
//                 */
//
//                auto await_suspend (coroutine_handle <promise_type> my_handle) noexcept -> coroutine_handle <>
//                {
//                    if (my_handle.promise().m_this_function_co_awaited_me)
//                    {
//                        my_handle.promise().m_parent -> m_current = &my_handle.promise();
//
//                    }
//
//                    auto& parent = my_handle.promise().m_this_function_co_awaited_me;
//
//                    return parent ? parent : noop_coroutine ();
//                }
//
//                auto await_resume () noexcept
//                {
//
//                }
//            };
//            return i_was_co_awaited {};
//        }
//
//        template <int N>
//        auto await_transform (int const(&a)[N])
//        {
//            m_ok = [a](int i) {
//                for (auto j : a)
//                {
//                    if (i == j)
//                    {
//                        return true;
//                    }
//                }
//                return false;
//            };
//
//            struct awaitable
//            {
//                promise_type& m_promise;
//
//                auto await_ready ()
//                {
//                    return false;
//                }
//
//                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
//                {
//                    m_promise.m_this_function_co_awaited_me = co_awaited_me;
//                    return true;
//                }
//
//                auto await_resume () -> token&
//                {
//                    return m_promise.m_found_token;
//                }
//            };
//            return awaitable {*this};
//        }
//
//
//        auto await_transform (lexer co_awaited)
//        {
//            co_awaited.m_promise.m_parent = this;
//            m_current = &co_awaited.m_promise;
//            m_value -> m_rhs = co_awaited.m_promise.m_value;
//
//            struct awaitable
//            {
//                promise_type& m_promise;
//                coroutine_handle<promise_type> m_handle = coroutine_handle<promise_type>::from_promise(m_promise);
//                auto await_ready ()
//                {
////                    return false;
////                    return m_handle.done();
//                    return false;
//                }
//
//                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
//                {
//                    m_promise.m_this_function_co_awaited_me = co_awaited_me;
////                    return true;
////                    return m_handle;
//                    return true;
//                }
//
//                auto await_resume () //-> token&
//                {
////                    return m_promise.m_found_token;
//                    return m_handle.resume();
//                    cout << "tjo" << endl;
////                    return coroutine_handle<promise_type>::from_promise(m_promise);
////                    return m_handle;
//                }
//            };
//            return awaitable {co_awaited.m_promise};
//        }
//
//        void lex (token const& t)
//        {
//            if (m_current == this)
//            {
//                if (m_ok (t.m_type))
//                {
//        //            cout << "OK" << endl;
//                    m_found_token = t;
//                    coroutine_handle <promise_type>::from_promise (*m_current).resume ();
//                } else
//                {
//        //            cout << "NOT OK" << endl;
//                }
//
//            } else
//            {
//                m_current->lex (t);
//            }
//
//
//        }
//    };
//
//
//    void lex (token const& t)
//    {
//        m_promise.lex (t);
////        if (m_promise.m_ok (t.m_type))
////        {
//////            cout << "OK" << endl;
////            m_promise.m_found_token = t;
////            static_cast <coroutine_handle<promise_type>>(m_promise).resume ();
////        } else
////        {
//////            cout << "NOT OK" << endl;
////        }
//    }
//
//
//    auto get_value () -> ph::expression_t*
//    {
//        return m_promise.m_value;
//    }
//    auto resume ()
//    {
//        return coroutine_handle <promise_type>::from_promise (m_promise).resume ();
//    }
//    lexer (promise_type& p) : m_promise {p}
//    {
//
//    }
//    lexer (lexer&& other) : m_promise {other.m_promise}
//    {
//
//    }
//    lexer (lexer const&) = delete;
//    lexer& operator=(lexer const&) = delete;
//    lexer& operator=(lexer&&) = delete;
////    coroutine_handle <promise_type> m_coro;
//    promise_type& m_promise;
//
//};

template <typename T>
auto lex (string const& input) -> vector <T>;

//#ifdef EAD
template <>
auto lex (string const& input) -> vector <var <TOKENS>>
{
    vector <var <TOKENS>> result;
    
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
                    result.push_back (var <TOKENS> {ph::number_t {stod (num.m_number)}});
//                    cout << "mf" << endl;
                    num.m_power = 0;
                    num.m_number.clear ();
                }
            }
            
            if (c == '+')
            {
                result.push_back (var <TOKENS> {ph::plus_t{}});
            }
            else if (c == '-')
            {
                result.push_back (var <TOKENS> {ph::minus_t{}});
            }
            else if (c == '*')
            {
                result.push_back (var <TOKENS> {ph::multi_t{}});
            }
            else if (c == '/')
            {
                result.push_back (var <TOKENS> {ph::divi_t{}});
            }
            else if (c == '(')
            {
                result.push_back (var <TOKENS> {ph::lparen_t{}});
            }
            else if (c == ')')
            {
                result.push_back (var <TOKENS> {ph::rparen_t{}});
            }
        }
    }
    
    if (num.m_power > 0)
    {
        result.push_back (var <TOKENS> {ph::number_t {stod (num.m_number)}});
    }
    
    for (auto& i : result)
        cout << i << endl;
    
    return result;
}
//#endif

template <>
auto lex (string const& input) -> vector <any>
{
    vector <any> result;
    
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
                    result.push_back (ph::number_t {stod (num.m_number)});
                    num.m_power = 0;
                    num.m_number.clear ();
                }
            }
            
            if (c == '+')
            {
                result.push_back (ph::plus_t{});
            }
            else if (c == '-')
            {
                result.emplace_back (ph::minus_t{});
            }
            else if (c == '*')
            {
                result.emplace_back (ph::multi_t{});
            }
            else if (c == '/')
            {
                result.emplace_back (ph::divi_t{});
            }
            else if (c == '(')
            {
                result.emplace_back (ph::lparen_t{});
            }
            else if (c == ')')
            {
                result.emplace_back (ph::rparen_t{});
            }
        }
    }
    
    if (num.m_power > 0)
    {
        result.emplace_back (ph::number_t {stod (num.m_number)});
    }
    
    return result;
}


auto lex_oldie (string const& input) -> vector <ph::Token>
{
    vector <ph::Token> result;
    
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
                    result.push_back (ph::number_t {stod (num.m_number)});
                    num.m_power = 0;
                    num.m_number.clear ();
                }
            }
            
            if (c == '+')
            {
                result.push_back (ph::plus_t{});
            }
            else if (c == '-')
            {
                result.emplace_back (ph::minus_t{});
            }
            else if (c == '*')
            {
                result.emplace_back (ph::multi_t{});
            }
            else if (c == '/')
            {
                result.emplace_back (ph::divi_t{});
            }
            else if (c == '(')
            {
                result.emplace_back (ph::lparen_t{});
            }
            else if (c == ')')
            {
                result.emplace_back (ph::rparen_t{});
            }
        }
    }
    
    if (num.m_power > 0)
    {
        result.emplace_back (ph::number_t {stod (num.m_number)});
    }
    
    return result;
}




