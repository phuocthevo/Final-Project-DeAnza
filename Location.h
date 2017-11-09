//This class will set each square of the table into an object
//Each object contain the coordinate of the square in the table
#include<iostream>
using namespace std;

class Location
{
private:
	int x, y;
public:
	//Constructor
	Location() {}
	Location(int, int);
	//Setter
	void setX(int );
	void setY(int );
	//Getters
	int getX();
	int getY();
};
//Setting the coordinate
Location::Location(int x, int y){
	this->x = x;
	this->y = y;
}
//Set x-axis
void Location::setX(int temp){
	x = temp;
}
//Set y-axis
void Location::setY(int temp){
	y = temp;
}
//Get the x-coordinate
int Location::getX(){
	return x;
}
//Get the y-coordinate
int Location::getY(){
	return y;
}