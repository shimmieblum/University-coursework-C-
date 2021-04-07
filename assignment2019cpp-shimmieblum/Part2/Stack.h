#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

// TODO: Your code goes here

class Stack{
    int size;
    vector<double> numbers;
    int end;
    

    public:
    Stack()
    : size(10), numbers(vector<double>(size)), end(0) 
    {}

    void push(const double & value){
        if(end == size){
            size = size*2;
            numbers.resize(size);
        }
        numbers[end] = value;
        end++;
    }

    double & pop(){
        end--;
        return numbers[end];
    }

    bool empty() const {
        return end == 0;
    }
};

double evaluate(const string& str){
    string input = " ";
    Stack stack = Stack();
    
    for(int i = 0; i < str.length(); i++){
        input.erase(); 
        while(str[i] != ' ' && i< str.length()){
            input +=str[i];
            i++;
        }
        const char& c = input[0];
        if(c == '+'){
            double a = stack.pop();
            double b = stack.pop();
            stack.push(b + a);
        }
        else if(c == '-'){
            double a = stack.pop();
            double b = stack.pop();
            stack.push(b - a);
        }
        else if(c == '*'){
            double a = stack.pop();
            double b = stack.pop();
            stack.push(b * a);
        }
        else if(c == '/'){
            double a = stack.pop();
            double b = stack.pop();
            stack.push(b / a);
        }
        else{
            stack.push(stod(input));
        }
    }

    return stack.pop();
}

// Do not write anything below this line

#endif
