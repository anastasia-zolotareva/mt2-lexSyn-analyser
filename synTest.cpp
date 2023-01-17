#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lexSyn.cpp"

string toTest(string input, string filename="g") {
    string output = "";
    Parser * pars = new Parser(input);
    Tree test = pars->parse();
    string ans = "digraph G {";
    int ind = -1;
    test.dotString(ind, -1, ans);
    ans += "\n}";
    ofstream out(".\\dots\\" + filename + ".dot");
    out << ans;
    out.close();
    const string com = "dot .\\dots\\" + filename + ".dot -Tpng -o .\\imgs\\" + filename + ".png";
    system(com.data());
    return ans;
}

TEST_CASE("1) Correct rules", "[Parser]") {
    REQUIRE_NOTHROW(toTest("a", "dot1"));
    REQUIRE_NOTHROW(toTest("a*", "dot2"));
    REQUIRE_NOTHROW(toTest("a|b", "dot3"));
    REQUIRE_NOTHROW(toTest("abc|b", "dot4"));
    REQUIRE_NOTHROW(toTest("abc*b", "dot5"));
    REQUIRE_NOTHROW(toTest("abc*|b", "dot6"));
    REQUIRE_NOTHROW(toTest("(a)", "dot7"));
    REQUIRE_NOTHROW(toTest("(a)|(b)", "dot8"));
    REQUIRE_NOTHROW(toTest("((a))", "dot9"));
    REQUIRE_NOTHROW(toTest("(abc)*", "dot10"));
    REQUIRE_NOTHROW(toTest("((abc*b|a)*ab(aa|b*)b)*", "dot11"));
}

TEST_CASE("2) Incorrect strings", "[Parser]") {
    REQUIRE_THROWS_WITH(toTest("*"), "S: illigal token CONC");
    REQUIRE_THROWS_WITH(toTest("a|"), "C: illigal token END");
    REQUIRE_THROWS_WITH(toTest("()|b"), "S: illigal token RPAREN");
    REQUIRE_THROWS_WITH(toTest("|b"), "S: illigal token VARIANT");
    REQUIRE_THROWS_WITH(toTest("()|"), "S: illigal token RPAREN");
    REQUIRE_THROWS_WITH(toTest("abc*|"), "C: illigal token END");
    REQUIRE_THROWS_WITH(toTest("*|"), "S: illigal token CONC");
    REQUIRE_THROWS_WITH(toTest("|"), "S: illigal token VARIANT");
    REQUIRE_THROWS_WITH(toTest("(a))"), "illigal end token RPAREN");
    REQUIRE_THROWS_WITH(toTest(")("), "S: illigal token RPAREN");
    REQUIRE_THROWS_WITH(toTest("((a)"), "C: illigal token END");
    REQUIRE_THROWS_WITH(toTest("("), "S: illigal token END");
}
