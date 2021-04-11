#pragma once

template <typename... T>
struct overload : T...
{
    using T::operator()...;
    explicit overload (T&&... t) : T {forward <T> (t)}...
    {
        
    }
};
