#include "mathcalc.h"
#define PI 3.141592653589793

// Constructor
MathCalc::MathCalc(double h, double fov, double ang, double r, int px)
{
    this->h = h;
    this->fov = fov;
    this->ang = ang;
    this->r = r;
    this->px = px;
    dAng = fov / px; // calculate and set the angle step
    maxAngle(); // calculate and set the max allowed value for the angle
}

// Law of sines, case 1: two sides and one non-enclosed angle are known, calculate the oposite angle of side_2.
double MathCalc::sinLawAng(double side_1, double side_2, double angle_1)
{
    double angle_2;

    angle_2 = asin((side_2) * sin(angle_1) / side_1);

    return angle_2;
}

// Law of sines, case 2: two angles and a side are known, calculate the oposite side of angle_2.
double MathCalc::sinLawSide(double angle_1, double angle_2, double side_1)
{
    double side_2;

    side_2 = side_1 * sin(angle_2) / sin(angle_1);

    return side_2;
}

// Law of cosines: two sides and the enclosed angle are known, calculate the third side.
double MathCalc::cosLaw(double side_1, double side_2, double angle)
{
    double side_3;

    side_3 = sqrt(pow(side_1, 2) + pow(side_2, 2) - 2 * side_1 * side_2 * cos(angle));

    return side_3;
}

// Find the max allowed angle (when the external side of fov angle gets tangent to the Earth's surface)
void MathCalc::maxAngle()
{
    double side_1, side_2, angle_1;
    side_1 = r + h;
    side_2 = r;
    angle_1 = PI / 2;
    maxAng= sinLawAng(side_1, side_2, angle_1) - (fov / 2) ;
}

// Calculate the lenth of all sides of the angles which result after the segmetation of the fov into px parts.
void MathCalc::dAngSidesCalc()
{
    vector<double> dAngSidesVec(px + 1);
    double side_1, side_2, ang_1, ang_2, ang_3;

    if (ang <= maxAng)
    {
        side_1 = r;
        side_2 = r + h;
        for (int i = 0; i <= px; i++)
        {
            ang_1 = ang + fov / 2 - i * dAng;
            ang_2 = 2 * PI - sinLawAng(side_1, side_2, ang_1);
            ang_3 = 2 * PI - ang_1 - ang_2;
            dAngSidesVec[i] = sinLawSide(ang_1, ang_3, side_1);
        }
    }

    this->dAngSidesVec = dAngSidesVec;
}

// Calculate the (centered) line of sight for each pixel.
void MathCalc::losCalc()
{
    vector<double> losVec(px);
    vector<double> angVec(px);
    double side_1, side_2, ang_1, ang_2, ang_3;

    if (ang < maxAng)
    {
        side_1 = r;
        side_2 = r + h;
        for (int i = 0; i < px; i++)
        {
            ang_1 = ang + (fov / 2) - (i + 1) * dAng + (dAng / 2);
            ang_2 = 2 * PI - sinLawAng(side_1, side_2, ang_1);
            ang_3 = 2 * PI - ang_1 - ang_2;
            losVec[i] = sinLawSide(ang_1, ang_3, side_1); // in each step, store the calculated line of sight
            angVec[i] = ang_1; // in each step, store the angle used
        }
    }

    this->losVec = losVec;
    this->angVec = angVec;
}


void MathCalc::pixSizeCalc()
{
    vector<double> pixVec(px);
    double crd, theta;

    if (ang <= maxAng)
    {
        dAngSidesCalc();
        for (int i = 0; i < px; i++)
        {
            //pixVec[i] = cosLaw(dAngSidesVec[i], dAngSidesVec[i+1], dAng);
            crd = cosLaw(dAngSidesVec[i], dAngSidesVec[i+1], dAng);
            theta = 2 * asin(crd / (2 * r));
            pixVec[i] = r * theta;
        }
    }

    this->pixVec = pixVec;
    //this->pixVec2 = pixVec2;
}

void MathCalc::setH(double h)
{
    this->h = h;
    maxAngle(); // when the h changes, recalculate the max allowed angle
}

void MathCalc::setFov(double fov)
{
    this->fov = fov;
    dAng = fov / px;
}

void MathCalc::setAng(double ang)
{
    this->ang = ang;
}

void MathCalc::setR(double r)
{
    this->r = r;
    maxAngle(); // when the r changes, recalculate the max allowed angle
}

void MathCalc::setPx(double px)
{
    this->px = px;
    dAng = fov / px;
}

std::vector<double> MathCalc::getPixVec()
{
    return pixVec;
}

std::vector<double> MathCalc::getDAngSizeVec()
{
    return dAngSidesVec;
}

std::vector<double> MathCalc::getLosVec()
{
    return losVec;
}

std::vector<double> MathCalc::getAngVec()
{
    return angVec;
}


