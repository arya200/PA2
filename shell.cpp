#include <iostream>
#include <unistd.h>
#include  <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <cctype>
using namespace std;

void removeSpaces(string &str) 
{ 
    // n is length of the original string 
    int n = str.length(); 
  
    // i points to next position to be filled in 
    // output string/ j points to next character 
    // in the original string 
    int i = 0, j = -1; 
  
    // flag that sets to true is space is found 
    bool spaceFound = false; 
  
    // Handles leading spaces 
    while (++j < n && str[j] == ' '); 
  
    // read all characters of original string 
    while (j < n) 
    { 
        // if current characters is non-space 
        if (str[j] != ' ') 
        { 
            // remove preceding spaces before dot, 
            // comma & question mark 
            if ((str[j] == '.' || str[j] == ',' || 
                 str[j] == '?') && i - 1 >= 0 && 
                 str[i - 1] == ' ') 
                str[i - 1] = str[j++]; 
  
            else
                // copy current character at index i 
                // and increment both i and j 
                str[i++] = str[j++]; 
  
            // set space flag to false when any 
            // non-space character is found 
            spaceFound = false; 
        } 
        // if current character is a space 
        else if (str[j++] == ' ') 
        { 
            // If space is encountered for the first 
            // time after a word, put one space in the 
            // output and set space flag to true 
            if (!spaceFound) 
            { 
                str[i++] = ' '; 
                spaceFound = true; 
            } 
        } 
    } 
  
    // Remove trailing spaces 
    if (i <= 1) 
        str.erase(str.begin() + i, str.end()); 
    else
        str.erase(str.begin() + i - 1, str.end()); 
}


vector<string> split(string str)
{
    vector<string> bgs;
    istringstream ss(str); 
    // Traverse through all words
    //cout << str.length();
    int i = 0; 
    do { 
        // Read a word 
        string word;
        ss >> word;
  
        // Print the read word
        bgs.push_back(word);
        //i++;
        // While there is more to read 
    } while (ss);
    bgs.resize(bgs.size()-1);
    return bgs;
}

char** vec_to_char_array(vector<string>& parts)
{
    //cout << "first element in parts is"<<parts[0] <<endl;
    char** result = new char* [parts.size()+1];
    //string val =" ";
    for(int i=0; i<parts.size(); i++)
    {   
        //cout << parts[i] << endl;
        result[i] = (char*) parts[i].c_str();
        
        //printf(result[i]);

    }
    result [parts.size()]=NULL;
    //cout  << "result is: " <<  **result <<endl;;
    return result;
}

int main ()
{
    vector<int> bgs;
    while(true)
    {
        for(int i=0; i<bgs.size(); i++)
        {
            waitpid(bgs[i], 0, 0);
        }
    }
    while (true)
    {
        cout << "My Shell$ "; //print a prompt
        string inputline;
        getline (cin, inputline); //get a line from standard input
        
        //cout << "inputline is: " << inputline << endl;
        if (inputline == string("exit"))
        {
            cout << "Bye!! End of shell" << endl;
            break;
        }
        
        bool bg = false;
        vector<string> parts = split(inputline);
        if(parts[parts.size()-1] == "&")
        {
            parts.resize(parts.size()-1);
            bg = true;
        }
        char** args = vec_to_char_array(parts);

        int pid = fork ();
        if (pid == 0)
        {   
            execvp (args[0], args);
        }
        else
        { 
            if(!bg)
            {
                //cout << "enter here" <<endl;
                waitpid (pid, 0, 0); //parent waits for child process
            }
            else
            {
                bgs.push_back(pid);
            }
            
        }
    }
}
