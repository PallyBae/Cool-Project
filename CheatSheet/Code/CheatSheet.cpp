#include <sstream>
#include "ClassName.h"
#include <iomanip>

//Main Function
int main()
{
    string Bite = "The bite of ";
    double BiteNum = 87.00;
    ClassName ObjectName(Bite, BiteNum);
    cout << ObjectName.m_GetName();
    cout << ObjectName.m_GetFragments();
    cout << endl;
    //The bite of 87
    cout << fixed << ObjectName.m_GetFragments() << endl;
    //87.000000
    cout << fixed << setprecision(3) << ObjectName.m_GetFragments() << endl;
    //87.000
    cout << setw(5) << "hi" << endl;
    //   hi
    vector <int> integer_vector;
    for(int i = 0; i < 10 ;i++)
    {
        integer_vector.push_back(i);
    }
    for(int i = 0; i < integer_vector.size() ;i++)
    {
        cout << integer_vector[i] << endl;
    }
    //0-9 vertical
    vector <int>::iterator begin;
    begin = integer_vector.begin();
    integer_vector.erase(begin + 1);
    for(int i = 0; i < integer_vector.size() ;i++)
    {
        cout << integer_vector[i] << endl;
    }
    //0,2-9 vertical
    int count = 0;
    do
    {
        count ++;
        cout << "HI5 S" << endl;
    } while (count < 0);
    //HI5 S
    return 0;
}