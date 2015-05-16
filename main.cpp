#include<iostream>
#include<cstring>
#include <string>
#include <vector>
#include "tag.h"
#include<dirent.h>
#include<fstream>

using namespace std;

template <class C>
C* IdHeap(C heapVariable, string variableName,vector<Tag> tags, long long lineNumber) {

    /// create the variable on the heap with a copy constructor
    C* heapReturn = new C(heapVariable);

    auto variableLocation = &(*heapReturn);

    ///create a tag for the variable
    Tag heapTag(variableLocation, variableName, lineNumber);

}

vector<string> GetFileNames(){

    ///FINDS THE FILES TO BE PROCESSED///
    string file_path;
    cout<<"Please enter the path of the folder with the files: ";  ///obtain the filepath from user
    cin>>file_path;
    const char* temp_path=file_path.c_str();    ///convert string to c_string because it doesn't work otherwise.
    DIR *dir;  ///using DIR magic from dirent.h library
    struct dirent *ent;
    vector<string> file_names;    ///List of files in a directory
    vector<string> selected_files;      ///List of files selected to be converted.
    if((dir= opendir(temp_path)) != NULL){    ///if there is anything in the directory (if it exists)
        cout<<"Files from "<<file_path<<":"<<endl;
        while((ent=readdir(dir)) != NULL){      ///print out the file names.
            string temp_name(ent->d_name);
            file_names.push_back(temp_name);
            cout<<" "<<ent->d_name<<endl;
        }
        cout<<"Please select files to be included when prompted. Only .h and .cpp files.  [y/n]"<<endl;
        string response;    ///y or n response from prompt
        for(unsigned int k=0; k<file_names.size(); k++){
            cout<<file_names[k]<<": ";
            cin>>response;
            while(response!="y" && response!="n"){
                cout<<"please enter whether to include the file.  Enter y for yes or n for no: ";
                cin>>response;
            }
            if(response=="y"){
                selected_files.push_back(file_names[k]);    //puts files selected into a vector
            }
        }

        cout<<"-------------"<<endl;
        closedir(dir);      ///close the directory (which also cleans up memory leaks from *ent and *dir.
    }
    else{       ///prints error
        cout<<"Unable to open directory."<<endl;
    }
    ///concatenates the file names to the ends of the path to the folder

    for(unsigned int k=0; k<selected_files.size(); k++){
        selected_files[k]=file_path + "\\" + selected_files[k];
        cout<<selected_files[k]<<endl;
    }
    return selected_files;
}



vector<vector<string>> FileConverter(vector<string> selected_files){
    cout<<"Files will now be converted"<<endl;
    string temp_line;
    vector<vector<string>> converted_files;
    vector<string> temp_file;
    for(unsigned int k=0; k<selected_files.size(); k++){
        ifstream current_file(selected_files[k]);
        while(getline(current_file, temp_line)){
            temp_file.push_back(temp_line);
        }
        converted_files.push_back(temp_file);
    }
    return converted_files;
}


void FileOutputter(vector<vector<string>> converted_files){
}



int main() {


    ///return newly created pointer
    return heapReturn;
}
