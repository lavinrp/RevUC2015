#include "CodeScanObject.h"

CodeScanObject::CodeScanObject()
{
    //ctor
}

CodeScanObject::CodeScanObject(string str)
{
    code_string = str;
}


CodeScanObject::~CodeScanObject()
{
    //dtor
}


void CodeScanObject::findNewKeyword() {
    ///search entire string
    for (unsigned int i = 0; i < code_string.length(); ++i) {
        ///find substring "new"
        unsigned int newPosition = code_string.find("new");

        if(isLoneNew(newPosition)) {
            ///code to construct the variable inside the IdHeap function
            string var_construct = CopyVarAfterNew(newPosition);

            ///replace new with IdHeap function
            code_string.replace(newPosition, + var_construct.length(), "IdHeap("+var_construct+")");
        }
    }
}


///copy constructor after new
string CodeScanObject::CopyVarAfterNew(unsigned int newPosition) {
    ///find first ';' char after the start of the constructor information
    unsigned int idx = newPosition + 3;

    for (unsigned int i = idx; i < code_string.length(); ++i) {
        if (code_string[i] == ';') {
            unsigned int cut_length = i - idx - 1;
            string copiedVar = code_string.substr(idx, cut_length);
            return copiedVar;
        }
    }
    return "";
}

///check to see if char before given index is empty
///input index of first letter of "new"
bool CodeScanObject::isLoneNew(unsigned int index) {
    index--;
    if (code_string[index + 1] == 0 || code_string[index] == ' ' || code_string[index] == '\n' || code_string[index] == '=') {
        ///move index to the end of new
        index+=4;
        if (code_string[index == 0] || code_string[index] == ' ' || code_string[index] == '\n') {
            return true;
        }
    }
    return false;
}
