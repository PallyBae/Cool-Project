#include "ClassName.h"


//Making the Class Functions
    ClassName::ClassName(int n)
    {
        number = n;
        fragments = 0.0;
        name = "";
        string_vector.push_back("No Strings");
    }
    ClassName::ClassName(string abc, double decimal)
    {
        number = 0;
        fragments = decimal;
        name = abc;
        string_vector.push_back(abc);
    }
    
    void ClassName::m_MemberFunction()
    {

    }
    int ClassName::m_GetNumber()
    {
        return number;
    }
    string ClassName::m_GetName()
    {
        return name;
    }
    double ClassName::m_GetFragments()
    {
        return fragments;
    }
    string ClassName::m_GetStringVectorPos(int i)
    {
        return string_vector[i];
    }