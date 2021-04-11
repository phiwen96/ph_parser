#pragma once
using namespace std;

struct expression
{
    virtual double eval () const = 0;
    auto parent () -> expression*
    {
        return m_parent;
    }
    expression (expression* parent) : m_parent {parent}
    {
        
    }
    expression () : m_parent {nullptr}
    {
        
    }
    
    expression* m_parent {nullptr};
};


struct number : expression
{
    double m_value;
    
    number (double value) : m_value (value)
    {
        
    }
    virtual double eval () const override
    {
        return m_value;
    }
    
};


struct add : expression
{
    expression* lhs {nullptr};
    expression* rhs {nullptr};

    virtual double eval () const override
    {
        return lhs->eval() + rhs->eval();
    }
};

struct subtract : expression
{
    expression* lhs {nullptr};
    expression* rhs {nullptr};

    virtual double eval () const override
    {
        return lhs->eval() - rhs->eval();
    }
};

struct multiply : expression
{
    expression* lhs {nullptr};
    expression* rhs {nullptr};

    virtual double eval () const override
    {        
        return lhs->eval() * rhs->eval();
    }
};

struct divide : expression
{
    expression* lhs {nullptr};
    expression* rhs {nullptr};

    virtual double eval () const override
    {
        return lhs->eval() / rhs->eval();
    }
};

struct binary_expression : expression
{
    enum type
    {
        add,
        sub,
        mult,
        div,
        number
    };
    
    virtual double eval () const override
    {
        if      (m_type == add)     return m_lhs->eval() + m_rhs->eval();
        else if (m_type == sub)     return m_lhs->eval() - m_rhs->eval();
        else if (m_type == mult)    return m_lhs->eval() * m_rhs->eval();
        else if (m_type == div)     return m_lhs->eval() / m_rhs->eval();
        else if (m_type == number)  return m_lhs->eval();
    }
    binary_expression ()
    {
        
    }
    
    binary_expression (type t) : m_type (t)
    {
        
    }
    
    binary_expression (type t, expression* parent) : m_type {t}, expression {parent}
    {
        
    }

    type m_type;
    expression* m_lhs {nullptr};
    expression* m_rhs {nullptr};
};


struct variable : expression
{
    expression* m_expr;
    
    virtual double eval () const override
    {
        return m_expr -> eval ();
    }
};

struct value : expression
{
    double m_num;
    
    value (auto&& num) : m_num {forward <decltype (num)> (num)}
    {
        
    }
    
    virtual double eval () const override
    {
        return m_num;
    }
};






