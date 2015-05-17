#include <iostream>
#include <regex>
#include <string>
using namespace std;


/*Object which will hold each variable segment(eg. new var(stuff) and the position of the first character
of each variable segment minus 1 )
*/
class variableObject{

public:

	//string constructor
	variableObject(string variableString, long variableLocation){
		this->variableString = variableString;

		this->variableLocation = variableLocation;
	}

	string getVariableString(){
		return variableString;
	}

	long getVariableLocation(){
		return variableLocation;
	}

	void set(){
		variableObject(variableString, variableLocation);
	}


private:
	string variableString;

	long variableLocation;
};

struct VariableInfo{
    string variable_type;
    string variable_name;
    string ConstructorStuff;
    long long line_number;
};

vector<VariableInfo> InfoExtractor(vector<variableObject> ObjectCaravan){
    vector<VariableInfo> var_info;
    VariableInfo temp_data;

    ///find variable name
    for(unsigned int k=0; k<ObjectCaravan.size(); k++){
        int equals=ObjectCaravan[k].getVariableString().find('=');
        string var_name=ObjectCaravan[k].getVariableString().substr(0, equals+1);
        for(unsigned int j=0; j<var_name.length(); j++){
            if(var_name[j]==' ' || var_name[j]=='='){
                var_name.erase(j, 1);
            }
        }
        temp_data.variable_name=var_name;

        ///variable type
        int after_equals=ObjectCaravan[k].getVariableString().find("new ");
        int first_parenth=ObjectCaravan[k].getVariableString().find("(");
        string var_type=ObjectCaravan[k].getVariableString().substr(after_equals+4, first_parenth-(after_equals+4));  ///+4 to skip over the rest of "new "
        temp_data.variable_type=var_type;


        ///constructor stuff
        int second_parenth=ObjectCaravan[k].getVariableString().find(")");
        string construct_stuff=ObjectCaravan[k].getVariableString().substr(first_parenth+1, second_parenth-first_parenth-1);
        temp_data.ConstructorStuff=construct_stuff;
        temp_data.line_number=k+1;///line number
        var_info.push_back(temp_data);
    }
    return var_info;
}


/*method which puts each variable segment into a vector of type variableObject
-params - string input : single line of code
- returns - the vector of type variableObject
*/
vector<variableObject> FindHeapVariables(string input){

	//regex string match
	smatch match;

	vector<variableObject> heapVarVector;

	long variableLocation = 0;

	//size of each match found by regex
    long matchSize = 0;

	bool firstLoopTrigger = false;

	///regex heapVariableRegEx("\\bnew\\b(.|\\n)*?(?=;)");
	regex heapVariableRegEx("([a-zA-Z0-9])*?( )*?(=)*?( )*?new( )*?([a-zA-Z0-9]+)(\\((.*)\\))?( )*?(?=;)");

	while (regex_search(input, match, heapVariableRegEx)){

		cout << match.str() << endl;

		//initial count
		variableLocation += match.position();


		//if first match
		if (firstLoopTrigger == false){

			int variableLocationMinusOne = variableLocation - 1;

			variableObject currentVariableObject = variableObject(match.str(), variableLocationMinusOne);

			heapVarVector.push_back(currentVariableObject);
		}

		//if not the first match
		else{
			variableObject currentVariableObject = variableObject(match.str(), variableLocation);

			heapVarVector.push_back(currentVariableObject);
		}


		matchSize = match.str().size();

		// the count/location
		variableLocation = variableLocation + matchSize + 1;

		firstLoopTrigger = true;

		input = match.suffix().str();

	}
	//testing to see whether the vector is displayed properly
	cout << "VECTOR!!!" << endl;

	for (unsigned int vb = 0; vb < heapVarVector.size(); vb++){
		cout << heapVarVector[vb].getVariableLocation() << "   " << heapVarVector[vb].getVariableString() << endl;
	}

	return heapVarVector;
}


