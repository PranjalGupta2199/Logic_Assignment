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

	Algorithm : 
	Make a object (statement) with value, rule, line1, line2 and its truth value
	
	Assign each premise a truth value : 
		1. T in case of premise 
		2. False in case of any other premise. 
	
	Then check iteratively, whether any non-premise ith statement (2 <= i <= n) 
	can be derived from any of it's previous statements.
		1. If yes, upadate the truth value of that Statement object.
			> In case of AND introduction, both the premises must be present and truth val must be true.
			> In case of AND elimination, a new premise object will be created.
			> In case of OR introduction, first check if either of one them is true, then make another
				premise object and assign T as it's truth value.
			> In case of IMPLICATION elimination, check if the antecedent is true, then make a new premise 
				and assign T as it's truth value. 
			 	
		2. Else, break the loop and print "Invalid Proof" and exit.
		
	[End of FOR loop] print "Valid Proof"
*/


class Statement{
/*
	This is a class for all the statements that you enter in 
	the proof.
	
	Data Members : 
		value : string
			The formula which is either a premise or a statement 
			derived from other statements
		rule : string
			The rule used to derive the value (data member) of the 
			statement. Allowed values are given in the definitions
		line1 : int
			The first line number of the statement in the proof from which 
			this statement is being derived
		line2 : int
			The second line number of the statement in the proof from which 
			this statement is being derived
			
*/

public :
	string value;
	string rule;
	int line1 = 0;
	int line2 = 0;
	
	Statement(string s) {
	/*
		Constructor of Statement class
		Intialises all the data members
	*/
		split(s);
	}
		

	void split(string s) {
	/*
		Splits the param and assigns value to the data members of the object
		Param : 
			s : string
			 	A line in the proof rules
	*/
		int counter = 0;
		string temp;
		for (int i = 0; i < s.length(); i++){
		// add the character while '/' is not encountered
			if (s[i] != '/') temp += s[i]; 
			else {
			// assign values to data members
				assign(counter, temp);
				counter ++;
				temp = s[i+1];
				i++;
			}
		}
		assign(counter, temp);	
		// assign value to remaining string
	}
	
	void assign(int counter, string temp){
	/*
		Input is of the form : 
			<statement>/<rule>[ /line1[ /line2 ]]
counter: 		0		 1 		 2			3
	*/
		if (counter == 0) value = temp;
		else if (counter == 1) rule = temp;
		else if (counter == 2) line1 = stoi(temp) - 1;
		else if (counter == 3) line2 = stoi(temp) - 1;
	}
	
	void print(){
	/*
		Prints all the values of the data members
	*/
		cout << value << " " << rule << " " <<  line1 << " " << line2 << endl;
	}
	
};

bool and_intro(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index];
	
	int line1 = formula->line1;
	int line2 = formula->line2;
	
	string rule1 = proof[line1]->value;
	string rule2 = proof[line2]->value;
	
	// checks whether the statement can be derived from other statement 
	// at line1 and line2
	if (formula->value != "(" + rule1 + "^" + rule2 + ")") return false;
	// Then check the truth value of those statements. For AND introduction, 
	// both the statements have to be true
	else if (truth_val[line1] == true && truth_val[line2] == true) return true;
	else return false;
}


bool and_el1(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index];
	
	int l1 = formula->line1;
	int n1 = formula->value.length() + 2;

	string sub = proof[l1]->value;

	// checks whether the statement can be derived from other statement 
	// at line1 and line2	
	if ("(" + formula->value + "^" + sub.substr(n1) != sub) return false;
	// Then check the truth value of statement at line1. If it's true then,
	// and of formula and line1 statement is true. return true
	else if (truth_val[l1] == true) return true;
	else return false;
}

