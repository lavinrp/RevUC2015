#include<iostream>
#include<cstring>
#include <string>
#include <vector>
#include "tag.h"
#include<dirent.h>
#include<fstream>
#include "heapRegex.h"

using namespace std;


/**@fn  IdHeap: middle man function to replace new. Dynamically allocates a version of the input variable. ...
        Tags input variable
 * @param heap_variable: the variable to be Dynamically allocated and tagged
 * @param tags: vector of tags
 * @param line_number: line number variable was created on
 * @return heap_return: pointer to variable created
*/
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

/**@fn  IdStack: Tags input variable
 * @param stack_variable: the variable to be tagged
 * @param tags: vector of tags
 * @param line_number: line number variable was created on
*/
template <class C>
void IdStack(C stack_variable, string variable_name, vector<Tag> &tags, long long line_number) {

    ///find memory location of stack variable
    auto variable_location = &stack_variable;

    ///create tag for stack variable and add it to vector of tags
    Tag stack_tag(variable_location, variable_name, line_number);
    tags.push_back(stack_tag);
}

struct FilenameEssentials{      ///struct so that we can return more than one thing because i'm uncreative
    vector<string> files;
    string path;
    vector<string> full_path;
};

struct FilenameEssentials GetFileNames(){

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

    FilenameEssentials our_files;
    our_files.files=selected_files;
    our_files.path=file_path;
    for(unsigned int k=0; k<selected_files.size(); k++){
        our_files.full_path.push_back(file_path+selected_files[k]);
    }

    for(unsigned int k=0; k<selected_files.size(); k++){
        selected_files[k]=file_path + "\\" + selected_files[k];
        cout<<selected_files[k]<<endl;
    }
    our_files.full_path=selected_files;
    return our_files;
}



vector<vector<string>> FileConverter(vector<string> selected_files){
    cout<<"Files will now be converted..."<<endl;
    string temp_line;
    vector<vector<string>> converted_files;
    vector<string> temp_file;
    for(unsigned int k=0; k<selected_files.size(); k++){  ///Copies the files contents as text and puts it in a vector.
        ifstream current_file(selected_files[k]);
        while(getline(current_file, temp_line)){
            temp_file.push_back(temp_line);
        }
        converted_files.push_back(temp_file);
    }
    return converted_files;
}


void FileOutputter(vector<vector<string>> tagged_files, FilenameEssentials file_names){
    vector<string> new_names=file_names.files;
    for(unsigned int k=0; k<new_names.size(); k++){
        new_names[k]=file_names.path+"\\_"+new_names[k];
    }
    cout<<endl<<"The following files were outputted.  Please compile them and run them to check for the location of memory leaks."<<endl;
    for(unsigned int k=0; k<new_names.size(); k++){
        ofstream new_file(new_names[k]);
        cout<<new_names[k]<<endl;
        for(unsigned int j=0; j<tagged_files[k].size(); j++){
            new_file << tagged_files[k][j]+"\n";
        }
    }
    return;
}


string SemicolonExcision(string valuables){
    valuables.pop_back();
    string treasures=valuables;
    return treasures;
}

int main() {


    ///read in files
    FilenameEssentials file_info=GetFileNames();
    vector<string> selected_files=file_info.full_path;
    vector<vector<string>> converted_files=FileConverter(selected_files);

    ///insert tags and whatnot
    ///create output file
    FileOutputter(converted_files, file_info);


    ///create tracking vectors
    vector <Tag> heapTags;

    ///parse every line of every file
    vector<variableObject> heap_strings;///store strings of heap variables
    vector<VariableInfo> InfoExtractor;

    for (vector<string> lines : converted_files) {
        for (string line : lines) {
            ///find all the new shits
            vector<VariableInfo> selected_info = FindHeapVariables(line);
        }
    }
    /*for (unsigned int i = 0; i < converted_files.size(); ++i) {
        for (unsigned int k = 0; k < (converted_files[i]).size(); ++k) {
            ///aquite alll s
            heap_strings.push_back(FindHeapVariables((converted_files[i])[k]));
        }
    }*/

    //string sample = "asdaf var v = new var(sample); asfdsg Hi Hello /n b=new bar(docte); sdfsadf";
	string sample("asdaf var v = new var(sample); \n asfdsg Hi Hello \n b=new bar(docte); sdfsadf \n var b = new bre(sample); ");


	cin.ignore();
	cin.get();

    ///return newly created pointer
    return 0;
}
