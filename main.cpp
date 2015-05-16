#include<iostream>
#include <string>
#include <vector>
#include "tag.h"
#include "testClass.h"

using namespace std;

template <class C>
C* IdHeap(C heap_variable, string variable_name, vector<Tag> &tags, long long line_number) {

    /// create the variable on the heap with a copy constructor
    C* heap_return = new C(heap_variable);

    /// find memory address of variable
    auto variable_location = &(*heap_return);

    ///create a tag for the variable and add it to vector of tags
    Tag heap_tag(variable_location, variable_name, line_number);
    tags.push_back(heap_tag);

    ///return newly created pointer
    return heap_return;
}

template <class C>
void IdStack(C stack_variable, string variable_name, vector<Tag> &tags, long long line_number) {

    ///find memory location of stack variable
    auto variable_location = &stack_variable;

    ///create tag for stack variable and add it to vector of tags
    Tag stack_tag(variable_location, variable_name, line_number);
    tags.push_back(stack_tag);
}

int main() {


    return 0;
}
