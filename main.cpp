#include<iostream>
#include <string>
#include <vector>
#include "tag.h"
#include "testClass.h"

using namespace std;

template <class C>
C* IdHeap(C heapVariable, string variableName,vector<Tag> tags, long long lineNumber) {

    /// create the variable on the heap with a copy constructor
    C* heapReturn = new C(heapVariable);

    auto variableLocation = &(*heapReturn);

    ///create a tag for the variable
    Tag heapTag(variableLocation, variableName, lineNumber);

    ///return newly created pointer
    return heapReturn;
}

int main() {


    return 0;
}
