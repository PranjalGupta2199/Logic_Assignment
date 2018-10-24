#include <iostream>

#include <string>
#include "LeafNode.h"
#include "ParseTree_h.h"
using namespace std;
/**
    \brief CS F214, Asn 2
    \brief Part1b.cpp
    \details Purpose : Calls LeafNode and ParseTree_h header files 

    \author : Pranjal Gupta
              Abhishree Jain
    \version : 1.0 24/10/2018
*/

int main(){
	cout << "Enter the postfix expression" << endl;

    ParseTree *t; 
    t = new ParseTree();

    string postfix;
    cin >> postfix;

    t -> postfix_to_parse_tree(postfix);
}