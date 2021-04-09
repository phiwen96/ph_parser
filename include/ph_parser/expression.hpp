#pragma once
using namespace std;

struct expression
{
    virtual double eval () const = 0;
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
        div
    };
    
    virtual double eval () const override
    {
        if      (m_type == add)     return m_lhs->eval() + m_rhs->eval();
        else if (m_type == sub)     return m_lhs->eval() - m_rhs->eval();
        else if (m_type == mult)    return m_lhs->eval() * m_rhs->eval();
        else if (m_type == div)     return m_lhs->eval() / m_rhs->eval();
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
