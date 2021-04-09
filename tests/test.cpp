#include <catch2/catch.hpp>
#include <ph_parser/lexer.hpp>
#include <ph_parser/token.hpp>
#include <ph_parser/expression.hpp>
#include <ph_parser/parser.hpp>
using namespace std;









TEST_CASE ("hej")
{
    vector <token> tokens = lex ("3.8+47.24-23");
    
    for (auto& i : tokens)
        cout << i << endl;
    
    parse (tokens);
    
}
