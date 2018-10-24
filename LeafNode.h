#ifndef LEAFNODE
#define LEAFNODE

#include <iostream>

#include <string>
#include <vector>
using namespace std;

/**
    CS F214 Asn 2
    LeafNode.h
    Purpose : Contains class definitions for Leaf Node 
    
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
*/ 
 


/**
    This is a class for a node in the binary tree. 
    
    Members : 
        value : char
            Will be an operator or an operand
        parent : * Leaf
            Will point to this node's parent
        chidl1 : * Leaf 
            Will point to left child node
        child2 : * Leaf 
            Will to point to right child node
*/
class Leaf{
public :
    char value;
    Leaf * parent;
    Leaf * child1;
    Leaf * child2;

/*
    Constructor for Leaf class
    Intializes all the data members.
*/
    Leaf(char v){
        parent = NULL;
        child1 = NULL;
        child2 = NULL;
        value = v;
    }


/**
    Adds a new node to head node.

    @param : head_ref is a pointer to head node
             temp_ref is a pointer to the child2 node

    @returns pointer to the new head node, i.e child2 
*/
    Leaf * add_child2(Leaf ** head_ref, Leaf ** temp_ref){
        Leaf * head = *head_ref;
        Leaf * temp = *temp_ref;
        
        head -> child2 = temp;
        temp -> parent = head;
        head = temp;

        return head;
    }


/**
    Finds the nearest node to head which has no child1.

    @param : head_ref is a pointer to head node
             temp_ref is a pointer to the child1 node
             
    @returns pointer to the new head node, i.e child1 
*/
    Leaf * add_child1(Leaf ** head_ref, Leaf ** temp_ref){
        Leaf * head = *head_ref;
        Leaf * temp = *temp_ref;

        do head = head -> parent;
        while (head -> child1 != NULL);
        head -> child1 = temp;
        temp -> parent = head;
        head = temp;

        return head;
    }
};
#endif