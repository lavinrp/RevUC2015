#ifndef TAG_H
#define TAG_H
#include <vector>

///  The Tag class tags a variable for trace. It takes 4 arguments, the variable's pointer, value, name, and line number.

class Tag
{
    public:
        tag(void* Tptr, string VarName,long long Line);

        virtual ~tag();

        void setVarName();

        void setVar();

        void setLine();

        string getVarName();

        long getSize();

        long long getLine();

        long long update();

    protected:


    private:
        void* Tptr;
        long Size;
        vector<string> VarName;
        vector<long long>Line;



};

#endif // TAG_H
