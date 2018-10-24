#ifndef ParseTree_H
#define ParseTree_H

#include <iostream>

#include <string>
#include <vector>
using namespace std;

/**
    \details File : ParseTree_h.h\n
    \details CS F214 Assignment 2
    \brief Class defintions for a Parse Tree 
    
    \author  Pranjal Gupta
    \author  Abhishree Jain
    \version 1.3 
    \date 24/10/2018
*/


class ParseTree{
public : 
//! \brief Top node in the parse tree
    Leaf * root = NULL; 
//! \brief Node which moves along the tree while adding new nodes
    Leaf * head = NULL;  

/**
    \brief Precondition:  The input must be a correct postfix expression
    \brief Postcondition: Prints the infix expression of the given postfix by forming a binary tree
    
    \param : postfix expression 
    \returns : void
*/
    void postfix_to_parse_tree(string postfix){
        
        for (int i = postfix.length() - 1; i >= 0; i--){
            // creating new instance of Leaf class
            Leaf* temp;
            temp = new Leaf(postfix[i]);
            
            if (temp -> value == '~') {
                Leaf *t;
                t = new Leaf('\0');
                temp ->  child1 = t;
            } //< Negation will always have child1 as some default value
            
            switch (postfix[i]) {
                case('V') :
                case('^') :
                case('~') :
                case('>') :

                    if (head == NULL){
                    // tree is empty
                        root = temp;
                        head = temp;       
                    
                    } else if(head -> value == 'V' || head -> value == '^' || head -> value == '~' || head -> value == '>') {
                       head = temp -> add_child2(&head, &temp);   //< Adding a operator as child2 to head      
                    
                    } else {
                        head = temp -> add_child1(&head, &temp); //< finding the nearest node which has a NULL child1
                    
                    } break;
                
                default :
                    
                    if (head -> parent == NULL){
                    // If the tree has only one node, i.e root
                        head -> child2 = temp;
                        temp -> parent = head;
                        head = head -> child2;
                    
                    } else if (head -> value == 'V' || head -> value == '^' || head -> value == '>' || head -> value == '~'){
                        head = temp -> add_child2(&head, &temp); //< Adding operand under a operator
                    
                    } else {
                        head = temp -> add_child1(&head, &temp); //< Finding the nearest node which has a NULL child1
                    
                    } break;
            }
        }

        in_order(root); // calls in-order traversal method
        cout << endl;
}


    void in_order(Leaf *head_ref){

/**
    \brief Precondition : Input must be a pointer of Leaf type pointing to the root node of the binary tree
    \brief Postcondition : Prints the fully parenthesized infix expression by performing the in-order traversal of the binary tree
    
    \param  Leaf *ptr \n
        Pointer to the root node of the parse tree
    \returns  void
*/        
        if (head_ref -> child1 != NULL && head_ref -> child2 != NULL){
            cout << "(";
            in_order(head_ref -> child1); //< traverse the left sub-tree
            cout << " " << head_ref -> value << " "; // print the root node
            in_order(head_ref -> child2); //< traverse the right sub-tree
            cout << ")";        
            return;
        
        } else {
            if(head_ref -> value == '\0') return; //< default child1 of negation is not printed
            else cout << head_ref -> value; //< Prints the operand
            return;
        }
    }
};

#endif