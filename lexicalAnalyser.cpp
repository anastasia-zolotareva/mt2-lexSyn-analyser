#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Token {
    LPAREN,
    RPAREN,
    CONC,
    VARIANT,
    CHARECTER,
    END
};

class Tree {
    private:

    string node;
    vector<Tree> children = {};

    public:

    Tree(string node, vector<Tree> tree) {
        this->node = node;
        this->children = tree;
    }

    void dotString(int & cur_ind, int prev_ind, string & cur_str) {
        cur_ind++;
        cur_str += "\n" + to_string(cur_ind) + " [label = \"" + this->node + "\"]";
        if (prev_ind > -1) {
            cur_str += "\n" + to_string(prev_ind) + " -> " + to_string(cur_ind);
        }
        prev_ind = cur_ind;
        for (int j = 0; j < this->children.size(); j++) {
            this->children[j].dotString(cur_ind, prev_ind, cur_str);
        }
    }


    operator string() {
        string ans = this->node;
        if (children.size() == 0) {return ans;};
        ans += "\n|";
        for (int i = 0; i < children.size(); i++) {
            ans += "_" + string((this->children[i])) + "|_\n";
        }
        ans += "\n";
        return ans;
    }
};

class LexicalAnalyzer {
    private:

    string file;
    Token curToken;
    int curPos = 0;
    char curChar = '$';

    bool isBlank() {
        return this->curChar == ' ' || this->curChar == '\t' || this->curChar == '\n';
    }

    void nextChar() {
        this->curPos++;
        if (this->file.length() == this->curPos) {
            this->curChar = '$';
            return;
        }
        this->curChar = this->file[this->curPos];
    }

    public:

    LexicalAnalyzer(string file) {
        this->file = file;
        try {
            this->curChar = this->file[0];
        }
        catch (...) {
            this->curChar = '$';
        }
    }

    operator string() {
        switch(this->getCurToken()) {
            case LPAREN:
                return "LPAREN";
            case RPAREN:
                return "RPAREN";
            case CONC:
                return "CONC";
            case VARIANT:
                return "VARIANT";
            case CHARECTER:
                return "CHARECTER";
            case END:
                return "END";
        }
    }

    void nextToken() {
        while(isBlank()) {
            nextChar();
        }
        switch (this->curChar)
        {
        case '(':
            nextChar();
            this->curToken = LPAREN;
            break;
        case ')':
            nextChar();
            this->curToken = RPAREN;
            break;
        case '|':
            nextChar();
            this->curToken = VARIANT;
            break;
        case '*':
            nextChar();
            this->curToken = CONC;
            break;
        case '$':
            this->curToken = END;
            break;
        default:
            if (int(this->curChar) >= 97 && int(this->curChar) <= 122) {
                nextChar();
                this->curToken = CHARECTER;
            }
            else {
                const string err = "illegal charecter at pos " + to_string(this->curPos) + " : " + this->curChar;
                throw err;
            }
            break;
        }
    }

    const Token getCurToken() {
        return this->curToken;
    }

    char getCurChar() {
        return this->curChar;
    }

};