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
    }
};

Leaf * head = NULL;
int main()
{
    string postfix;
    getline(cin, postfix);
    
    
    for (int i = postfix.length() - 1; i >= 0; i--)
    {
        Leaf* temp;
        temp = new Leaf(postfix[i]);

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
    /*
    cout<<"\n\n";
    while(head != NULL){
        cout<<head -> value;
        head = head -> parent;
    }
	*/
}
