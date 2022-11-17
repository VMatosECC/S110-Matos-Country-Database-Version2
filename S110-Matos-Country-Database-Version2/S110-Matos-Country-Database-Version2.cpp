// S110-Country-Database.cpp 
// Author:  V. Matos
// Goal:    Create a parallel vector-based database holding information
//          about countries of the world;
//          Version2 - Retrieve by capital 
// ----------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Prototypes -------------------------------------------------------------
void makeDatabase(vector<string>& vcountry, vector<string>& vcapital,
    vector<string>& vcurrency, vector<string>& vlanguages);

void queryDatabase(vector<string>& vcountry, vector<string>& vcapital,
    vector<string>& vcurrency, vector<string>& vlanguages);
void populateVector(vector<string>& v, string fileName);
int  sequentialSearch(vector<string> v, string key);
int  binarySearch(vector<string> v, string key);

void reorganizeDb(vector<string>& v1, vector<string>& v2,
                  vector<string>& v3, vector<string>& v4);

int main()
{
    //Database
    vector<string> vcountry, vcapital, vcurrency, vlanguages;

    makeDatabase(vcountry, vcapital, vcurrency, vlanguages);
    queryDatabase(vcountry, vcapital, vcurrency, vlanguages);

}

//User-defined functions --------------------------------------------------
void makeDatabase(vector<string>& vcountry, vector<string>& vcapital,
    vector<string>& vcurrency, vector<string>& vlanguages)
{
    populateVector(vcountry, "c:/temp/xcountry.txt");
    populateVector(vcapital, "c:/temp/xcapital.txt");
    populateVector(vcurrency, "c:/temp/xcurrency.txt");
    populateVector(vlanguages, "c:/temp/xlanguages.txt");
}

void queryDatabase(vector<string>& vcountry, vector<string>& vcapital,
    vector<string>& vcurrency, vector<string>& vlanguages)
{
    do
    {
        cout << "\nEnter capital [xxx to end]: ";
        string strCapital;
        getline(cin, strCapital);

        if (strCapital == "xxx") break;
        //int pos = sequentialSearch(vcountry, strCountry);

        reorganizeDb(vcapital, vcountry, vlanguages, vcurrency);

        int pos = binarySearch(vcapital, strCapital);
        if (pos == -1)
        {
            cout << "Sorry - no data found for given country\n";
        }
        else
        {
            cout << "Country:     " << vcountry[pos] << endl;
            cout << "Currency:    " << vcurrency[pos] << endl;
            cout << "Language(s): " << vlanguages[pos] << endl;
        }

    } while (true);

}

void populateVector(vector<string>& v, string fileName)
{
    ifstream infile(fileName);
    if (!infile)
    {
        cout << "Fatal error - file not found! \n";
        exit(1);
    }

    string strValue;
    while (getline(infile, strValue))
    {
        v.push_back(strValue);
    }
    infile.close();
}

int  sequentialSearch(vector<string> v, string key)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == key) return i;
    }
    return -1;
}
//---------------------------------------------------------------
int  binarySearch(vector<string> v, string key)
{
    int first = 0;
    int last = v.size() - 1;

    while (first <= last)
    {
        int mid = (first + last) / 2;
        if (v[mid] == key) return mid;  //success! 

        if (v[mid] < key)
            first = mid + 1;            //explore right side
        else
            last = mid - 1;             //explore left side
    }
    return -1;                          //Failure - data not found
}

//---------------------------------------------------------------------
void reorganizeDb(vector<string>& v1, vector<string>& v2,
                  vector<string>& v3, vector<string>& v4)
{
    //using bubblesort
    for (int last = v1.size() - 1; last > 0; last--)
    {
        for (int i = 0; i < last; i++)
        {
            if (v1[i] > v1[i + 1])
            {
                string temp1 = v1[i];
                v1[i] = v1[i + 1];
                v1[i + 1] = temp1;


                string temp2 = v2[i];
                v2[i] = v2[i + 1];
                v2[i + 1] = temp2;

                string temp3 = v3[i];
                v3[i] = v3[i + 1];
                v3[i + 1] = temp3;

                string temp4 = v4[i];
                v4[i] = v4[i + 1];
                v4[i + 1] = temp4;

            }
        }
       
    }
}