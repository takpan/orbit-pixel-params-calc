#ifndef OrbitPixParams_H
#define OrbitPixParams_H

#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;

class OrbitPixParams
{

public:

    OrbitPixParams(double h, double fov, double viewAng, double r, int px);

    void losCalc();

    void pixSizeCalc();

    void setH(double h);

    void setFov(double fov);

    void setAng(double viewAng);

    void setR(double r);

    void setPx(double px);

    double getmaxViewAng();

    double getMaxFov();

    bool getErrFov();

    bool getErrViewAng();

    string getErrMsg();

    vector<double> getPixVec();

    vector<double> getDAngSizeVec();

    vector<double> getLosVec();

    vector<double> getAngVec();

    bool printToFile(string fileName, string angMeas);

private:

    double sinLawAng(double side_1, double side_2, double angle_1);

    double sinLawSide(double angle_1, double angle_2, double side_1);

    double cosLaw(double side_1, double side_2, double angle);

    double strtLineLenCalc(double ang_1);

    void dAngSidesCalc();

    void maxFovCalc();

    void maxViewAngCalc();

    bool checkCond();

    bool errViewAng, errFov;

    string errMsg;

    int px;

    double h, fov, viewAng, r, maxFov, maxViewAng, dViewAng;

    vector<double> angVec, dAngSidesVec, losVec, pixVec;

};

#endif // OrbitPixParams_H
