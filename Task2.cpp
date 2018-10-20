#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
class Leaf
{
public :
    char value;
    Leaf * parent;
    Leaf * child1;
    Leaf * child2;
    int flag;

    Leaf(char v)
    {
        parent = NULL;
        child1 = NULL;
        child2 = NULL;
        value = v;
    	flag = 0;
    }
};

void in_order (Leaf * head_ref)
{
	/*
		If it is a node with a subtree beneath it, go to the leftmost node 
		and call the function, print the node and call the function on the right node
		
		else print the node and return (because it is an operand)
	
		replace the pointer with it's parent and then call the function again
		
		if the parent is null, then return to main thread
	*/
	
	if (head_ref == NULL) return;
	
	if (head_ref->child1 != NULL && head_ref->child2 != NULL)
	{
		/*
			An operator is the node. THere may be a subtree beneath it.
		*/
		Leaf *t1, *t2;
		t1 = head_ref->child1;
		t2 = head_ref->child2;
		
		/* Going to the lowest possible and leftmost leaf in the subtree*/
		//while (t1->child1 != NULL) t1 = t1->child1;
		//while (t2->child1 != NULL) t2 = t2->child1;
		
		if (t1->flag != 1) in_order(t1);
		
		if (head_ref->flag != 1) 
		{	
			cout << head_ref->value;
			head_ref -> flag = 1;
		}
		
		if (t2->flag != 1) in_order(t2);
	}
	else {
		/*
			This is an operand. There can be no subtree beneath it. 
			Then print the value and move up the tree.
		*/
		if (head_ref->flag != 1)
		{
			cout << head_ref->value;
			head_ref -> flag = 1;
		}
		else return;
	}
	if (head_ref->parent != NULL && head_ref -> parent -> flag != 1)
	{	
		head_ref = head_ref->parent;
		in_order(head_ref);
	}
	else return;
}


int main()
{
    string postfix;
    getline(cin, postfix);
    
    Leaf * head = NULL;
    for (int i = postfix.length() - 1; i >= 0; i--)
    {
        Leaf* temp;
        temp = new Leaf(postfix[i]);
		
		if (temp->value == '~') {
			Leaf *t;
			t = new Leaf('\0');
			temp-> child1 = t;
			temp->flag = 1;
		}
        
        switch (postfix[i]) 
        {
            case('V') :
            case('^') :
            case('~') :
            case('>') :
                if (head == NULL){
                    head = temp;       
                }
                else if(head->value == 'V' || head->value == '^' || head->value == '~' || head->value == '>') {
                  	head->child2 = temp;
                    temp->parent = head;
                    head = temp;           
                    }
                else {
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
                    head->child2 = temp;
                    temp->parent = head;
                    head = head->child2;
                }
                else if (head->value == 'V' || head->value == '^' || head->value == '>' || head->value == '~')
                {
                    head->child2 = temp;
                    temp->parent = head;
                    head = temp;
                }
                else 
                {
                    do head = head->parent;
                    while (head->child1 != NULL);
                    head->child1 = temp;
                    temp->parent = head;
                    head = temp;
                }
                break;
        }
	}
	in_order(head);  
	cout << endl; 
}
