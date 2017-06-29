#ifndef MATHCALC_H
#define MATHCALC_H

#include <vector>
#include <math.h>

using namespace std;

class MathCalc
{

public:

    MathCalc(double h, double fov, double ang, double r, int px);

    void maxAngle();

    void pixSizeCalc();

    void losCalc();

    void setH(double h);

    void setFov(double fov);

    void setAng(double ang);

    void setR(double r);

    void setPx(double px);

    std::vector<double> getPixVec();

    std::vector<double> getDAngSizeVec();

    std::vector<double> getLosVec();

    std::vector<double> getAngVec();

private:

    double sinLawAng(double side_1, double side_2, double angle_1);

    double sinLawSide(double angle_1, double angle_2, double side_1);

    double cosLaw(double side_1, double side_2, double angle);

    void dAngSidesCalc();

    int px;

    double h, fov, ang, r, maxAng, dAng;

    vector<double> angVec, dAngSidesVec, losVec, pixVec;

};

#endif // MATHCALC_H
