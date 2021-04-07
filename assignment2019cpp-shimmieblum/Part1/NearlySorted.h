#ifndef NEARLYSORTED_H
#define NEARLYSORTED_H

#include<iostream>
#include <vector>
using std::vector;
using std::cout;

/** @brief Class that describes how to sort a nearly-sorted vector */
class HowToSort {
protected:
    
    /** @brief The index of the first element to use */
    int firstElement;
    
    /** @brief The index of the second element to use */
    int secondElement;
    
    /** @brief If true, firstElement and secondElement should be swapped; if false, the range of elements should be reversed */
    bool swapThem;
    
public:
    
    /** @brief Default constructor.
     * 
     * This assumes that we can't sort the vector by swapping/reversing a range -- it sets both elements
     * to have an index -1.
     */
    HowToSort() 
      : firstElement(-1),
        secondElement(-1),
        swapThem(false) {
    }
    
    /** @brief The actual constructor: use this to define how to sort a nearly-sorted vector
     * 
     * @param firstElementIn   The first element to use
     * @param secondElementIn  The second element to use
     * @param swapThemIn       If true, swap firstElementIn and secondElementIn; if false, reverse the range of elements
     */
    HowToSort(const int firstElementIn, const int secondElementIn,
              const bool swapThemIn)
      : firstElement(firstElementIn),
        secondElement(secondElementIn),
        swapThem(swapThemIn) {
    }
    
    /** @brief Returns false if no way to sort the vector could be found (i.e. if firstElement == -1) */
    bool canBeMadeSorted() const {
        return (firstElement != -1);
    }
    
    /** @brief Accessor function -- get the first element to use */
    int getFirstElement() const {
        return firstElement;
    }

    /** @brief Accessor function -- get the second element to use */
    int getSecondElement() const {
        return secondElement;
    }

    /** @brief If true, the element indices denote a swap.  If false, they denote a range reversal. */
    bool isASwap() const {
        return swapThem;
    }
    
};

// TODO your code goes here:

bool isSwap(const int & first, const int & last, const vector<int> & vector ){
    bool goodSwap = vector[first] > vector[last - 1]; 
    if(last < vector.size()){
        goodSwap = goodSwap && vector[first] < vector[last+1];
    }
    
    goodSwap = goodSwap && vector[last] < vector[first + 1];
    if(first > 0){
        goodSwap = goodSwap && vector[first] > vector[first - 1]; 
    }

    return goodSwap;
}

HowToSort nearlySorted(const vector<int> & vector){
    int current = vector[0];
    int previous = 0;
    int greatest = 0;

    int firstEl = 0;
    int lastEl = 0;

    bool firstFound = false;
    bool lastFound = false;
    bool swapThem = true;

    for(int i = 1; i < vector.size(); ++i){
        previous = current;
        current = vector[i];
        if(current > greatest){
            greatest = current;
        }

        if(current < previous){
            if (!firstFound){
                firstEl = i-1;
                lastEl = i;
                firstFound = true;
            }
            else if(firstFound){
                if(lastFound){
                    return HowToSort();
                }
                else{
                    if(lastEl == i-1){
                        lastEl = i;
                        swapThem = false;
                    }
                    else{
                        if(isSwap(firstEl, i, vector)){
                            lastEl = i;
                            swapThem = true;
                            lastFound = true;
                        }
                        else
                        {
                            return HowToSort();
                        }
                    }
                }
            }
        }
        else {
            if(lastEl == i-1 && !swapThem){
                lastFound = true;
            }
        }
    }

    if(lastEl -  firstEl < 3){
        swapThem = true;
    }
    return HowToSort(firstEl, lastEl, swapThem);
}


// Don't write any code below this line

#endif
