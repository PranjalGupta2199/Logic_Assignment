#include <iostream>
#include <string>
using namespace std;

class Leaf
{
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
}

int main()
{
	string postfix;
	getline(cin, postfix);
	
	Leaf * head = NULL; 
	
	for (int i = postfix.length() - 1, i >= 0; i--)
	{
		Leaf temp = Leaf(postfix[i]);
		switch (postfix[i]) 
		{
			case('V') :
			case('^') :
			case('~') :
			case('>') :
				if (head == NULL){
					head = &temp;
				}
				else {
					if(head.value != 'V' || head.value != '^' || head.value != '~' || head.value != '>') {
						head = head.parent;
						head.child1 = &temp;
						temp.parent = head;
						head = &temp;
					
					}
					else {
						head.child2 = &temp;
						temp.parent = head;
						head = &temp;
						temp.flag = 1;
					}
				}
				break;
			default :
				if (head.parent == NULL)
				{
					head.child2 = &temp;
					temp.parent = head;
					head = &temp;
					//temp.flag = 1;			
				}
				else if (head.value == 'V' || head.value == '^' || head.value == '>' || head.value == '~')
				{
					head.child2 = &temp;
					temp.parent = head;
					head = temp;
				}
				else 
				{
					head = head.parent;
					head.child1 = &temp;
					temp.parent = head.child1;
					head = child1;
				}
				break;
		}
	}

}
