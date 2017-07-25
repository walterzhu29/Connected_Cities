//
//  Connected.cpp
//  Connected
//
//  Created by YUQI ZHU on 2017/7/25.
//  yzhu29@stevens.edu
//

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

//
//class CheckConnection declaration
//class CheckConnection check two specified cities are connected
//

class CheckConnection
{
private:
    //the key in hash is the city of the map
    //the value is a set of string, which is the cities are connected
    unordered_map<string, vector<string>> hash;
public:
    CheckConnection(){}
    
    //get cities' name from every line of input text
    vector<string> getCity(string input);
    
    //add two cities
    void addConnection(string input);
    
    //display hash
    void display();
    
    //check whether two specified cities are connected
    bool checkConnected(string start, string end);
};

//
//class CheckConnection definition
//other function definition
//

//get cities' name from every line of input text
vector<string> CheckConnection::getCity(string input)
{
    string start, end;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    int i = 0;
    while(input[i] == ' ')
        i++;
    while(input[i] != ',')
        start += input[i++];
    while(input[i] == ' ' || input[i] == ',')
        i++;
    while(i < input.size())
        end += input[i++];
    while(end[end.size() - 1] == ' ')
        end.pop_back();
    return {start, end};
}

//add connection of two cities
void CheckConnection::addConnection(string intput)
{
    vector<string> cityname = getCity(intput);
    hash[cityname[0]].push_back(cityname[1]);
    hash[cityname[1]].push_back(cityname[0]);
}

//display hash
void CheckConnection::display()
{
    for(auto a: hash)
    {
        cout<<"From "<<a.first<<" to:"<<endl;
        for(auto b: a.second)
            cout<<b<<" ";
        cout<<endl;
    }
}

//check whether two specified cities are connected
bool CheckConnection::checkConnected(string startCity, string endCity)
{
    transform(startCity.begin(), startCity.end(), startCity.begin(), ::tolower);
    transform(endCity.begin(), endCity.end(), endCity.begin(), ::tolower);
    if(hash.find(startCity) == hash.end() || hash.find(endCity) == hash.end())
        return false;
    //use queus for BFS
    queue<string> Q;
    Q.push(startCity);
    //unordered_set inConnected indicate whether a city can be connected to start city
    //If a city can be find in inConnected, which means this city is connected
    unordered_set<string> isConnected;
    while(!Q.empty())
    {
        string curr = Q.front();
        isConnected.insert(curr);
        if(curr == endCity)
            return true;
        Q.pop();
        for(auto nb: hash[curr])
        {
            if(isConnected.find(nb) != isConnected.end())
                continue;
            Q.push(nb);
        }
        
    }
    return false;
}

//Warning when given a malformed input file or malformed command line
void wrongCommandWarning()
{
    cout<<"The program will be invoked from the command line as (comma separated):"<<endl;
    cout<<"./Connected <filename> <cityname1> <cityname2>"<<endl;
    cout<<"For example:"<<endl;
    cout<<"./Connected cities.txt Boston Pittsburgh"<<endl;
    cout<<"And will output a single line stating yes or no."<<endl;
}


//
//main function
//
int main (int argc, const char * argv[])
{
    if(argc != 4)
    {
        wrongCommandWarning();
        return -1;
    }
    //get input file name
    string file_name = argv[1];
    //get two cities' name
    string startCity = argv[2], endCity = argv[3];
    ifstream read;
    CheckConnection check;
    read.open(file_name, ios::in);
    if(read.fail())
    {
        cout<< "Fail to open the file!"<<endl;
        return -1;
    }
    string s;
    while(!read.eof())
    {
        getline(read,s);
        check.addConnection(s);
    }
    
    if(check.checkConnected(startCity, endCity))
        cout<<"yes"<<endl;
    else
        cout<<"no"<<endl;
    return -1;
}






