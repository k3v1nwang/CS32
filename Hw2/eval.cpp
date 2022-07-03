#include <string>
#include <cctype>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

int evaluate(string infix, string& postfix, bool& result);
bool isValid(string infix);
string convert(string infix, string& postfix);
int precedence(char c);

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	assert(evaluate("!(T&F)", pf, answer) == 0 && pf == "TF&!");
	assert(evaluate("(F) & T) ^((F)", pf, answer) == 1);
	assert(evaluate("TT", pf, answer) == 1);
	assert(evaluate("(!!!T)", pf, answer) == 0 && pf == "T!!!");
	assert(evaluate("TT^^F T", pf, answer) == 1);
	assert(evaluate("T!^F", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("T(", pf, answer) == 1);
	assert(evaluate("FT", pf, answer) == 1);
	assert(evaluate("FF", pf, answer) == 1);
	assert(evaluate("F(F)", pf, answer) == 1);
	assert(evaluate("T!&T", pf, answer) == 1);
	assert(evaluate("T!^T", pf, answer) == 1);
	assert(evaluate("(T!)", pf, answer) == 1);
	assert(evaluate("T&&T", pf, answer) == 1);
	assert(evaluate("T&^T", pf, answer) == 1);
	assert(evaluate("(T&)", pf, answer) == 1);
	assert(evaluate("T^&T", pf, answer) == 1);
	assert(evaluate("T^^T", pf, answer) == 1);
	assert(evaluate("(T^)", pf, answer) == 1);
	assert(evaluate("(&T)", pf, answer) == 1);
	assert(evaluate("(^T)", pf, answer) == 1);
	assert(evaluate("T()", pf, answer) == 1);
	assert(evaluate("(T^T)T", pf, answer) == 1);
	assert(evaluate("(T^T)F", pf, answer) == 1);
	assert(evaluate("(T^T)!", pf, answer) == 1);
	assert(evaluate("(T^T)(", pf, answer) == 1);
	assert(evaluate("T & !(F^ T & T^ F) ^!!! (F & T&F)", pf, answer) == 0
		&& pf == "TFTT&^F^!&FT&F&!!!^");
	cout << "Passed all tests" << endl; 
}
int evaluate(string infix, string& postfix, bool& result)
{
	if (isValid(infix)) {

		postfix = convert(infix, postfix);
		if (postfix.empty())
			return 1;

		stack<bool>rStack;		//stack of trues or falses

		for (int k = 0; k < postfix.size(); k++) {

			char c = postfix[k];

			if (c == 'T')
				rStack.push(true);

			else if (c == 'F')
				rStack.push(false);

			else if (c == '!') {			//temp bool to swap truth values
				bool temp = rStack.top();
				rStack.pop();
				rStack.push(!temp);
			}

			else {
				bool r2 = rStack.top();
				rStack.pop();
				if (rStack.empty())		//parenthesis check
					return 1;
				bool r1 = rStack.top();
				rStack.pop();
				//evaluate
				if (postfix[k] == '&') {
					if (r1 && r2)
						rStack.push(true);
					else
						rStack.push(false);
				}
				if (postfix[k] == '^') {
					if (r1 ^ r2)				//exlusive or
						rStack.push(true);
					else
						rStack.push(false);
				}
			}
		}
		result = rStack.top();
		return 0;
	}
	return 1;
};

bool isValid(string infix)
{
	//check syntax of infix string, return false for invalid characters/wrong syntax

	//first get rid of spaces
	string s = "";
	for (int k = 0; k < infix.size(); k++)
	{
		if (infix[k] != ' ')
			s += infix[k];
	}
	//check valid char and sequence
	
	for (int k = 0; k < s.size(); k++)
	{
		//valid chars
		if (s[k] != 'T' && s[k] != 'F' && s[k] != '(' && s[k] != ')' && s[k] != '!' && s[k] != '&' && s[k] != '^')
			return false;
		if (s[k] == '(') {
			if(s[k + 1] == ')')		//cannot have empty parenthesis 
				return false;
		}
		if (s[k] == ')')					//close parenthesis cannot be followed by T F or !
		{
			if (s[k + 1] == 'T' || s[k + 1] == 'F' || s[k + 1] == '!')
				return false;
		}
		if (s[k] == '^' || s[k] == '&')			//binary operators much have operand expresions before and after
		{
			if (s[k - 1] != 'T' && s[k - 1] != 'F' && s[k - 1] != ')')		//valid previous values
				return false;
			if (s[k + 1] != 'T' && s[k + 1] != 'F' && s[k + 1] != '(' && s[k+1] != '!')	   //valid next values
				return false;
		}
		else if (s[k] == 'T' || s[k] == 'F')		//operands cannot be followed by another operand, (, or !
		{
			if (s[k + 1] == 'T' || s[k + 1] == 'F' || s[k + 1] == '(' || s[k + 1] == '!')
				return false;
		}
	}
	return true;
};

string convert(string infix, string& postfix)
{
	postfix = "";
	stack<char>oStack;
	for (int k = 0; k < infix.size(); k++)
	{
		char c = infix[k];
		switch (c) {
		case 'T':
		case'F':
			postfix += infix[k];			//append operands to postfix
			break;
		case '(':
			oStack.push(c);					//push ( to stack
			break;
		case ')':
			while (!oStack.empty() && oStack.top() != '(') {			//pop operands off the stack 
				postfix += oStack.top();
				oStack.pop();
			}
			if (oStack.empty())			//invalid syntax			
				return "";
			oStack.pop();
			break;
		case '!':
			while (!oStack.empty() && oStack.top() != '(' && precedence(c) < precedence(oStack.top())) {	//append operants with greater precedence
				postfix += oStack.top();
				oStack.pop();
			}
			oStack.push(c);		//push current operator
			break;
		case '&':
		case '^':
			while (!oStack.empty() && oStack.top() != '(' && precedence(c) <= precedence(oStack.top())) {		//append operants with greater/equal precendence 
				postfix += oStack.top();
				oStack.pop();
			}
			oStack.push(c);		//push current operator
			break;
		default:
			break;
		}

	}

	//pop the rest of the operators off the stack and append to postfix
	while (!oStack.empty()) {
		postfix += oStack.top();
		oStack.pop();
	}

	return postfix;
};

int precedence(char c)
{
	switch (c)
	{
	case '!':
		return 3;
	case '&':
		return 2;
	case '^':
		return 1;
	default:
		return 0;
	}
};