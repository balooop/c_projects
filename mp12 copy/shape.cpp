#include "shape.hpp"
#include <math.h>
#include <fstream>
#include <string>
#include <vector>



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name)	// uses resolution operator to create shape function
{
  this->name_ = name;   // assigns name of new shape object to Shape
}
string Shape::getName()
{
  return this->name_;	// returns name of this shape
}



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle")
{
  this->width_ = width;            	// assigns width
  this->length_ = length;        	// assigns length
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
double Rectangle::getArea()const{return length_ * width_;} //return length times width
double Rectangle::getVolume()const{return 0;}

Rectangle Rectangle:: operator +(const Rectangle& r1)	// overloaded operator with 2 rectangles passed by reference as parameters
{
  double newLength = getLength() + r1.length_;    	// creates new length as sum of parameter lengths
  double newWidth = getWidth() + r1.width_;        	// creates new width as sum of parameter widths
  Rectangle newR(newWidth, newLength);                                	// creates new rectangle with new parameters
  return newR;                                                                                	// returns new rectangles
}

Rectangle Rectangle:: operator -(const Rectangle& r1)
{
  double newLength = getLength() - r1.getLength();    	// creates new length by subtracting new lengths
  double newWidth = getWidth() - r1.getWidth();        	// creates new width by subtracting new widths
  if(newWidth<0)
  {
	newWidth = 0;
  }
  if (newLength<0)
  {
	newLength = 0;
  }
  return Rectangle(newWidth, newLength);                            	// returns new Rectangle
}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle")
{
  this->radius_ = radius;        	// assigns radius
}
double Circle::getRadius()const{return radius_;}
double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);       	// returns pi*r^2 (radius) of the circle
}
double Circle::getVolume() const
{
  return 0; // circle has no volume
}

Circle Circle::operator +(const Circle& c1)
{
  double radiusNew = getRadius() + c1.getRadius(); //add 2 radii
  Circle newCircle(radiusNew);                                	//construct new circle
  return newCircle;                                                        	// return new circle
}
Circle Circle::operator -(const Circle& c1)
{
  double radiusNew = getRadius() - c1.getRadius(); //subtract 2 radii
  if (radiusNew<0)
  {
	radiusNew = 0;
  }
  Circle newCircle(radiusNew);   //construct new circle
  return newCircle;                         	// return new circle
}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here


Sphere::Sphere(double radius):Shape("Sphere")
{
  this->radius_ = radius; //radius
}
double Sphere::getRadius()const{return radius_;}
double Sphere::getArea() const
{
  return 4 * M_PI * radius_ * radius_;    	// are of a sphere is 4pi*r^
}
double Sphere::getVolume() const
{
  return (4.0/3.0) * M_PI * radius_ * radius_ * radius_;     	// returns volume of 4/3 * pi * r^3
}

Sphere Sphere:: operator +(const Sphere& r1)
{
  return Sphere(this->radius_ + r1.getRadius());
}
Sphere Sphere:: operator -(const Sphere& r1)
{
  double newRadius = getRadius() - r1.getRadius();
  if (newRadius<0)
  {
	newRadius = 0;
  }
  return Sphere(newRadius);
}
//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
  this->width_ = width;        	// sets length, width, height
  this->length_ = length;
  this->height_ = height;
}
double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
double RectPrism::getArea()const{return 2*(width_*length_ + width_*height_ + length_ * height_);}
double RectPrism::getVolume()const{return (width_*length_*height_);}

RectPrism RectPrism:: operator +(const RectPrism& p1)
{
  double lengthNew = getLength() + p1.getLength(); //add lengths
  double widthNew = getWidth() + p1.getWidth(); 	//add widths
  double heightNew = getHeight() + p1.getHeight(); // add Heights
  RectPrism newRectPrism(widthNew, lengthNew, heightNew);                                	//construct new prism
  return newRectPrism;                                                        	// return new prism
}
RectPrism RectPrism:: operator -(const RectPrism& p1)
{
  double lengthNew = getLength() - p1.getLength(); //subtract lengths
  if (lengthNew<0)
  {
	lengthNew = 0;
  }
  double widthNew = getWidth() - p1.getWidth(); 	//subtract widths
  if (widthNew<0)
  {
	widthNew = 0;
  }
  double heightNew = getHeight() - p1.getHeight() ; //subtract Heights
  if (heightNew<0)
  {
	heightNew = 0;
  }
  RectPrism newRectPrism(widthNew, lengthNew, heightNew);                                	//construct new circle
  return newRectPrism;                                                        	// return new circle
}
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
  //@@Insert your code here
  int size;
  std::ifstream input_file(file_name);
  input_file >> size;
  
  string shape_name;    
  std::vector<Shape*> shapeVect(size);
  double height, width, length;
  for (int i = 0; i<size; i++)
  {
	input_file >> shape_name;
	if(shape_name == "Sphere")
	{
  	input_file >> height;
  	shapeVect[i] = new Sphere(height);
	}
	if(shape_name == "RectPrism")
	{
  	input_file >> height >> width >> length;
  	shapeVect[i] = new RectPrism(height, width, length);
	}
	if(shape_name == "Circle")
	{
  	input_file >> height;
  	shapeVect[i] = new Circle(height);
	}
    if(shape_name == "Rectangle")
	{
  	input_file >> height >> width;
  	shapeVect[i] = new Rectangle(height, width);
	}
  }
  input_file.close();
 
  return shapeVect;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
  double max_area = shapes[0]->getArea();
  //@@Insert your code here
  for(int i = 1; i < shapes.size(); i++)
  {
	if(shapes[i]->getArea() > max_area)	// if the current shape area is greater than current max area
  	max_area = shapes[i]->getArea();        	// set current area to max
  }
  return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
  double max_volume = shapes[0]->getVolume();
  //@@Insert your code here
  for(int i = 1; i < shapes.size(); i++)            	// lOoP tHrOuGh shAPeS
  {
	if(shapes[i]->getVolume() > max_volume)	// if the current shapes volume is greater than current max volume
  	max_volume = shapes[i]->getVolume();        	// maxVolume = currentVolume
  }
  return max_volume;
}








