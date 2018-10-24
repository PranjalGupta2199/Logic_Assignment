#ifndef LEAFNODE
#define LEAFNODE

#include <iostream>

#include <string>
#include <vector>
using namespace std;

/**
    \details CS F214 Assignment 2\n
    \details File : LeafNode.h
    \brief Class definitions for Leaf Node 
    
    \author  Pranjal Gupta
    \author  Abhishree Jain
    \version 1.3 
    \date 24/10/2018 
*/

class Leaf{

public :
//! \brief Will be an operator or an operand
    char value; 
//! \brief Will point to this node's parent 
    Leaf * parent; 
//! \brief Will point to left child node
    Leaf * child1; 
//! \brief Will to point to right child node
    Leaf * child2; 

    Leaf(char v){
/**
    \brief Constructor for Leaf class.\n
    Intializes all the data members.
*/
        parent = NULL;
        child1 = NULL;
        child2 = NULL;
        value = v;
    }

    Leaf * add_child2(Leaf ** head_ref, Leaf ** temp_ref){
/**
    \brief Adds a child2 node to head node.

    \param  head_ref is a pointer to head node
    \param  temp_ref is a pointer to the child2 node

    \returns pointer to the new head node, i.e child2 
*/
      
        Leaf * head = *head_ref;
        Leaf * temp = *temp_ref;
        
        head -> child2 = temp;
        temp -> parent = head;
        head = temp;

        return head;
    }



    Leaf * add_child1(Leaf ** head_ref, Leaf ** temp_ref){
/**
    \brief Finds the nearest node to head which has no child1.

    \param  head_ref is a pointer to head node
    \param  temp_ref is a pointer to the child1 node
             
    \returns pointer to the new head node, i.e child1 
*/       
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