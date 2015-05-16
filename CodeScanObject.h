#ifndef CODESCANOBJECT_H
#define CODESCANOBJECT_H

#include <string>

using namespace std;

class CodeScanObject
{
    public:
        /** Default constructor */
        CodeScanObject();
        CodeScanObject(string str);
        string code_string;

        void findNewKeyword();

        string CopyVarAfterNew(unsigned int newPosition);

        bool isLoneNew(unsigned int index);


        /** Default destructor */
        virtual ~CodeScanObject();
    protected:
    private:

};

#endif // CODESCANOBJECT_H
