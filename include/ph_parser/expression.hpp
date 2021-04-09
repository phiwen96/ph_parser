#pragma once
using namespace std;

struct expression
{
    virtual double eval () const = 0;
};


struct number : expression
{
    double m_value;
    
    virtual double eval () const override
    {
        
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
