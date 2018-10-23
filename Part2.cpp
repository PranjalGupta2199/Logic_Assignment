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
		1. If yes, upadate the truth value of that Statement object.
			> In case of AND introduction, both the premises must be present.
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
		else if (counter == 2) line1 = stoi(temp) - 1;
		else if (counter == 3) line2 = stoi(temp) - 1;
	}
	
	void print(){
		cout << value << " " << rule << " " <<  line1 << " " << line2 << endl;
	}
	
};

bool and_intro(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index];
	
	int line1 = formula->line1;
	int line2 = formula->line2;
	
	string rule1 = proof[line1]->value;
	string rule2 = proof[line2]->value;
	
	if (formula->value != "(" + rule1 + "^" + rule2 + ")") return false;
	else if (truth_val[line1] == true && truth_val[line2] == true) return true;
	else return true;
}


bool and_el1(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index];
	
	int l1 = formula->line1;
	string sub = proof[l1]->value;
	int n1 = formula->value.length() + 2;
	
	if ("(" + formula->value + "^" + sub.substr(n1) != sub) return false;
	else if (truth_val[l1] == true) return true;
	else return false;
}

bool and_el2(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index]; 
	int l1 = formula->line1; 
	string sub = proof[l1]->value; 
	int n1 = sub.length() - 2 - formula->value.length();
	
	if (sub.substr(0,n1) + "^" + formula->value + ")" != sub) return false; 
	else if (truth_val[l1] == true) return true;
	else return false;
}
bool or_intro1(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index]; //aVb
	int l1 = formula->line1;
	
	string sub = proof[l1]->value; //a
	int n = sub.length() ; 
	
	if ("(" + sub + "V" + formula->value.substr(n+2) != formula->value) return false;
	else if (truth_val[l1] == true) return true;
	else return false;

}
bool or_intro2(vector <Statement *> proof, vector <bool> truth_val, int index) {}
bool impl_el(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index];
	
	int line1 = formula->line1;
	int line2 = formula->line2;
	
	string rule1 = proof[line1]->value;
	string rule2 = proof[line2]->value;
	
	if (truth_val[line1] == true && truth_val[line2] == true) return true;
	else return false;
}
bool MT(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index];
	
	int line1 = formula->line1;
	int line2 = formula->line2;
	
	string rule1 = proof[line1]->value;
	string rule2 = proof[line2]->value;
	
	if (truth_val[line1] == true && truth_val[line2] == false) return true;
	else return false;	
}




bool assign_rule(string rule,vector <Statement *> proof, vector <bool> truth_val, int index){
	
	if (rule == "^i") return and_intro(proof, truth_val, index);
	else if (rule == "^e1") return and_el1(proof, truth_val, index);
	else if (rule == "^e2") return and_el2(proof, truth_val, index);
	else if (rule == "Vi1") return or_intro1(proof, truth_val, index);
	else if (rule == "Vi2") return or_intro2(proof, truth_val, index);
	else if (rule == "->e") return impl_el(proof, truth_val, index);
	else if (rule == "MT") 	return MT(proof, truth_val, index);
	else return true;
}	

void check_validity(vector <Statement *> proof, vector <bool> truth_val){
	for (int i = 0; i < proof.size(); i++)
	{
		Statement *temp;
		temp = proof[i];
		
		truth_val[i] = assign_rule(temp->rule, proof, truth_val, i);
		
		if (truth_val[i] == false) {
			cout << "INVALID PROOF" << endl;
			exit(0);
		}
		else {}
	}
	cout << "VALID PROOF" << endl;
}

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
	
	check_validity(proof, truth_val);
}



































