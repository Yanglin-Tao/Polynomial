//
//  polynomial.h
//  hw08 - separate compilation
//
//  Created by Yanglin Tao on 12/1/21.
//

#ifndef polynomial_h
#define polynomial_h

#include <string>
#include <iostream>
#include <vector>

// create a Polynomial class
class Polynomial{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    // create struct Node
    struct Node{
        Node(int data = 0, Node* next = nullptr) : data(data), next(next){}
        int data;
        Node* next;
    };
    
    // default constructor
    Polynomial();
    // constructor that takes a vector of its coefficients
    // in order from the highest degree term to lowest
    Polynomial(const std::vector<int>& coefficients);
    
    // destructor
    ~Polynomial();
    
    // copy constructor
    Polynomial(const Polynomial& rhs);
    
    // assignment operator
    Polynomial& operator=(const Polynomial& rhs);
    
    // method to evaluate polynomial
    int evaluate(int val) const;
    
    // overload operator+=
    Polynomial& operator+=(const Polynomial& rhs);
    
    // for debugging
//    size_t getDegree() const {
//        return degree;
//    }
    
private:
    Node* headPtr;
    int degree;
    
    // method to add to the front of linked list
    void addFront(int data);
    
    int exponentiation(int base, int power) const;
    
    // method to clean up leading 0's
    Polynomial& cleanup();
};


#endif /* polynomial_h */
