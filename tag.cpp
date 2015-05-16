#include "tag.h"

Tag::Tag(void* Tptr,string Varname, long long Linenumber) {

            this -> Tptr = Tptr;

            Size = sizeof(&Tptr);

            VarName.push_back(Varname);

            Line.push_back(Linenumber);  //ctor

}

Tag::~Tag() {

    Tptr = NULL;    //dtor
}

void Tag::update(string Varname, long long Linenumber) {

    Size = sizeof(&Tptr);

    VarName.push_back(Varname);

    Line.push_back(Linenumber);
}
