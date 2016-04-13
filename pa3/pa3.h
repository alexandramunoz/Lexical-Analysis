//
//  pa3.h
//  pa3
//
//  Created by Alexandra Munoz on 4/11/16.
//  Copyright © 2016 Alexandra Munoz. All rights reserved.
//

#ifndef pa3_h
#define pa3_h

using namespace std;

//Node class for Linked Lists
class Node{
    
public:
    string data;
    bool nodeUsed;
    
    Node * next;
    //Node constructor
    Node(string name){
        data = name;
        next = NULL;
        nodeUsed = false;
    }
};

class LinkedList{

    
private:
    Node *head;
    
public:
    void push(string token){
        //Creates head of linked list
        if(head == NULL){
            head = new Node(token);
            return;
        }
        Node*temp = head;
        //Inserts new nodes
        while (temp -> next != NULL){
            temp = temp -> next;
        }
        temp-> next = new Node(token);
    }
//Searches for word inside of file
    int look(string word){
        int wordCount = 0;
        Node * curr = head;
//Searches nodes for word
        while(curr!=NULL){
            if(curr->data == word){
                wordCount++;
            }
            curr = curr->next;
        }
//Print out found word
        if(wordCount > 0){
        cout<<word << " ";
        }
        return wordCount;
    }
//Pop from the stack (delete last created node in linked list)
    void pop(){
        Node* toDelete = head;
        head = head->next;
        delete(toDelete);
    }
//Search for constants in file
     void constants(){
//Create linked list for constants
        LinkedList* constantsStack = new LinkedList();
        Node*temp = head;
        while(temp != NULL){
            string number = temp->data;
//Read first char of word in every node
            for(int i = 0; i < number.size();i++){
                char charCheck = number.at(i);
//If first char is a digit
                if(isdigit(charCheck)){
//Call method to be sure number hasn't already been found in file
                    if(constantsStack->repeated(number) == false)
//Add constant to linked list
                    constantsStack->push(number);
                }
            }
            temp = temp->next;
        }
//Call method to print linked list
         constantsStack->print();
    }
//Method to search for identifiers in file
    void identifiers(){
////Create linked list for identifiers
        LinkedList* identifiersStack = new LinkedList();
        Node*temp = head;
        while(temp != NULL){
            string word = temp->data;
//Read first char of word in every node
            for(int i = 0; i < word.size();i++){
                char charCheck = word.at(i);
//If first char is lowercase
                if(islower(charCheck)){
//Call method to be sure word hasn't already been found in file
                    if(identifiersStack->repeated(word) == false)
//Add identifier to linked list
                        identifiersStack->push(word);
                }
            }
            temp = temp->next;
        }
//Call method to print linked list
        identifiersStack->print();
        
    }
//Search for errors in file
    void errors(){
//Create linked list for errors
        LinkedList* errorsStack = new LinkedList();
        Node*temp = head;
        while(temp != NULL){
            string word = temp->data;
//Read first char of word in every node
            for(int i = 0; i < word.size();i++){
                char charCheck = word.at(i);
//If first char in word is uppercase
                if(isupper(charCheck)){
//If word is not keyword and hasn't already been found in file, add word to errors linked list
                    if(errorsStack->repeated(word) == false && word != "FOR" && word != "END" && word != "BEGIN")
                        errorsStack->push(word);
                }
//If char isn't uppercase, lowercase, or a digit, must be an error. So, add word to errors linked list after checking that it hasn't already been found in file
                if(!(isupper(charCheck)) && !(islower(charCheck)) && (!isdigit(charCheck))){
                    if(errorsStack->repeated(word) == false)
                        errorsStack->push(word);
                }
            }
            temp = temp->next;
        }
//Call method to print linked list
        errorsStack->print();
    }
//Method to check if word has already been found in file
    bool repeated(string wordCheck){
        bool repeated = false;
        Node*temp = head;
        while (temp != NULL){
//Compare word to other words in file
            if(temp->data == wordCheck){
                repeated = true;
            }
            temp = temp->next;
        }
        return repeated;
    }
//Method to print a linked list
    void print(){
    string free = "free";
    Node * temp = head;
    int nodeCount = 0;
    while(temp != NULL){
//Print name of nodes (type of token)
                cout<< temp->data <<" ";
                temp = temp -> next;
                nodeCount++;
            }
    }
};

#endif /* pa3_h */
