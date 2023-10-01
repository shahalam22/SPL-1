#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream file;
    file.open("index.html");
    string line;
    while(getline(file, line)){
        if(line.find("<a") != string::npos){
            if(line.find("href") != string::npos){
                int start = line.find("href");
                int end = line.find(">", start);
                string url = line.substr(start+6, end-start-7);
                cout << url << endl;
            }
        }
    }
}