bool and_el2(vector <Statement *> proof, vector <bool> truth_val, int index){
	Statement * formula = proof[index]; 
	int l1 = formula->line1; 
	
	string sub = proof[l1]->value; 
	int n1 = sub.length() - 2 - formula->value.length();

	// checks whether the statement can be derived from other statement 
	// at line1 and line2		
	if (sub.substr(0,n1) + "^" + formula->value + ")" != sub) return false;
	// Then check the truth value of statement at line1. If it's true then,
	// and of formula and line1 statement is true. return true
	else if (truth_val[l1] == true) return true;
	else return false;
}
bool or_intro1(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index]; 
	int l1 = formula->line1;
	
	string sub = proof[l1]->value; 
	int n = sub.length() ; 

	// checks whether the statement can be derived from other statement 
	// at line1 and line2
	if ("(" + sub + "V" + formula->value.substr(n+2) != formula->value) return false;
	// Then check the truth value of statement at line1. If it's true then,
	// or of formula and line1 statement is true. return true
	else if (truth_val[l1] == true) return true;
	else return false;

}
bool or_intro2(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index];
	
	int l1 = formula->line1;
	int f_length = formula->value.length();
	string sub = proof[l1]->value; 
	int n = sub.length() ; 

	// checks whether the statement can be derived from other statement 
	// at line1 and line2	
	if ("V" + sub + ")" != formula->value.substr(f_length - n -2)) return false;
	// Then check the truth value of statement at line1. If it's true then,
	// or of formula and line1 statement is true. return true
	else if (truth_val[l1] == true) return true;
	else return false;

}
bool impl_el(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index];
	int l1 = formula->line1;
	int l2 = formula->line2;

	// checks whether the statement can be derived from other statement 
	// at line1 and line2	
	if ("(" + proof[l2]->value + "->" + formula->value + ")" != proof[l1]->value) return false;
	// if the implication and the antecedent both are true, then the 
	// consequent is also true
	else if (truth_val[l1] == true && truth_val[l2] == true) return true;
	else return false;
}
bool MT(vector <Statement *> proof, vector <bool> truth_val, int index) {
	Statement * formula = proof[index];
	int l1 = formula->line1;
	int l2 = formula->line2;
	
	// checks whether the statement can be derived from other statement 
	// at line1 and line2	
	if ("(" + formula->value.substr(1) + "->" + proof[l2]->value.substr(1) + ")" != proof[l1]->value) return false;
	// Then check if the implication is true and negation of consequent is true
	// then negation of antecedent must be true.
	else if (truth_val[l1] == true && truth_val[l2] == true) return true;
	else return false;
}




bool assign_rule(string rule,vector <Statement *> proof, vector <bool> truth_val, int index){
	/*
		Check for which rule is being used and call that function
	*/
	if (rule == "P") return true;
	else if (rule == "^i") return and_intro(proof, truth_val, index);
	else if (rule == "^e1") return and_el1(proof, truth_val, index);
	else if (rule == "^e2") return and_el2(proof, truth_val, index);
	else if (rule == "Vi1") return or_intro1(proof, truth_val, index);
	else if (rule == "Vi2") return or_intro2(proof, truth_val, index);
	else if (rule == "->e") return impl_el(proof, truth_val, index);
	else if (rule == "MT") 	return MT(proof, truth_val, index);
	else return false; // if no matching rules, return false
}	

void check_validity(vector <Statement *> proof, vector <bool> truth_val){
	/*
		Iterate through all the statements and check their truth value.
		If anyone of them becomes false after evaluation from its constituents,
		then the proof becomes INVALID.
		Else the proof is VALID, if there is no statement which becomes
		false after evaluation from its constituents 
	*/
	
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

void prompt(){
/*
	Calls other functions of proof rules and validity check
*/
	int n; // number of lines in the proof
	string s; // string containing the input
	Statement *t; // pointer to statement object
	
	vector <Statement *> proof; 
	vector <bool> truth_val;
	
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> s;	
		t = new Statement(s);
		
		proof.push_back(t);
		
		// assign truth_val as 'true' in case of premise 
		// else 'false' for all other statements
		if (t -> rule == "P") truth_val.push_back(true);
		else truth_val.push_back(false);
	}
	
	// check the validity of the proof
	check_validity(proof, truth_val);
}

int main(){
	prompt();
}


