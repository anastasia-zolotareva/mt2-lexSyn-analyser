#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lexicalAnalyser.cpp"

string toTest(string input) {
    LexicalAnalyzer * lex = new LexicalAnalyzer(input);
    string output = "";
    for (int i = 0; i <= input.length(); i++) {
            lex->nextToken();
            string ans = string(*lex);
            output += " " + string(*lex);
            if (ans == "END") {
                break;
            }
    }
    return output;
}

TEST_CASE("1) Simple correct strings", "[LexicalAnalyzer]") {
    REQUIRE(toTest("a") == " CHARECTER END");
    REQUIRE(toTest("ab") == " CHARECTER CHARECTER END");
    REQUIRE(toTest("abc") == " CHARECTER CHARECTER CHARECTER END");
    REQUIRE(toTest("a|b") == " CHARECTER VARIANT CHARECTER END");
    REQUIRE(toTest("a*") == " CHARECTER CONC END");
    REQUIRE(toTest("a*|b") == " CHARECTER CONC VARIANT CHARECTER END");
    REQUIRE(toTest("(a)") == " LPAREN CHARECTER RPAREN END");
    REQUIRE(toTest("(a)*|b") == " LPAREN CHARECTER RPAREN CONC VARIANT CHARECTER END");
}

TEST_CASE("2) Simple incorrect strings", "[LexicalAnalyzer]") {
    REQUIRE_THROWS_WITH(toTest("A"), "illegal charecter at pos 0 : A");
    REQUIRE_THROWS_WITH(toTest("aA"), "illegal charecter at pos 1 : A");
    REQUIRE_THROWS_WITH(toTest("10"), "illegal charecter at pos 0 : 1");
    REQUIRE_THROWS_WITH(toTest("a?"), "illegal charecter at pos 1 : ?");
}

TEST_CASE("3) Correct strings", "[LexicalAnalyzer]") {
    REQUIRE(toTest(" (a )* |b") == " LPAREN CHARECTER RPAREN CONC VARIANT CHARECTER END");
    REQUIRE(toTest("(a\n)*\t|b\n") == " LPAREN CHARECTER RPAREN CONC VARIANT CHARECTER END");
    REQUIRE(toTest("((abc*b|a)*ab(aa|b*)b)*") == " LPAREN LPAREN CHARECTER CHARECTER CHARECTER CONC CHARECTER VARIANT CHARECTER RPAREN CONC CHARECTER CHARECTER LPAREN CHARECTER CHARECTER VARIANT CHARECTER CONC RPAREN CHARECTER RPAREN CONC END");
}




