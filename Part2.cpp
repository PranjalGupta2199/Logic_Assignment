#include <iostream>

#include <vector>
#include <string>

#include "ProofRules.h"
using namespace std;

/**
    CS-F214 Asn 2
    Proof Checking Engine
    Purpose : Check whether the given the proof is valid or not

    @author Pranjal Gupta
            Abhishree Jain
    @version 1.1 24/10/2018
*/


/**
* Input : n (integer)
*   n lines each of the form <statement>/<rule>[ /line1[ /line2 ]]
*   
* Output : Valid/Invalid proof
*
* Definitions:
*   <statement> ::= p | ¬p | ¬(<statement>) | (<statement> ∧ <statement>) | (<statement> ∨ <statement>) |
*   (<statement> → <statement>)
*   <rule> ::= ∧i | ∧e1 | ∧e2 | ∨i1 | ∨i2 | →e |P
*
* Algorithm : 
* Make a object (statement) with value, rule, line1, line2 and its truth value
*
* Assign each premise a truth value : 
*   1. T in case of premise 
*   2. False in case of any other premise. 
*
* Then check iteratively, whether any non-premise ith statement (2 <= i <= n) 
* can be derived from any of it's previous statements.
*   1. If yes, upadate the truth value of that Statement object.
*       > In case of AND introduction, both the premises must be present and truth val must be true.
*       > In case of AND elimination, a new premise object will be created.
*       > In case of OR introduction, first check if either of one them is true, then make another
*           premise object and assign T as it's truth value.
*       > In case of IMPLICATION elimination, check if the antecedent is true, then make a new premise 
*           and assign T as it's truth value. 
*           
*   2. Else, break the loop and print "Invalid Proof" and exit.
*   
*[End of FOR loop] print "Valid Proof"
*/


/**
    Iterate through all the statements and check their truth value.
    If anyone of them becomes false after evaluation from its constituents,
    then the proof becomes INVALID.
    Else the proof is VALID, if there is no statement which becomes
    false after evaluation from its constituents 
*/
void check_validity(vector <Statement *> proof, vector <bool> truth_val){
    for (int i = 0; i < proof.size(); i++)
    {
        Statement *temp;
        temp = proof[i];
        truth_val[i] = assign_rule(temp->rule, proof, truth_val, i);
        
        if (truth_val[i] == false) {
            cout << endl << "INVALID PROOF" << endl;
            exit(0);
        } else {}
    }
    cout << endl << "VALID PROOF" << endl;
}


/*
    Calls other functions of proof rules and validity check
*/
void prompt(){
    int n; //< number of lines in the proof
    string s; //< string containing the input
    Statement *t; //< pointer to statement object
    
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
