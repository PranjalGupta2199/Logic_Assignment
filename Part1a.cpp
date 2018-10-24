#include <iostream> 
#include <stack> 
#include <string> 
using namespace std;
/**
    \detail File : Part1a.cpp\n
    \detail CS F214, Assignment 2 Part1(a).cpp
    \brief Class definition for a generic infix statement.

    \author  Pranjal Gupta
    \author Abhishree Jain
    \version  1.0 
    \date 24/10/2018
*/

/**
    
*/
class Expression{
public :    
    string infix_to_postfix(){
/**
    \brief Precondition : The infix expression must be well formed and fully parenthesized\n
    \brief Postcondition : The postfix expression of the given input        
    
    \returns postfix expression of the given infix expression
*/
        cout << "Enter the infix expression" << endl;
    //! \brief infix is input and postfix is the output expressions   
        string infix, postfix; 
    // contains the operators and parenethesis
        stack <char> operators; 

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
                    operators.pop(); //< removes the last left parenthesis
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
        return postfix; 
    }
};

int main()
{
    Expression *e;
    e = new Expression();
    string postfix = e->infix_to_postfix();
    cout << postfix << endl;
}

