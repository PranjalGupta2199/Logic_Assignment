#include <iostream> 
#include <stack> 
#include <string> 
using namespace std;
/*
	Algorithm : 
	1 : Push '(' onto stack and add ')' to the end of the expression
	2 : Scan X from left to right and REPEAT steps 3 to 6 for each element of X UNTIL the stack is empty 
	3 : If an operand is encountered, add it to result
	4 : If a '(' is encountered, push it onto stack
	5 : If an operator is encountered, then : 
        (a) Repeatedly pop from stack and add to result each operator which has the same precedence as or higher precedence than operator.
        (b) Add operator to stack
	6 : If ')' is encountered then :
        (a) Repeatedly pop from stack and add to result each operator until a '(' is encountered
        (b) Remove the '('
	7 : END    
*/

void infix_to_postfix()
{
    /*
        Precondition : The infix expression must be well formed and fully parenthesized
        Postcondition : The postfix expression of the given input
    */
	cout << "Enter the infix expression" << endl;
	string infix, postfix; // infix is input and postfix is the output expressions
	stack <char> operators; // contains the operators and parenethesis

	cin >> infix;
		
	for (int i = 0; i < infix.length(); i++)
	{
		switch (infix[i])
		{
			case('V') : 
			case ('^') :
			case ('>') :
			case ('~') : 
			case ('(') :
			    // if the character is an operator or a left parenthesis, then 
			    // push it onto stack
				operators.push(infix[i]);
				break;
				
			case (')') : 
			    // else pop all the elements until a left parenthesis is encountered.
				do{
					postfix += operators.top();
					operators.pop();
				}
				while (operators.top() != '(');
				operators.pop(); // removes the last left parenthesis
				break;
			case (' ') :
			 	// If space comes in the infix input 
				break;
			default :
			    // this is the case when an operand is reached.
				postfix += infix[i];
				break;
			
		}
	}
	cout << postfix << endl;	
}

int main()
{
	infix_to_postfix();
}

