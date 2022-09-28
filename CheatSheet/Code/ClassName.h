#include <iostream>
#include <vector>
using namespace std;

//Making a Class
class ClassName
{
private:
    int number = 0;
    double fragments = 0.0;
    string name = "";
    vector <string> string_vector;

public:
    //Default Constructor Example 1
    ClassName()
    {
        number = 0;
        fragments = 0.0;
        name = "";
        string_vector.push_back("No Strings");
    }
    //Default Constructor Example 2
    ClassName(int n);
    //Default Constructor Example 3
    ClassName(string abc, double decimal);
    //Destructor Example
    ~ClassName()
    {
        cout << "Inside Destructor";
    }
    //Member Functions
    void m_MemberFunction();
    int m_GetNumber();
    string m_GetName();
    double m_GetFragments();
    string m_GetStringVectorPos(int i);
};
//Dont forget the Semicolon at the end