#pragma once
#include "token.hpp"
#include "expression.hpp"
#include <ph_coroutines/co_promise.hpp>
#include <ph_coroutines/i_was_co_awaited_and_now_i_am_suspending.hpp>
#include <experimental/coroutine>
#include <ph_type_list/type_list.hpp>
#include "common.hpp"
using namespace ph;

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

template <typename T, typename... U>
constexpr auto is_variant_of_current_type (variant<U...> const& v) -> bool
{
    return visit ([]<typename V>(V const& u) constexpr -> bool {return is_same_v <V, T>;}, v);
}

template <typename... U>
constexpr auto is_variant_of_current_type (auto&& a, variant<U...> const& v) -> bool
{
    return visit ([]<typename V>(V const& u) constexpr -> bool {return is_same_v <V, decltype (a)>;}, v);
}
#define GETTER_STRUCTS \
    X (get_stack) \
    X (get_token)

#define X(s) \
    struct _##s {}; \
    inline constexpr _##s s {};

    GETTER_STRUCTS
#undef X






using Stack = stack <Token>;

struct parser
{
    using return_type = any;//variant <TOKENS>;
    using initial_suspend_awaitable_type = suspend_never;
    using final_suspend_awaitable_type = i_was_co_awaited_and_now_i_am_suspending;
    
    
    
    struct promise_type : co_promise <parser>
    {
        promise_type ()
        {
//            cout << "promise_type (" << coroutine_handle<promise_type>::from_promise (*this).address() << ")" << endl;
        }
        ~promise_type ()
        {
//            cout << "~promise_type (" << coroutine_handle<promise_type>::from_promise (*this).address() << ")" << endl;
        }
        operator coroutine_handle <promise_type> ()
        {
            return coroutine_handle <promise_type>::from_promise (*this);
        }
        
        using base = co_promise <parser>;
        token::type m_looking_for_token;
        token m_found_token;
        function <bool(any const&)> m_ok = [](any const&){return true;};
        promise_type* m_current {this};
        promise_type* m_parent {nullptr};
//        variant <TOKENS> m_current_token;
        any m_current_token;

        variant <TOKENS> m_return_token;
//        stack <variant <TOKENS>> m_stack;
        stack <any> m_stack;


        /**
         push token to stack
         */
        auto yield_value (variant<TOKENS> const& tok)
        {
            m_stack.push (tok);
            return suspend_never {};
        }
        
        auto final_suspend () noexcept
        {
            
            struct i_was_co_awaited
            {
                promise_type& m_promise;
                auto await_ready () noexcept -> bool
                {
//                    cout << "final_suspend!!" << endl;
//                    return coroutine_handle<promise_type>::from_promise (m_promise).done();
                    return false;
                }
                
                /**
                 @param my_handle is a handle to this function
                 
                 @return a handle to the function that co_awaited us.
                 */

                auto await_suspend (coroutine_handle <promise_type> my_handle) noexcept -> coroutine_handle <>
                {
                    auto& parent_promise = *my_handle.promise().m_parent;
                    
                    if (my_handle.promise().m_this_function_co_awaited_me)
                    {
                        
                        auto& parent_handle = my_handle.promise().m_this_function_co_awaited_me;

                        parent_promise.m_current = &parent_promise;

                        return coroutine_handle<promise_type>::from_promise (*parent_promise.m_current);

                    } else
                    {
                        cout << "whaaaat" << endl;
                        return noop_coroutine ();
                    }
                    
                   
                    
                }
                
                auto await_resume () noexcept
                {
//                    cout << "tjoo" << endl;
//                    return *m_promise.m_parent
                }
            };
            return i_was_co_awaited {*this};
        }
        
      
        
