#include <iostream>
#include <fstream>
#include <vector>
#include "lexicalAnalyser.cpp"

using namespace std;

/* Rules:
    S -> V S'
    S' -> | V S'
    S' -> eps
    
    V -> K V'
    V' -> K V'
    V' -> * V'
    V' -> eps
    
    K -> C K'
    K' -> eps
    C -> ( E )
    C -> char
*/

class Parser {
    private:
    LexicalAnalyzer * lex;

    public:
    Parser(string str) {
        this->lex = new LexicalAnalyzer(str);
    }
    Tree S() {
        switch(this->lex->getCurToken()) {
            case LPAREN:
            case CHARECTER:
                {
                return Tree("S", {this->V(), this->SPrime()});
                break;
                }
            default:
                const string err= "S: illigal token " + string(*this->lex);
                throw err;
        }
    }

    Tree SPrime() {
        switch(this->lex->getCurToken()) {
            case VARIANT:
                {
                cout<<lex->getCurChar();
                this->lex->nextToken();
                return Tree("S1", {Tree("|", {}), this->V(), this->SPrime()});
                break;
                }
            case RPAREN:
            case END:
                {
                return Tree("S1", {Tree("eps", {})});
                break;
                }
            default:
                const string err= "S1: illigal token " + string(*this->lex);
                throw err;
        }
    }
    Tree V() {
        switch(this->lex->getCurToken()) {
            case CONC:
            case LPAREN:
            case CHARECTER:
            case END:
                {
                return Tree("V", {this->K(), this->VPrime()});
                break;
                }
            default:
                const string err= "V: illigal token " + string(*this->lex);
                throw err;
        }
    }

    Tree VPrime() {
        switch(this->lex->getCurToken()) {
            case CONC:
                {
                this->lex->nextToken();
                return Tree("V1", {Tree("*", {}), this->VPrime()});
                break;
                }
            case CHARECTER:
            case LPAREN:
                {
                return Tree("V1", {K(), this->VPrime()});
                break;
                }
            case VARIANT:
            case RPAREN:
            case END:
                {
                return Tree("V1", {Tree("eps", {})});
                break;
                }
            default:
                const string err= "V1: illigal token " + string(*this->lex);
                throw err;
        }
    }

    Tree K() {
        switch(this->lex->getCurToken()) {
            case CONC:
            case LPAREN:
            case CHARECTER:
            case END:
                {
                return Tree("K", {this->C(), this->KPrime()});
                break;
                }
            default:
                const string err= "K: illigal token " + string(*this->lex);
                throw err;
        }
    }

    Tree KPrime() {
        return Tree("K1", {Tree("eps", {})});
    }

    Tree C() {
        switch(this->lex->getCurToken()) {
            case LPAREN:
                {
                this->lex->nextToken();
                Tree sub = this->S();
                if (this->lex->getCurToken() != RPAREN) {
                    const string err= "C: illigal token " + string(*this->lex);
                    throw err;
                }
                this->lex->nextToken();
                return Tree("C", {Tree("(", {}), sub, Tree(")", {})});
                break;
                }
            case CHARECTER:
                {
                this->lex->nextToken();
                return Tree("C", {Tree("char", {})});
                break;
                }
            default:
                const string err= "C: illigal token " + string(*this->lex);
                throw err;
                break;
        }
    }
    

    Tree parse() {
        this->lex->nextToken();
        Tree ans = this->S();
        if (this->lex->getCurToken() != END) {
            const string err= "illigal end token " + string(*this->lex);
            throw err;
        }
        return ans;
    }
};

/* int main() {
    string a;
    cout << "write string: ";
    cin >> a;
    try {
        LexicalAnalyzer * test_lex = new LexicalAnalyzer(a);
        for (int i = 0; i <= a.length(); i++) {
            test_lex->nextToken();
            cout<<string(*test_lex);
        }
    }
    catch (const string e) {
        cout<<"error in lexical analysation!\n";
        cout<<e;
        cout<<"\n";
    }
    catch (...) {
        cout<<"some illegal thing in lexical analysation!";
        cout<<"\n";
    }
    try {
        Parser * pars = new Parser(a);
        Tree test = pars->parse();
        string ans = "digraph G {";
        int ind = -1;
        test.dotString(ind, -1, ans);
        ans += "\n}";
        ofstream out("g.dot");
        out << ans;
        out.close();
        system("dot g.dot -Tpng -o g.png");
    }
    catch (const string e) {
        cout << "some error!\n";
        cout << e;
        cout<<"\n";
    }
    catch (...) {
        cout<< "some unknown error(";
        cout<<"\n";
    }
    return 0;
} */