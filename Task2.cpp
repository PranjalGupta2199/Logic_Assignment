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

void in_order(Leaf *head_ref)
{
	if (head_ref->child1 != NULL && head_ref->child2 != NULL)
	{
		cout << "(";
		in_order(head_ref->child1);
		cout << head_ref->value << " ";
		in_order(head_ref->child2);
		cout << ")";
		return;
	}
	else {
		if(head_ref->value == '\0') return;
		else cout << head_ref->value << " ";
		return;
	}
}


int main()
{
    string postfix;
    getline(cin, postfix);
    
    Leaf *root = NULL;
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
                	root = temp;
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
	//cout << root->value << endl;
	in_order(root);  
	cout << endl; 
}
