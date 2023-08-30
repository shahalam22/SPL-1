#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> inLinkVector;

int main(){
    fstream inlinkFile;
    inlinkFile.open("outLinks.txt");
    if(!inlinkFile){
        cout << "Such MATRIX file doesn't exist!" << endl;
    }else{
        while(inlinkFile){
            vector<int> temp{};
            string x;
            std::getline(inlinkFile, x);
            for(char &c : x){
                if(c != ','){
                    int p = c-'0';
                    temp.push_back(p);
                }
            }
            inLinkVector.push_back(temp);
        }
    }
    inlinkFile.close();

    for(int i=0; i<inLinkVector.size(); i++){
        for(int j=0; j<inLinkVector.at(i).size(); j++){
            cout << inLinkVector.at(i).at(j) << " ";
        }
        cout << endl;
    }
}