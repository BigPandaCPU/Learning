 /*** 对象工厂模式初探 *****/

#include<iostream>
#include<stdexcept>
#include<cstddef>
#include<string>
#include<vector>

 using namespace std;
 class Shape
 {
 public:
	 virtual void draw()  = 0;
	 virtual void erase() = 0;
	 virtual ~Shape(){}

	 class BadShapeCreation : public logic_error
	 {
	 public:
		 BadShapeCreation(string type):logic_error("Cannot create type"){}
	 };
	 static Shape *factory(const string &type)
		 throw(BadShapeCreation);
 };

 class Circle:public Shape
 {
 private:
	 Circle() {}
	 friend class Shape;
 public:
	 void draw(){cout<<"Circle::draw"<<endl;}
	 void erase(){cout<<"Circle::erase"<<endl;}
	 ~Circle(){cout<<"Circle::~Circle"<<endl;}
 };

 class Square:public Shape
 {
	 Square(){}
	 friend class Shape;
 public:
	 void draw(){cout<<"Square::draw"<<endl;}
	 void erase(){cout<<"Square::erase"<<endl;}
	 ~Square(){cout<<"Square::~Square"<<endl;}
 };


 Shape *Shape::factory(const string &type)
	 throw(Shape::BadShapeCreation)
 {
	 if(type == "Circle")
		 return new Circle;
	 if(type == "Square")
		 return new Square;
	 throw BadShapeCreation(type);
 }

 char *sl[]={"Circle","Square","Square","Circle","Circle","Square"};

 int main()
 {
	 vector<Shape *> shapes;
	 try
	 {
		 for(size_t i =0; i<sizeof sl/sizeof sl[0] ;i++)
			shapes.push_back(Shape::factory(sl[i]));
				//cout<<sizeof(sl[i])<<typeid(sl[i]).name()<<endl;
	 }
	 catch(Shape::BadShapeCreation e)
	 {
		 cout<<e.what()<<endl;
		 system("pause");
		 return -1;
	 }
	 for(size_t i = 0;i<shapes.size();i++)
	 {
		 shapes[i]->draw();
		 shapes[i]->erase();
	 }

	 system("pause");
	 return 0;
 }