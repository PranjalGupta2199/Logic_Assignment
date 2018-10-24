#ifndef ParseTree_H
#define ParseTree_H

#include <iostream>

#include <string>
#include <vector>
using namespace std;

/**
    CS F214 Asn 2
    ParseTree_h.h
    Purpose : Contains class defintions for a Parse Tree 
    
    @author : Pranjal Gupta
              Abhishree Jain
    @version : 1.3 24/10/2018
*/



/**
* Input : Postfix string
*
* Output : The infix expression after performing in-order traversal of the tree formed.
*
* Definitions : 
*   Symbols for operators ::=  ~ <negation> | ^ <AND> | V <OR> | > <implication>
*
* in-order traversal :    
*   1. Traverse the left subtree, i.e., call Inorder(left-subtree)
*   2. Visit the root.
*   3. Traverse the right subtree, i.e., call Inorder(right-subtree)
*
*
* postfix_to_binary_tree : 
* 
* Input the given the postfix expression.
* Then iterate from the last character of the string, making a new node for each character you parse.
*   1. If the character to be added is an operator : 
*       > If the there is no root node, then make the temp node as root. This will happen only happen when the 
*           character is an operator (as the root node will only be an operator)
*       > Check the last node added : 
*           >> If it's an operator, then add the current node to it's child2.
*           >> Else (i.e when the character is an operand) find that node just above the last node added 
*               which has an empty child1. Then add this temp as child1
*   2. Else if the character to be added is an operand,
*       > If the last node added is the root, then add the current node as it's child2/
*       > Check the last node added : 
*           >> If it was an operator, then add temp node as it's child2.
*           >> Else, find that parent of the last node which has an empty child1. Add the current operator as it's 
*               child1.
* [end of FOR loop] 
*   
*/


class ParseTree{
public : 
    Leaf * root = NULL; //< top node in the parse tree
    Leaf * head = NULL; //< node which moves along the tree while adding new nodes 

/**
    Precondition:  The input must be a correct postfix expression
    Postcondition: Prints the infix expression of the given postfix by forming a binary tree
    
    @param : postfix expression 
    @returns : void
*/
    void postfix_to_parse_tree(string postfix){
        //string postfix;
        //getline(cin, postfix);
        
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


/**
    Precondition : Input must be a pointer of Leaf type pointing to the root node 
                   of the binary tree
    Postcondition : Prints the fully parenthesized infix expression by performing 
                  sthe in-order traversal of the binary tree
    
    @param : Leaf *ptr 
        Pointer to the root node of the parse tree
    @returns : void
*/
    void in_order(Leaf *head_ref){
        
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