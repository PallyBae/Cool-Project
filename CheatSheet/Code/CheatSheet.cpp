#include <SFML/Graphics.hpp>
#include <complex>
#include <cmath>
#include <sstream>
#include "ClassName.h"
#include <iomanip>

//Main Function
int main()
{
    //Testing My Class by creating an Object
    string Bite = "The bite of ";
    double BiteNum = 87.00;
    ClassName ObjectName(Bite, BiteNum);
    cout << ObjectName.m_GetName();
    cout << ObjectName.m_GetFragments();
    cout << endl;
    //Output
    //The bite of 87
    //
    
    //Showing Output Manipulation
    cout << fixed << ObjectName.m_GetFragments() << endl;
    //Output
    //87.000000
    //
    cout << fixed << setprecision(3) << ObjectName.m_GetFragments() << endl;
    //Output
    //87.000
    cout << setw(5) << "hi" << endl;
    //Output
    //   hi
    //

    //Testing Vectors
    vector <int> integer_vector;

    //Filling the vector
    for(int i = 0; i < 10 ;i++)
    {
        integer_vector.push_back(i);
    }
    //Showing the vector
    for(int i = 0; i < integer_vector.size() ;i++)
    {
        cout << integer_vector[i] << endl;
    }
    //OUTPUT
    //0-9 vertical

    //Removing one value from the vector
    vector <int>::iterator begin;
    begin = integer_vector.begin();
    integer_vector.erase(begin + 1);
    //Showing the vector
    for(int i = 0; i < integer_vector.size() ;i++)
    {
        cout << integer_vector[i] << endl;
    }
    //OUTPUT
    //0,2-9 vertical

    //Do While loop
    int count = 0;
    do
    {
        count ++;
        cout << "HI5 S" << endl;
    } while (count < 0);
    //Output
    //HI5 S
    //
    
    return 0;
}