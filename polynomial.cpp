//
//  polynomial.cpp
//  hw08 - separate compilation
//
//  Created by Yanglin Tao on 12/1/21.
//

#include "polynomial.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// function prototype
Polynomial operator+(Polynomial& lhs, Polynomial& rhs);
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);


// Polynomial class

// default constructor
Polynomial::Polynomial(): headPtr(new Node()), degree(0){}

// constructor that takes a vector of its coefficients
// in order from the highest degree term to lowest
Polynomial::Polynomial(const vector<int>& coefficients) :
degree(0), headPtr(new Node(coefficients[0])){
    Node* curr = headPtr;
    for(size_t i = 1; i < coefficients.size(); i++){
        curr -> next = new Node(coefficients[i]);
        curr = curr -> next;
        degree++;
    }
    // cleaning up leading 0's upon construction
    cleanup();
}

// method to clean up leading 0's
Polynomial& Polynomial::cleanup(){
    const Node* curr = headPtr;
    if(headPtr != nullptr){
        while(curr -> data == 0 && degree > 0){
            headPtr = headPtr -> next;
            degree --;
            curr = curr -> next;
        }
    }
    return *this;
}

// destructor
Polynomial::~Polynomial(){
    const Node* curr = headPtr;
    const Node* next;
    while(curr != nullptr){
        next = curr -> next;
        delete curr;
        curr = next;
    }
}

// copy constructor
Polynomial::Polynomial(const Polynomial& rhs){
    if(rhs.headPtr != nullptr){
        headPtr = new Node(rhs.headPtr -> data);
        degree = rhs.degree;
        const Node* curr = rhs.headPtr -> next;
        Node* last = headPtr;
        while(curr != nullptr){
            last -> next = new Node(curr -> data);
            curr = curr -> next;
            last = last -> next;
        }
    }
}

// assignment operator
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this != &rhs){
        const Node* curr = headPtr;
        const Node* next;
        while(curr != nullptr){
            next = curr -> next;
            delete curr;
            curr = next;
        }
        if(rhs.headPtr != nullptr){
            headPtr = new Node(rhs.headPtr -> data);
            degree = rhs.degree;
            const Node* curr2 = rhs.headPtr -> next;
            Node* last = headPtr;
            while(curr2 != nullptr){
                last -> next = new Node(curr2 -> data);
                curr2 = curr2 -> next;
                last = last -> next;
            }
        }
    }
    return *this;
}

// method to add to the front of linked list
void Polynomial::addFront(int data){
    headPtr = new Node(data, headPtr);
}

int Polynomial::exponentiation(int base, int power) const{
    int result = 1;
    for(size_t i = 0; i < power; i++){
        result *= base;
    }
    return result;
}

// method to evaluate polynomial
int Polynomial::evaluate(int val) const{
    int result = 0;
    const Node* curr = headPtr;
    int power = degree;
    while(curr != nullptr){
        result += curr->data * exponentiation(val, power);
        curr = curr -> next;
        power--;
    }
    return result;
}

// overload operator+=
Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    if(degree >= rhs.degree){
        Node* curr1 = headPtr;
        int traverse = degree - rhs.degree;
        for(size_t i = 0; i < traverse; i++){
            curr1 = curr1 -> next;
        }
        
        const Node* curr2 = rhs.headPtr;
        while(curr2 != nullptr){
            curr1 -> data += curr2 -> data;
            curr1 = curr1 -> next;
            curr2 = curr2 -> next;
        }
        
        cleanup();
    }
    else{
        const Node* curr1 = rhs.headPtr;
        int traverse = rhs.degree - degree;
        for(size_t i = 0; i < traverse; i++){
            addFront(0);
        }
        
        Node* curr2 = headPtr;
        while(curr2 != nullptr){
            curr2 -> data += curr1 -> data;
            curr1 = curr1 -> next;
            curr2 = curr2 -> next;
        }
        
        degree = rhs.degree;
        
        cleanup();

    }
    return *this;
}