        template <typename... T>
        auto await_transform (type_list_t <T...> tl)
        {
//            m_ok = [](Token const& v){return type_list_t <T...>::has_variant (v);};

            m_ok = [](any const& a){return type_list_t <T...>::has_any (a);};

            
            struct awaitable
            {
                promise_type& m_promise;
                coroutine_handle<promise_type> m_handle = coroutine_handle<promise_type>::from_promise(m_promise);

                auto await_ready ()
                {
//                    cout << "await_ready" << endl;
//                    return false;
                    return m_handle.done();
                }
                
                auto await_suspend (coroutine_handle <promise_type> co_awaited_me) //-> coroutine_handle <promise_type>
                {
                    m_promise.m_this_function_co_awaited_me = co_awaited_me;

//                    cout << "await_suspend" << endl;
                    return true;
                }
                
                auto await_resume () -> auto&
                {
//                    cout << "await_resume" << endl;
                    return m_promise.m_current_token;
                }
            };
            return awaitable {*this};
        }
        
        auto await_transform (suspend_always)
        {
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
                
                auto await_resume () -> auto&
                {
                    return m_promise.m_current_token;
                }
            };
            return awaitable {*this};
        }
        
        auto await_transform (_get_stack)
        {
//            cout << "tjo" << endl;
            struct awaitable
            {
                promise_type& m_promise;
                
                auto await_ready ()
                {
//                    return coroutine_handle <promise_type>::from_promise (m_promise).done()
                    return true;
                }
                
                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
                {

                }
                
                auto await_resume () -> auto&
                {
                    return m_promise.m_stack;
                }
            };
            return awaitable {*this};
        }

        auto await_transform (parser co_awaited)
        {
            co_awaited.m_promise.m_parent = this;
            m_current = &co_awaited.m_promise;
//            m_value -> m_rhs = co_awaited.m_promise.m_value;
            
            struct awaitable
            {
                promise_type& m_promise;
                coroutine_handle<promise_type> m_handle = coroutine_handle<promise_type>::from_promise(m_promise);
                auto await_ready ()
                {
                    return m_handle.done();
//                    return false;
                }
                
                auto await_suspend (coroutine_handle <> co_awaited_me) //-> coroutine_handle <promise_type>
                {
//                    cout << "await_suspend!" << endl;
                    m_promise.m_this_function_co_awaited_me = co_awaited_me;
                    return true;
                }
                
                auto await_resume () -> auto&&
                {
//                    cout << "await_resume" << endl;

                    return move (m_promise.m_return_value);
//                    return m_promise.m_return_token;
                }
            };
            return awaitable {co_awaited.m_promise};
        }
        
        void parse (any const& e)
        {
            if (m_current == this)
            {
//                if (coroutine_handle <promise_type>::from_promise (*this).done ())
//                {
//                    cout << "lol " << e << " " << coroutine_handle<promise_type>::from_promise(*this).address() << endl;
//
//                    m_parent->m_current = m_parent;
//
////                    m_parent -> parse (e);
//                }
//                m_stack.push (e);
                if (m_ok (e))
                {
                    
                    m_current_token = e;
//                    m_current_token = e;
//                    cout << "tjo" << endl;
//                    cout << "adding token " << e << " " << coroutine_handle<promise_type>::from_promise(*this).address() << endl;
//                    cout << coroutine_handle <promise_type>::from_promise (*m_current).done () << endl;
                    coroutine_handle <promise_type>::from_promise (*m_current).resume ();
                } else
                {
                    m_stack.push (e);
                }
                
            } else
            {
                m_current->parse (e);
            }

            
        }
    };
    
    
    void parse (any const& e)
    {
        m_promise.parse (e);
    }
    

    auto get_value () -> return_type
    {
        return m_promise.m_return_value;
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
    ~parser ()
    {
        coroutine_handle <promise_type>::from_promise (m_promise).destroy();
    }
    parser (parser const&) = delete;
    parser& operator=(parser const&) = delete;
    parser& operator=(parser&&) = delete;
//    coroutine_handle <promise_type> m_coro;
    promise_type& m_promise;
    
};






