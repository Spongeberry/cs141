#include "vector.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {

    // Test constructor
    Vector<int> intVec{1, 3, 5, 7, 9};
    Vector<double> doubleVec{1.5, 2.5, 3.5, 4.5};

    // Test copy constructor
    Vector<int> iv{intVec};
    Vector<double> dv{doubleVec};

    // Test overloaded << operator
    cout << "intVec: " << intVec << endl;  // Should print "intVec: (1, 3, 5, 7, 9)"
    cout << "iv: " << iv << endl;  // Should print "iv: (1, 3, 5, 7, 9)"
    cout << "doubleVec: " << doubleVec << endl;  // Should print "doubleVec: (1.5, 2.5, 3.5, 4.5)"
    cout << "dv: " << dv << endl;  // Should print "dv: (1.5, 2.5, 3.5, 4.5)"

    // Test size function
    assert(intVec.size() == 5);
    assert(doubleVec.size() == 4);

    // Test overloaded [] operator
    assert(intVec[0] == 1);
    try {
        intVec[-1];  // Should throw an error
    } catch (out_of_range &e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    // Test overloaded + operator
    Vector<int> sumVec = intVec + iv;
    cout << "sumVec: " << sumVec << endl;  // Should print "sumVec: (2, 6, 10, 14, 18)"

    // Test overloaded == and != operators
    assert(intVec == iv);
    assert(intVec != sumVec);

    // Test overloaded * operator (dot product)
    int dotProduct = intVec * iv;
    cout << "Dot product: " << dotProduct << endl;  // Should print "Dot product: 165"

    // Test overloaded = operator (assignment)
    Vector<int> assignedVec = intVec;
    assert(assignedVec == intVec);

    // Test friend function for scalar multiplication
    Vector<int> scaledVec = 2 * intVec;
    cout << "Scaled Vector: " << scaledVec << endl;  // Should print "Scaled Vector: (2, 6, 10, 14, 18)"

    // Test friend function for scalar addition
    Vector<int> addedVec = 1 + intVec;
    cout << "Added Vector: " << addedVec << endl;  // Should print "Added Vector: (2, 4, 6, 8, 10)"

    cout << "All tests passed!" << endl;

    return 0;
}
