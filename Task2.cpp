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

	if (head_ref->child1 != NULL && head_ref->child2 != NULL)
	{
		if (head_ref->child1->flag != 1) 
		{
		    cout << "(";
		    in_order(head_ref->child1);
		}
		
		if (head_ref->flag != 1) 
		{
			cout << head_ref->value;
			head_ref -> flag = 1;
		}
		
		if (head_ref->child2->flag != 1) 
		{   
		    in_order(head_ref->child2);
            cout << ")";
		}
	}
	else {
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
			temp->child1->flag = 1;
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
	cout << "(";
	in_order(head);  
	cout << endl; 
}
