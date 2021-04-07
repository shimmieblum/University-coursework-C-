#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <set>
#include <iostream>
#include "Searchable.h"
#include <cmath>
#include "SudokuSquare.h"

using namespace std;
// TODO: Your Sudoku class goes here:

class singleSquare{
    public: 
    int row;
    int column;
    int value;
    
    singleSquare(int r, int c, int v)
    :row(r), column(c), value(v){}

    bool error(){
        return row == -1 && column == -1 && value == -1;
    }
};

class Sudoku : public Searchable{
    private:
    int size;
    vector<vector<SudokuSquareSet>> board;
    

    public:

    Sudoku(int inSize)
    : Searchable(), size(inSize), board(size){
        for(int i = 0; i < size; ++i){
            board[i] = vector<SudokuSquareSet>(size);
            for(int p = 0; p < size; ++p){
                SudokuSquareSet newSet;
                for(int val = 1; val <=size; val++) newSet.insert(val);
                board[i][p] = newSet;
            }
        }
    }

    int getSquare(int row, int column){
        
        if(board[column][row].size() > 1){
            return -1;
        }
        
        else return *board[column][row].begin();
    }

    bool setSquare(int row, int column, int value){
        SudokuSquareSet & s = board[column][row];
        
        s.clear();
        s.insert(value);
        return fixBoard(row,column,value);
         
    }

    bool fixBoard(int row, int column, int value){
        vector<singleSquare> sqr = fixRowColumnSquare(row,column,value);
        return cascadeChanges(sqr);
    }
        

    vector<singleSquare> fixRowColumnSquare(int row, int column, int value){
       
        vector<singleSquare> vec;
        for(int i = 0; i<size; ++i){
            SudokuSquareSet & columnSet = board[column][i];
            int css = columnSet.size();
            
            SudokuSquareSet & rowSet = board[i][row];
            int rss = rowSet.size();


            if(setHasValue(columnSet, value) && i != row){
                if(columnSet.size() == 1) {
                    return vector<singleSquare>{singleSquare(-1,-1,-1)}; // if there is 0 in one set, return 'error flag' 
                }
                columnSet.erase(value);
                if(columnSet.size()==1) vec.push_back(singleSquare(i,column, *columnSet.begin()));
                
                
            }
            if(setHasValue(rowSet, value) && i !=column){
                if(rowSet.size() == 1) {
                    return vector<singleSquare>{singleSquare(-1,-1,-1)}; // if there is 0 in one set, return 'error flag' 
                }
                rowSet.erase(value);
                if(rowSet.size() == 1) vec.push_back(singleSquare(row,i, *rowSet.begin()));
            }
        }
        int sqr = sqrt(size);
        int topLeftRow = (row/sqr) * sqr;
        int topLeftCol = (column/sqr) * sqr;
        
        for(int r = topLeftRow; r < (topLeftRow + sqr); ++r){
            for(int c = topLeftCol; c < (topLeftCol + sqr); ++c){
                if(r==row && c == column){}
                else {
                    SudokuSquareSet & s = board[c][r];
                    if(setHasValue(s,value)){
                        if(s.size() == 1) {
                            return vector<singleSquare>{singleSquare(-1,-1,-1)}; // if there is 0 in one set, return 'error flag'
                        }
                        s.erase(value);
                        if(s.size() == 1) vec.push_back(singleSquare(r,c, *s.begin()));
                    }
                }
            }
        }

         return vec;
    }

    bool cascadeChanges(vector<singleSquare> & vec){
        if(vec.size() == 0) return true;
        vector<singleSquare> changes;
        for(auto & t:vec){
            vector<singleSquare> newChanges = fixRowColumnSquare(t.row,t.column,t.value);
            if(newChanges.size() == 1 && newChanges[0].error()) return false; // disgusting method to check for terrible value.
            changes.insert(changes.end(), newChanges.begin(), newChanges.end());
        }
        return cascadeChanges(changes);

    }

    bool setHasValue(const SudokuSquareSet & s, int value)const{
        return s.find(value) !=s.end();
    }

    virtual bool isSolution() const{
        for(int c = 0; c<size; c++){
            for(int r = 0; r<size; r++){
                if(board[c][r].size() !=1) return false;
            }
        }
        return true;
    }    

    virtual void write(ostream & o)const{
        int sqr = sqrt(size);
        for(int r = 0; r<size; r++){
            if(r%sqr == 0){
                for(int i=0; i<=size+sqr;i++) o<<"___";
                o<<"\n";
            }
            for(int c = 0; c<size; c++){
                if(c%sqr == 0) o<<" | ";
                board[c][r].size() !=1 ? o<<"   " : o<<" "<<*board[c][r].begin()<<" ";
            }
            o<<" | \n";
        }
        for(int i=0; i<=size+sqr;i++) o<<"___";
    }

    virtual vector<unique_ptr<Searchable>> successors() const {
        vector<unique_ptr<Searchable>> vec;
        SudokuSquareSet s;
        int row = -1;
        int column = -1;
        bool found = false;
        for(int r = 0; r < size && !found; ++r){
            for(int c = 0; c < size && !found; ++c){
                if (board[c][r].size() > 1){
                    s = board[c][r];
                    row = r;
                    column = c;
                    found = true;
                }
            }
        }
        int i = 0;
        for(const auto & value:s){
            i +=value;
            unique_ptr<Sudoku> copy = unique_ptr<Sudoku>(new Sudoku(*this));
            bool solution = copy->setSquare(row,column,value);
            if(solution){
                vec.push_back(move(copy));
            }
        }
        return vec;
    }


};




#endif
