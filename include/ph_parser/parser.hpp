#pragma once
#include "token.hpp"
#include "expression.hpp"
#include <ph_coroutines/co_promise.hpp>
#include <ph_coroutines/i_was_co_awaited_and_now_i_am_suspending.hpp>
#include <experimental/coroutine>
using namespace std;
using namespace experimental;

template <typename T, typename... U>
auto fiind (auto&& fun)
{
    if (fun.template operator()<T>())
        return true;
    else
    {
        if constexpr (sizeof... (U) == 0)
            return false;
        else
            return fiind <U...> (fun);
    }
}


struct parser
{
    using value_type = expression*;
    using initial_suspend_awaitable_type = suspend_never;
    using final_suspend_awaitable_type = i_was_co_awaited_and_now_i_am_suspending;
    
    
    
    struct promise_type : co_promise <parser>
    {
        
        operator coroutine_handle <promise_type> ()
        {
            return coroutine_handle <promise_type>::from_promise (*this);
        }
        
        token::type m_looking_for_token;
        token m_found_token;
        function <bool(int)> m_ok;
        promise_type* m_current = this;
        promise_type* m_parent {nullptr};
        
        auto final_suspend () noexcept
        {
            cout << "tjooo" << endl;
            
            struct i_was_co_awaited
            {
                auto await_ready () noexcept -> bool
                {
                    return false;
                }
                
                /**
                 @param my_handle is a handle to this function
                 
                 @return a handle to the function that co_awaited us.
                 */

                auto await_suspend (coroutine_handle <promise_type> my_handle) noexcept -> coroutine_handle <>
                {
                    if (my_handle.promise().m_this_function_co_awaited_me)
                    {
                        my_handle.promise().m_parent -> m_current = &my_handle.promise();
                        
                    }
                    
                    auto& parent = my_handle.promise().m_this_function_co_awaited_me;
                    
                    return parent ? parent : noop_coroutine ();
                }
                
                auto await_resume () noexcept
                {
                    
                }
            };
            return i_was_co_awaited {};
        }
        
        template <int N>
        auto await_transform (int const(&a)[N])
        {
            m_ok = [a](int i) {
                for (auto j : a)
                {
                    if (i == j)
                    {
                        return true;
                    }
                }
                return false;
            };
            
            struct awaitable
            {
                promise_type& m_promise;
                
                auto await_ready ()
                {
                    return false;
                }
                
                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
                {
                    m_promise.m_this_function_co_awaited_me = co_awaited_me;
                    return true;
                }
                
                auto await_resume () -> token&
                {
                    return m_promise.m_found_token;
                }
            };
            return awaitable {*this};
        }
        

        auto await_transform (parser co_awaited)
        {
            co_awaited.m_promise.m_parent = this;
            m_current = &co_awaited.m_promise;
            
            struct awaitable
            {
                promise_type& m_promise;
                coroutine_handle<promise_type> m_handle = coroutine_handle<promise_type>::from_promise(m_promise);
                auto await_ready ()
                {
//                    return false;
//                    return m_handle.done();
                    return false;
                }
                
                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
                {
                    m_promise.m_this_function_co_awaited_me = co_awaited_me;
//                    return true;
//                    return m_handle;
                    return true;
                }
                
                auto await_resume () //-> token&
                {
//                    return m_promise.m_found_token;
                    return m_handle.resume();
                    cout << "tjo" << endl;
//                    return coroutine_handle<promise_type>::from_promise(m_promise);
//                    return m_handle;
                }
            };
            return awaitable {co_awaited.m_promise};
        }
        
        void parse (token const& t)
        {
            if (m_current == this)
            {
                if (m_ok (t.m_type))
                {
        //            cout << "OK" << endl;
                    m_found_token = t;
                    coroutine_handle <promise_type>::from_promise (*m_current).resume ();
                } else
                {
        //            cout << "NOT OK" << endl;
                }
                
            } else
            {
                m_current->parse (t);
            }

            
        }
    };
    
    
    void parse (token const& t)
    {
        m_promise.parse (t);
//        if (m_promise.m_ok (t.m_type))
//        {
////            cout << "OK" << endl;
//            m_promise.m_found_token = t;
//            static_cast <coroutine_handle<promise_type>>(m_promise).resume ();
//        } else
//        {
////            cout << "NOT OK" << endl;
//        }
    }
    
    auto resume ()
    {
        return coroutine_handle <promise_type>::from_promise (m_promise).resume ();
    }
    parser (promise_type& p) : m_promise {p}
    {

    }
    parser (parser&& other) : m_promise {other.m_promise}
    {

    }
    parser (parser const&) = delete;
    parser& operator=(parser const&) = delete;
    parser& operator=(parser&&) = delete;
//    coroutine_handle <promise_type> m_coro;
    promise_type& m_promise;
    
};





auto parse (vector <token> const& tokens, binary_expression * curr, int& i) -> expression *
{
//    bool have_lhs {false};
//    auto* exp = new binary_expression;
    
    for (; i < tokens.size (); ++i)
    {
        auto& tok = tokens [i];
        
        auto oper = tok.m_type;
        
        if (oper == token::type::number)
        {
            double num = stod (tok.m_text);
            curr -> m_rhs = new number {num};
            
        } else if (oper == token::type::plus)
        {
            curr -> m_type = binary_expression::add;
            
        } else if (oper == token::type::minus)
        {
            curr -> m_type = binary_expression::sub;
            
        } else if (oper == token::type::mult)
        {
            curr -> m_type = binary_expression::mult;
            
        } else if (oper == token::type::div)
        {
            curr -> m_type = binary_expression::div;
        }
    }
    return curr;
}
