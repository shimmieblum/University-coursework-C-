#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
#include <iostream>
using std::string;
using std::cout;


//TODO: your code goes here:
bool hasMatch(const string & target, string & substring, int index){
    int q = 0;
    bool matchFound = false;
    for(int i = 0; i < index; ++i){
        q = 0;
        if(target[i] == substring[q]){
            matchFound = true;
            for(int p = i + 1; p < substring.length(); ++p && ++q){
                if(target[p] != substring[q]){
                    matchFound = false;
                    break;
                }
            }
        }
        if(matchFound){
            break;
        }
    }
    return matchFound;
}

bool findMatch(const string & target, int i, int & length){
    string s = "";
    bool matchFound = false;
    for(int p = i; p < (i*2)+1 && p < target.length(); p++){
        s += target[p];
        
        if(hasMatch(target, s, i)){
            length = p - i;
            matchFound = true;
        }
    }
    return matchFound;
}

bool hasClone(string target, int index, int & size){
    char c = target[index];
    int maxLength = 0;
    for(int i=0; i<=index; i++){
        c = target[index];
        if(target[i] == c){
            int length = 0;
            int q = i;
            int w = index;
            while(c == target[q] && q<index){
                    q++;
                    length++;
                    w++;
                    c = target[w];
                }
            if(length >maxLength) maxLength = length;
        }
    }
    size = maxLength;
    return maxLength > 0;
}

int stringConstruction(string target, int append, int clone){
    int cost = 0;
    
        for(int i = 0; i<target.size();++i){
            int size = 0;
            if(hasClone(target,i, size) && size*append>clone){
                cost +=clone;
                i+=size-1;
            }
            else cost +=append;
        }
    return cost;       
}




// do not write or edit anything below this line

#endif
