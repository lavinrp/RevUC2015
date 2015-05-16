#include "tag.h"

Tag::Tag(void* tptr, string var_name, long long line_number) {

            this -> tptr = tptr;

            size = sizeof(&tptr);

            var_names.push_back(var_name);

            lines.push_back(line_number);  //ctor

}

Tag::~Tag() {

    tptr = NULL;    //dtor
}

void Tag::update(string var_name, long long line_number) {

    size = sizeof(&tptr);

    var_names.push_back(var_name);

    lines.push_back(line_number);
}
