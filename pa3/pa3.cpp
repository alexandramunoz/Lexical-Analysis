//
//  pa3.cpp
//  pa3
//
//  Created by Alexandra Munoz on 4/7/16.
//  Copyright © 2016 Alexandra Munoz. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "pa3.h"

using namespace std;

//What will be used to compare file's contents to to find delimiters and operators

const string delimiters[] = {";",","};
const string operators[] = {"+","-","*","/","++","="};

//declare booleans used when finding operators and delimiters

bool hasSemicolon;
bool hasComma;
bool hasOnePlus;
bool hasMinus;
bool hasStar;
bool hasSlash;
bool hasTwoPlus;
bool hasEqual;


int main(int argc, char * argv[]) {
    //Checks to determine whether user correctly inputted arguments to run the program
    if (argc > 2){
        cout<<"You have entered more than 2 arguments when only 2 are allowed.\n";
        return 0;
    }
    if(argc < 2){
        cout<<"You have entered less than 2 arguments when 2 are needed.\n";
        return 0;
    }
//Strings for delimiters and operators
    string delimiters;
    string operators;

//Linked list of words in file
    LinkedList * llStack = new LinkedList();
//Linked list of "FOR" in file
    LinkedList* forStack = new LinkedList();
//Read in file
    ifstream file2;
    string line;
    file2.open(argv[1], ios::in);
    if(file2.is_open()){
        while(file2.good()){
//Max number of characters per line
            char buf[512];
//Read in lines in file
            file2.getline(buf,512);
            int n = 0;
//Tokenize file's contents(get tokens of everything besides white space, delimiters, and operators)
            const char* tokens[20] = {};
            tokens[0]=strtok(buf," ()+-*/+=;,");
            if(tokens[0]){
                for(n = 1; n < 20; n++){
                    tokens[n] = strtok(0," ()+-*/+=;,");
                    if(!tokens[n])
                        break;
                }
            }
//Put tokens inside of linked list
            for(int i = 0; i < n; i++){
                llStack->push(tokens[i]);
             //   cout<<tokens[i]<<endl;
            }
        }
        file2.close();
    }
    
//Read in file
    ifstream file;
    file.open(argv[1], ios::in);
    
//Initialize booleans
    
    hasSemicolon = false;
    hasComma = false;
    hasOnePlus = false;
    hasMinus = false;
    hasStar = false;
    hasSlash = false;
    hasTwoPlus = false;
    hasEqual = false;
    
    if (file.is_open()){
//Read in lines of file
        while(getline(file,line)){
//Read every character of each line
            for(int i = 0; i < static_cast<int>(line.size()); i++){
                char charCheck = line.at(i);
//Check for semicolons
                if(!hasSemicolon && charCheck == ';'){
                    hasSemicolon = true;
//Add semicolon to delimiter string
                    delimiters += charCheck;
                    delimiters += " ";
                }
//Check for commas
                if(!hasComma && charCheck == ','){
                    hasComma = true;
//Add comma to delimiter string
                    delimiters += charCheck;
                    delimiters += " ";
                }
//Check for one and two plus signs
                if(!hasOnePlus && charCheck == '+'){
//If next char is also a plus sign
                    if(!hasTwoPlus && line.at(i+1) == '+'){
                        hasTwoPlus = true;
//Add ++ to operator string
                        operators += charCheck;
                        operators += charCheck;
                        operators += " ";
                    }
                    else{
//If only one plus sign
                        hasOnePlus = true;
//Add + to operator string
                        operators += charCheck;
                        operators += " ";
                    }
                }
//Check for minus sign
                if(!hasMinus && charCheck == '-'){
                    hasMinus = true;
//Add minus sign to operators string
                    operators += charCheck;
                    operators += " ";
                }
//Check for * symbol
                if(!hasStar && charCheck == '*'){
                    hasStar = true;
//Add * to operators string
                    operators += charCheck;
                    operators += " ";
                }
//Check for forward slash
                if(!hasSlash && charCheck == '/'){
                    hasSlash = true;
//Add / to operators string
                    operators += charCheck;
                    operators += " ";
                }
//Check for equals sign
                if(!hasEqual && charCheck == '='){
                    hasEqual = true;
//Add = to operators string
                    operators += charCheck;
                    operators += " ";
                }
                
            }
            
        }
    }
//If file can't open
    else{
        cout<<"Could not open file\n";
    }
    file.close();
//Initialize number of nested loops
    int nestedLoopsCount = 0;
//Find keywords
    cout<<"Keywords: ";
//Call linked list method to search for keyword FOR
    int forCount = llStack->look("FOR");
//Add every FOR found to a linked list of FORs in file
    for(int i = 0; i < forCount; i++){
        forStack->push("FOR");
    }
//Call linked list method to search for keyword BEGIN
    llStack->look("BEGIN");
//Call linked list method to search for keyword END
    int endCount = llStack->look("END");
//If less than or equal to the number of FOR ENDs are found
    if(endCount <= forCount){
        for(int i = 0; i < endCount; i++){
//Pop a FOR from the linked list every time END is found
            forStack->pop();
        }
        nestedLoopsCount = endCount;
    }
//If more END is found than FOR, pop every FOR, but only the number of FORs is the nested loop count because this is the max count
    if(endCount > forCount){
        for(int i = 0; i <forCount; i++){
            forStack->pop();
        }
        nestedLoopsCount = forCount;
    }
//Call linked list method to search for and print identifiers
    cout<<endl; cout<<"Identifier: "; llStack->identifiers(); cout<<endl;
//Call linked list method to search for and print constants
    cout<<"Constant: "; llStack->constants(); cout<<endl;
//Print out string of operators
    cout<<"Operators: "; cout<<operators; cout<<endl;
//Print out string of delimiters
    cout<<"Delimiter: "; cout<<delimiters; cout<<endl;
////Call linked list method to search for and print errors
    cout<<"Syntax Error(s): "; llStack->errors(); cout<<endl;
//Print out number of nested loops
    cout<<endl; cout<<"The maximum depth of nested loop(s) is "; cout<<nestedLoopsCount; cout<< endl; cout<<endl;
    return 0;
}