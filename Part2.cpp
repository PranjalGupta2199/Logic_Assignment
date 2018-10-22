#include <iostream>
#include <vector>
#include <string>
using namespace std;


/*
	Input : n (integer)
		n lines each of the form <statement>/<rule>[ /line1[ /line2 ]]
		
	Output : Valid/Invalid proof
	
	Definitions:
	<statement> ::= p | ¬p | ¬(<statement>) | (<statement> ∧ <statement>) | (<statement> ∨ <statement>) |
	(<statement> → <statement>)
	<rule> ::= ∧i | ∧e1 | ∧e2 | ∨i1 | ∨i2 | →e |P

	Make a object (statement) with value, rule, line1, line2 and its truth value
	
	Assign each premise a truth value : 
		1. T in case of premise 
		2. False in case of any other premise. 
	
	Then check iteratively, whether any non-premise ith statement (2 <= i <= n) 
	can be derived from it's previous statements.
		1. If yes, upadate the loop and make a new statement object.
			> In case of AND introduction, no need to update in the truth table.
			> In case of AND elimination, a new premise object will be created.
			> In case of OR introduction, first check if either of one them is true, then make another
				premise object and assign T as it's truth value.
			> In case of IMPLICATION elimination, check if the antecedent is true, then make a new premise 
				and assign T as it's truth value. 
			 	
		2. Else, break the loop and print "Invalid Proof" and exit.
		
	[End of FOR loop] print "Valid Proof"
	
	To improve the efficiency, make a static array which will contain the value of all the 
	statements (string type) and another static array which will contain pointers to all the statements.
*/


// static vector <string> proof;
//	static vector <Statement> * rule_ref;
class Statement{

public :
	string value;
	string rule;
	int line1 = 0;
	int line2 = 0;
	
	Statement(string s) {split(s);}


	void split(string s) {
		int counter = 0;
		string temp;
		for (int i = 0; i < s.length(); i++){
			if (s[i] != '/') temp += s[i];
			else {
				assign(counter, temp);
				counter ++;
				temp = s[i+1];
				i++;
			}
		}
		assign(counter, temp);	
	}
	
	void assign(int counter, string temp)
	{
		if (counter == 0) value = temp;
		else if (counter == 1) rule = temp;
		else if (counter == 2) line1 = stoi(temp);
		else if (counter == 3) line2 = stoi(temp);
	}
	
	void print(){
		cout << value << " " << rule << " " <<  line1 << " " << line2 << endl;
	}
	
};

int main(){
	int n;
	string s;
	Statement *t;
	
	vector <Statement *> proof;
	vector <bool> truth_val;
	
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> s;	
		t = new Statement(s);
		
		proof.push_back(t);
		
		if (t -> rule == "P") truth_val.push_back(true);
		else truth_val.push_back(false);
	}
}



































