#include <iostream>

#include <vector>
#include <string>

#include "ProofRules.h"
using namespace std;

/**

    \brief Purpose : Check whether the given the proof is valid or not

*/


void check_validity(vector <Statement *> proof, vector <bool> truth_val){
/**
    \detail Iterate through all the statements and check their truth value.
    If anyone of them becomes false after evaluation then the proof becomes INVALID.
    Else the proof is VALID, if there is no statement which becomes
    false after evaluation 
*/   
    Rules *t;
    t = new Rules(); 
    for (int i = 0; i < proof.size(); i++){
        Statement *temp;
        temp = proof[i];
        truth_val[i] = t->assign_rule(temp->rule, proof, truth_val, i);
        
        if (truth_val[i] == false) {
            cout << endl << "INVALID PROOF" << endl;
            exit(0);
        } else {}
    }
    cout << endl << "VALID PROOF" << endl;
}



void prompt(){
/**
    \brief Calls other functions of proof rules and validity check
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
