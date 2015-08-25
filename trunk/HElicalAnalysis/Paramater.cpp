#include "Paramater.h"
Paramater::Paramater(double ri,double ro, double sh,double sl,double tw,double ti,string na)
{
	rise=ri;
	roll=ro;
	shift=sh;
	slide=sl;
	twist=tw;
	tilt=ti;
	name=na;
}

Paramater::~Paramater(void)
{
}
void Paramater::SetTwist(double d)
    {
        twist=d;
    }
    void Paramater::SetTilt(double d)
    {
        tilt=d;
    }
    void Paramater::SetRoll(double d)
    {
        roll=d;
    }
    void Paramater::SetRise(double d)
    {
        rise=d;
    }
    void Paramater::SetShift(double d)
    {
        shift=d;
    }
    void Paramater::SetSlide(double d)
    {
        slide=d;
    }
    void Paramater::SetName(string s)
    {
        name=s;
    }
    double Paramater::GetRise()
    {
        return rise;
    }
    double Paramater::GetRoll()
    {
        return roll;
    }
    double Paramater::GetShift()
    {
        return shift;
    }
    double Paramater::GetSlide()
    {
        return slide;
    }
    double Paramater::GetTilt()
    {
        return tilt;
    }
    double Paramater::GetTwist()
    {
        return twist;
    }
    string Paramater::GetName()
    {
        return name;
    }

