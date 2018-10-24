#ifndef PROOFRULES
#define PROOFRULES

#include <iostream>

#include <vector>
#include <string>
using namespace std;

/**
    CS-F214 Asn 2
    ProofRules.h
    Purpose : Rules which are applied on formula

    @author Pranjal Gupta
            Abhishree Jain
    @version 1.1 24/10/2018
*/


/**
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
class Statement{

public :
    string value;
    string rule;
    int line1 = 0;
    int line2 = 0;

/**
    Constructor of Statement class
    Intialises all the data members
*/  
    Statement(string s) {

        split(s);
    }

        
/**
    Splits the param and assigns value to the data members of the object
    @param[in] : statement of the proof
*/
    void split(string s) {
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


/**
    Input is of the form : 
        <statement>/<rule>[ /line1[ /line2 ]]
*/  
    void assign(int counter, string temp){
        if (counter == 0) value = temp;
        else if (counter == 1) rule = temp;
        else if (counter == 2) line1 = stoi(temp) - 1;
        else if (counter == 3) line2 = stoi(temp) - 1;
    }


/**
    Prints all the values of the data members
*/  
    void print(){
    cout << value << " " << rule << " " <<  line1 << " " << line2 << endl;
    }
    
};


bool and_intro(vector <Statement *> proof, vector <bool> truth_val, int index){
    Statement * formula = proof[index];
    
    int line1 = formula -> line1;
    int line2 = formula -> line2;
    
    string rule1 = proof[line1] -> value;
    string rule2 = proof[line2] -> value;
    
    // checks whether the statement can be derived from other statement 
    // at line1 and line2
    if (formula -> value != "(" + rule1 + "^" + rule2 + ")") return false;
    else if (truth_val[line1] == true && truth_val[line2] == true) return true;
    else return false;
}


bool and_el1(vector <Statement *> proof, vector <bool> truth_val, int index){
    Statement * formula = proof[index];
    
    int l1 = formula -> line1;
    int n1 = formula -> value.length() + 2;

    string sub = proof[l1] -> value;

    // checks whether the statement can be derived from other statement 
    // at line1 and line2   
    if ("(" + formula -> value + "^" + sub.substr(n1) != sub) return false;
    else if (truth_val[l1] == true) return true;
    else return false;
}


bool and_el2(vector <Statement *> proof, vector <bool> truth_val, int index){
    Statement * formula = proof[index]; 
    int l1 = formula -> line1; 
    
    string sub = proof[l1] -> value; 
    int n1 = sub.length() - 2 - formula -> value.length();

    // checks whether the statement can be derived from other statement 
    // at line1 and line2       
    if (sub.substr(0,n1) + "^" + formula -> value + ")" != sub) return false;
    else if (truth_val[l1] == true) return true;
    else return false;
}


bool or_intro1(vector <Statement *> proof, vector <bool> truth_val, int index) {
    Statement * formula = proof[index]; 
    int l1 = formula -> line1;
    
    string sub = proof[l1] -> value; 
    int n = sub.length() ; 

    // checks whether the statement can be derived from other statement 
    // at line1 and line2
    if ("(" + sub + "V" + formula -> value.substr(n+2) != formula -> value) return false;
    else if (truth_val[l1] == true) return true;
    else return false;

}


bool or_intro2(vector <Statement *> proof, vector <bool> truth_val, int index) {
    Statement * formula = proof[index];
    
    int l1 = formula -> line1;
    int f_length = formula -> value.length();
    string sub = proof[l1] -> value; 
    int n = sub.length() ; 

    // checks whether the statement can be derived from other statement 
    // at line1 and line2   
    if ("V" + sub + ")" != formula -> value.substr(f_length - n -2)) return false;
    else if (truth_val[l1] == true) return true;
    else return false;

}


bool impl_el(vector <Statement *> proof, vector <bool> truth_val, int index) {
    Statement * formula = proof[index];
    int l1 = formula -> line1;
    int l2 = formula -> line2;

    // checks whether the statement can be derived from other statement 
    // at line1 and line2   
    if ("(" + proof[l2] -> value + " -> " + formula -> value + ")" != proof[l1] -> value) return false;
    else if (truth_val[l1] == true && truth_val[l2] == true) return true;
    else return false;
}


bool MT(vector <Statement *> proof, vector <bool> truth_val, int index) {
    Statement * formula = proof[index];
    int l1 = formula -> line1;
    int l2 = formula -> line2;
    
    // checks whether the statement can be derived from other statement 
    // at line1 and line2   
    if ("(" + formula -> value.substr(1) + " -> " + proof[l2] -> value.substr(1) + ")" != proof[l1] -> value) return false;
    else if (truth_val[l1] == true && truth_val[l2] == true) return true;
    else return false;
}


/**
    Check for which rule is being used and call that function
*/
bool assign_rule(string rule,vector <Statement *> proof, vector <bool> truth_val, int index){
    if (rule == "P") return true;
    else if (rule == "^i") return and_intro(proof, truth_val, index);
    else if (rule == "^e1") return and_el1(proof, truth_val, index);
    else if (rule == "^e2") return and_el2(proof, truth_val, index);
    else if (rule == "Vi1") return or_intro1(proof, truth_val, index);
    else if (rule == "Vi2") return or_intro2(proof, truth_val, index);
    else if (rule == " -> e") return impl_el(proof, truth_val, index);
    else if (rule == "MT")  return MT(proof, truth_val, index);
    else return false; // if no matching rules, return false
} 

#endif
