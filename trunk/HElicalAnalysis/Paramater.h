#pragma once
#include<string>
using namespace std;

class Paramater
{
public:
	Paramater(double,double,double,double,double,double,string);
	~Paramater(void);
	void SetTwist(double);
	void SetTilt(double);
	void SetRoll(double);
	void SetRise(double);
	void SetShift(double);
	void SetSlide(double);
	void SetName(string);
	double GetRise();
	double GetRoll();
	double GetShift();
	double GetSlide();
	double GetTilt();
	double GetTwist();
	string GetName();

private:
	double twist;
    double tilt;
    double roll;
    double shift;
    double rise;
    double slide;
    string name;
};


