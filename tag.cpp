#include "tag.h"

tag::tag(void* Tptr,string Varname, long long Linenumber) {

            this -> Tptr = Tptr;

            Size = sizeof(&Tptr);

            Varname = VarName;

            Line.push_back(Linenumber);  //ctor

}

tag::~tag() {

    Tptr = NULL;    //dtor
}

tag::update(string Varname, long long Linenumber) {

    int count = 0;

    Size = sizeof(&Tptr);

    VarName.push_back(Varname);

    Line.push_back(Linenumber);


}
