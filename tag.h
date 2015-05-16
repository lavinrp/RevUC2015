#ifndef TAG_H
#define TAG_H

#include <vector>
#include <string>

using namespace std;

///  The Tag class tags a variable for trace. It takes 4 arguments, the variable's pointer, value, name, and line number.

class Tag
{
    public:
        Tag(void* tptr, string var_name,long long line);

        virtual ~Tag();

        void setVarName();

        void setVar();

        void setLines();

        string getVarName();

        //long getSize();

        long long getLines();

        void update(string var_name, long long line_number);

    protected:


    private:
        void* tptr;
        ///TODO: (anyone) find way to accurately determine size
        //long size;
        vector<string> var_names;
        vector<long long>lines;

};

#endif // TAG_H
