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

	regex heapVariableRegEx("\\bnew\\b(.|\\n)*?(?=;)");

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


int main(){

	//string sample = "asdaf var v = new var(sample); asfdsg Hi Hello /n b=new bar(docte); sdfsadf";
	string sample("asdaf var v = new var(sample); \n asfdsg Hi Hello \n b=new bar(docte); sdfsadf \n var b = new bre(sample); ");
	FindHeapVariables(sample);

	cin.ignore();
	cin.get();

}

