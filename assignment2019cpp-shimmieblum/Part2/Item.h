#ifndef ITEM_H
#define ITEM_H


#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using std::string;
using std::ostream;

using std::vector;


// TODO: copy your Item.h file from assignment 1 over this file


class Item
{
	double latitude, longitude;
	string ID;
	int time;
	

	public:

	Item(double newLatitude, double newLongitude, string newID, int newTime)
		: latitude(newLatitude), longitude(newLongitude), ID(newID), time(newTime) 
	{}

	double getLatitude() const{
		return latitude;
	}

	double getLongitude() const{
		return longitude;
	}

	string getID()const{
		return ID;
	}

	int getTime() const{
		return time;
	}


	

	double const distanceTo(const Item & otherItem) const{
		double lon1 = radians(longitude);
		double lat1 = radians(latitude);
		double lon2 = radians(otherItem.getLongitude());
		double lat2 = radians(otherItem.getLatitude());

		double dlon = lon2 - lon1;
		double dlat = lat1 - lat2;  
		double a = pow((sin(dlat/2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon/2)), 2);  
		double c = 2 * atan2( sqrt(a), sqrt(1-a) );  
		double distance = 6373000 * c;

		return distance;
	}

	bool operator==(const Item & other) const{
		return getTime() == other.getTime() 
			&& getLatitude() == other.getLatitude() 
			&& getLongitude() == other.getLongitude()
			&& getID() == other.getID();
	}

	private:

	double radians(double val) const{
		return (val * 3.141592654 / 180);
	}

	
	
};

ostream& operator<<(ostream& stream, Item item){
	stream << "{" << item.getLatitude() << ", " << item.getLongitude() << ", \"" << item.getID() << "\", " << item.getTime() << "}";
	return stream;
}


#endif

