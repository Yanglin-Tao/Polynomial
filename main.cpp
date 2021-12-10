//
//  main.cpp
//  hw08 - separate compilation
//
//  Created by Yanglin Tao on 12/9/21.
//

#include <iostream>
#include "polynomial.h"
#include <string>
#include <vector>

using namespace std;

void doNothing(Polynomial temp) {}

// outside of Polynomial class

// overload operator+
Polynomial operator+(Polynomial& lhs, Polynomial& rhs){
    Polynomial result(lhs);
    return result += rhs;
}

// overload operator==
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if(lhs.degree == rhs.degree){
        bool done = true;
        const Polynomial::Node* currLhs = lhs.headPtr;
        const Polynomial::Node* currRhs = rhs.headPtr;
        while(currLhs != nullptr && currRhs != nullptr){
            if(currLhs -> data != currRhs -> data){
                done = false;
            }
            currLhs = currLhs -> next;
            currRhs = currRhs -> next;
        }
        if(done == true){
            return true;
        }
    }
    return false;
}

// overload operator !=
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

// output operator for polynomial class
ostream& operator<<(ostream& os, const Polynomial& rhs){
    const Polynomial::Node* curr = rhs.headPtr;
    int power = rhs.degree;
    while(curr != nullptr && power > 0){
        if(curr -> data != 0){
            if(power > 1 && curr -> data != 1){
                os << curr -> data << "x^" << power << " + ";
            }
            else if(power > 1 && curr -> data == 1){
                os << "x^" << power << " + ";
            }
            else if(power == 1 && curr -> data != 1){
                os << curr -> data << "x" << " + ";
            }
            else if(power == 1 && curr -> data == 1){
                os << "x" << " + ";
            }
        }
        curr = curr -> next;
        power--;
    }
    os << curr -> data;
    return os;
}


int main() {
    
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;
    
    //    cerr << "displaying polynomials\n";
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;

    // Polynomial temp;
    // temp = p2 + p3;
    // cout << "temp: " << temp << endl;
    
    cout << "p2 + p3: " << (p2+p3) << endl;
    cout << "p2 + p4: " << (p2+p4) << endl;
    cout << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
    
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    /*=================================================================
    NEW TEST CODE - test if cleaning the leading 0s
    ===================================================================*/

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()
    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;

    
}



