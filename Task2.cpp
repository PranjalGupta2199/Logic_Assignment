#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
	Input : Postfix string
	
	Output : The infix expression after performing in-order traversal of the tree formed.
	
	Definitions : 
		Symbols for operators ::=  ~ <negation> | ^ <AND> | V <OR> | > <implication>

	in-order traversal :    
	1. Traverse the left subtree, i.e., call Inorder(left-subtree)
   	2. Visit the root.
   	3. Traverse the right subtree, i.e., call Inorder(right-subtree)
	
	
	postfix_to_binary_tree : 
	 
	Input the given the postfix expression.
	Then iterate from the last character of the string, making a new node for each character you parse.
		1. If the character to be added is an operator : 
		  	> If the there is no root node, then make the temp node as root. This will happen only happen when the 
				character is an operator (as the root node will only be an operator)
			> Check the last node added : 
				>> If it's an operator, then add the current node to it's child2.
				>> Else (i.e when the character is an operand) find that node just above the last node added 
					which has an empty child1. Then add this temp as child1
		2. Else if the character to be added is an operand,
			> If the last node added is the root, then add the current node as it's child2/
			> Check the last node added : 
				>> If it was an operator, then add temp node as it's child2.
				>> Else, find that parent of the last node which has an empty child1. Add the current operator as it's 
					child1.
	[end of FOR loop] 
		
*/ 
 

class Leaf
{
/*
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

public :
    char value;
    Leaf * parent;
    Leaf * child1;
    Leaf * child2;

    Leaf(char v){
    /*
    	Constructor for Leaf class
    	Intializes all the data members.
    */
        parent = NULL;
        child1 = NULL;
        child2 = NULL;
        value = v;
    }
};

void in_order(Leaf *head_ref)
{
	/*
		Param : Leaf * ptr
		 	Pointer to the root node of the parse tree
		Precondition : Input must be a pointer of Leaf type pointing to the root node 
					   of the binary tree
		Postcondition : Prints the fully parenthesized infix expression by performing 
					  sthe in-order traversal of the binary tree
	*/

	if (head_ref->child1 != NULL && head_ref->child2 != NULL)
	{
		cout << "(";
		in_order(head_ref->child1); // traverse the left sub-tree
		cout << " " << head_ref->value << " "; // print the root node
		in_order(head_ref->child2); // traverse the right sub-tree
		cout << ")"; 		
		return;
	}
	else {
		if(head_ref->value == '\0') return; // The left node of negation operator is assigned this value
		else cout << head_ref->value; // Prints the operand
		return;
	}
}


void postfix_to_binary_tree()
{
	/*
		Precondition:  The input must be a correct postfix expression
		Postcondition: Prints the infix expression of the given postfix by forming a binary tree
	*/

    string postfix;
    getline(cin, postfix);
    
    Leaf * root = NULL; // top node in the parse tree
    Leaf * head = NULL; // node which moves along the tree while adding new nodes 
    for (int i = postfix.length() - 1; i >= 0; i--)
    {
    	// creating new instance of Leaf class
        Leaf* temp;
        temp = new Leaf(postfix[i]);
		
		if (temp->value == '~') {
		// Negation, by default will always have it's child1 having the value
		// '\0'. The next node will be added to it's child2
			Leaf *t;
			t = new Leaf('\0');
			temp-> child1 = t;
		}
        
        switch (postfix[i]) 
        {
       	// If the character is an operator
            case('V') :
            case('^') :
            case('~') :
            case('>') :
                if (head == NULL){
                // tree is empty
                	root = temp;
                    head = temp;       
                }
                else if(head->value == 'V' || head->value == '^' || head->value == '~' || head->value == '>') {
                // Adding a operator as child2 to head
                  	head->child2 = temp;
                    temp->parent = head;
                    head = temp;           
                    }
                else {
                // finding the nearest node which has a NULL child1
                    do head = head->parent;
                    while (head->child1 != NULL);

                    head->child1 = temp;
                    temp->parent = head;
                    head = temp;
                }
                break;
            default :
                if (head->parent == NULL)
                {
                // If the tree has only one node, i.e root
                    head->child2 = temp;
                    temp->parent = head;
                    head = head->child2;
                }
                else if (head->value == 'V' || head->value == '^' || head->value == '>' || head->value == '~')
                {
                // Adding operand under a operator
                    head->child2 = temp;
                    temp->parent = head;
                    head = temp;
                }
                else 
                {
                // Finding the nearest node which has a NULL child1
                    do head = head->parent;
                    while (head->child1 != NULL);
                    head->child1 = temp;
                    temp->parent = head;
                    head = temp;
                }
                break;
        }
	}
	in_order(root);  // calls in-order traversal function
	cout << endl; 
}

int main(){
	postfix_to_binary_tree();
}
