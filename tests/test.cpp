//#include <catch2/catch.hpp>
//#include <ph_parser/lexer.hpp>
//#include <ph_parser/token.hpp>
//#include <ph_parser/expression.hpp>
//#include <ph_parser/parser.hpp>
//#include <ph_type_list/type_list.hpp>
//#include <variant>
//using namespace std;
//
//
//
//
///**
//
//
//
//      +            *
//1            5           +
//                    2        1
//
//
//     +
//1             *          +
//        5           2         1
//
//
// */
//
//int loops {0};
//
////parser parse ()
////{
////    int m_loop = loops;
////    ++loops;
////
////    begin:
////
////
////
////    has_lhs:
////    co_return 3;
////}
//
//
//
//
//
//
//
//auto parse () -> parser
//{
////    auto m_stack = stack <variant <TOKENS>> {};
//
//    begin:
//    for (;;)
//    {
//        variant <TOKENS> & token = co_await type_list <TOKENS>;
//        cout << token << endl;
//        if (token == ph::number_t {})
//            cout << "oj" << endl;
//
//        else if (token == ph::minus_t {})
//        {
//            co_yield token;
//            goto first_minus;
//        }
////        else if (token == ph::number{})
//
//    }
//
//    first_minus:
//    for (;;)
//    {
//        variant <TOKENS> & token = co_await type_list <TOKENS>;
//
//        if (token == ph::number_t {})
//        {
//            auto& m_stack = co_await get_stack;
//            cout << m_stack.top() << endl;
//
//            get <ph::number_t> (token).m_number *= -1;
//            cout << "yay" << token << endl;
//        }
//    }
//
//
//
//
//
//}
//
//
//
//
//
//
//
//
//
//TEST_CASE ("hej")
//{
//
//
//
//
//
//
////    return;
//    vector <ph::Token> tokens = lex ("-4*5+6-(7+8)/97");
//
//    parser p = parse ();
//    for (auto const& token : tokens)
//    {
//        p.parse (token);
//
//    }
//
//
////    vector <token> tokens = lex ("1+2+3+7+4");
////    []{
////        vector <token> tokens = lex ("1+5+1");
////        parser p = loop ();
////
////    //    p.resume ();
////        for (auto const& i : tokens)
////            p.parse (i);
////
////        expression * res = p.get_value();
////        assert (res->eval() == 7);
////    }();
////
////    []{
////        vector <token> tokens = lex ("-5-5");
////        parser p = loop ();
////
////    //    p.resume ();
////        for (auto const& i : tokens)
////            p.parse (i);
////
////        expression * res = p.get_value();
////        assert(res->eval() == -10);
////    }();
////
////    []{
////        vector <token> tokens = lex ("1+5+2*2");
////        parser p = loop ();
////
////    //    p.resume ();
////        for (auto const& i : tokens)
////            p.parse (i);
////
////        expression * res = p.get_value();
////        assert(res->eval() == 10);
////    }();
////
////    []{
////        vector <token> tokens = lex ("1+5*2+1");
////        parser p = loop ();
////
////    //    p.resume ();
////        for (auto const& i : tokens)
////            p.parse (i);
////
////        expression * res = p.get_value();
////        cout << res->eval() << endl;
//////        assert(res->eval() == 12);
////    };
//
////    vector <token> tokens__ = lex ("-4*5+6-(7+8)/97");
//
//
////    if (auto* a = get_if<int>(&d))
////        cout << "tjo" << endl;
//
//
//
//
//
////    variant <ph::expression, ph::term, ph::factor, ph::number> d {in_place_type <ph::term>};
//
//
//
//
//
////        cout << i << endl;
//
//
////    auto* root = new binary_expression;
////    root -> m_lhs = new number {0};
////    root -> m_type = binary_expression::add;
////    int i {0};
////    auto* tree = parse (tokens, root, i);
////
////    cout << tree -> eval() << endl;
//    cout << endl;
//}
