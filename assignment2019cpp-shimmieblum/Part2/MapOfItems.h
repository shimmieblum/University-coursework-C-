#ifndef MAPOFITEMS_H
#define MAPOFITEMS_H

#include "Item.h"
#include <iostream>

// TODO: your code goes here

using namespace std;
class MapOfItems{
    private:
    vector<Item> items;

    public:

    MapOfItems():items()
    {}

     void addItem(Item item){
        items.push_back(item);
    }

    int size(){
        return items.size();        
    }

    const vector<Item> & getItems(){
        return  items;
    }

    Item * getShortestTime(){
        Item * shortestTime = &items[0];
        for(auto & item:items){
            if(item.getTime() < shortestTime->getTime())
            shortestTime = &item;
        }
        return shortestTime;
    }

    double visit(const Item & current, const Item & visited, double speed){
        double time = current.distanceTo(visited)/speed;
        return time;
    }

    vector<Item *> getTour(double speed){
        vector<Item *> tour;
        vector<Item*> unvisited; 
        for(auto & item: items){
            unvisited.push_back(&item);
        }

        Item * current = getShortestTime();
        double time = current->getTime();

        int i = 0;
        for(; i<unvisited.size(); ++i){
            if(*current == *unvisited[i]){
                break;
            }
        }

        unvisited.erase(unvisited.begin()+i);
        tour.push_back(current);

        while(time < 3600 && unvisited.size() > 0){
            double bestVisitTime = 4000;
            Item * bestItem = nullptr;

            for(auto & item : unvisited){
                double t = item->getTime();
                double visitTime = visit(*current, *item, speed);
                if(visitTime + time > t + 900){
                    continue;
                }
                if(visitTime + time < t){
                    visitTime = t - time;
                }
                if(visitTime < bestVisitTime){
                    bestVisitTime = visitTime;
                    bestItem = item;
                }
            
            }

            if(bestItem == nullptr) {break;}
            
            time += bestVisitTime;
            tour.push_back(bestItem);
            current = bestItem;
            for(i = 0; i<unvisited.size(); ++i){          
                if(*current == *unvisited[i]){
                        break;
                    }
                }
            unvisited.erase(unvisited.begin()+i);
            
                   
        }
        return tour;
    }

};




// don't write any code below this line
#endif