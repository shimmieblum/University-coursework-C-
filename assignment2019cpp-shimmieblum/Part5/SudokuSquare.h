#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H
#include <iostream>

using namespace std;
// Do not add any #include statements to this file

class SudokuSquareSetIterator{
    private:
    unsigned int current;

    public:
    SudokuSquareSetIterator(unsigned int set)
    :current(set){}

    int operator*()const{
        
        unsigned int copy = current;
        if(copy == 0) return 0;
        int count = 1;
        while(copy % 2 != 1 ){ // odd number has value in bit 0. how far needs to be moved to reach that == the value.
            count++;
            copy = copy >> 1;
        }
        return count;
    }

    void operator++(){
        unsigned int val = *(*this) ; // the number currently pointed to -1
        --val;
        unsigned int bitMask = pow(2,val);
        
        bitMask = ~bitMask;
        current =  current & bitMask;
    }


    bool operator==(const SudokuSquareSetIterator & other) const{
        return current == other.getCurrent();
    }

    bool operator!=(const SudokuSquareSetIterator & other) const{
        return current != other.getCurrent();
    }

    unsigned int getCurrent()const{
        return current;
    }

    unsigned int pow(unsigned int base, unsigned int expo){
        unsigned int v= 1;
        for(int i = 0; i<expo; ++i){
            v*=base;
        }
        return v;
    }
};


class SudokuSquareSet {

    // TODO: write your code here
    public:
    unsigned int contentBin;
    int count;

    SudokuSquareSet():
    contentBin(0), count(0){}

    int size() const{
        return count;
    }

    bool empty() const{
        return count == 0;
    }

    void clear(){
        contentBin = 0;
        count = 0;
    }

    bool operator==(const SudokuSquareSet & other) const{
        return contentBin == other.contentBin;
    }

    bool operator!=(const SudokuSquareSet & other) const{
        return contentBin != other.contentBin;
    }

    SudokuSquareSetIterator begin()const{
        return SudokuSquareSetIterator(contentBin);
    }

    SudokuSquareSetIterator end()const{
        return SudokuSquareSetIterator(0);
    }

    SudokuSquareSetIterator insert(int value){
        
        if(find(value) == end()){
            count++;
            contentBin += pow(2,value-1);
        }
    }

    SudokuSquareSetIterator find(int value)const{
        SudokuSquareSetIterator it = begin();
        while(it != end()){
            if(*it == value) return it;
            ++it;
        }
        return end();
    }

    void erase(SudokuSquareSetIterator & it){
        erase(*it);
    }

    void erase(int value){
        
        if(find(value) != end()){
            contentBin -= pow(2,value-1);
            count--;
        }
    }

    int pow(int base, int expo)const{
        int val = 1;
        for(int i = 0; i<expo; ++i){
            val *=base;
        }
        return val;
    }


};



// Do not write any code below this line
static_assert(sizeof(SudokuSquareSet) == sizeof(unsigned int) + sizeof(int), "The SudokuSquareSet class needs to have exactly two 'int' member variables, and no others");


#endif
