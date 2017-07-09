#include "orbitpixparams.h"
#define PI 3.141592653589793

//-----------------------------------------------------------------------------
// CONSTRUCTORS:
//-----------------------------------------------------------------------------

OrbitPixParams::OrbitPixParams(double h, double fov, double viewAng, double r, int px)
{
    this->h = h;
    this->fov = fov;
    this->viewAng = viewAng;
    this->r = r;
    this->px = px;
    dViewAng = fov / px; // calculate and set the angle step
    maxFovCalc(); // calculate and set the max allowed value for the fov angle
    maxViewAngCalc(); // calculate and set the max allowed value for the view angle
    errViewAng = false; // error flag for view angle
    errFov = false; // // error flag for fov angle
}

//-----------------------------------------------------------------------------
// CALC METHODS:
//-----------------------------------------------------------------------------

// Law of sines, case 1: two sides and one non-enclosed angle are known, calculate the oposite angle of side_2.
double OrbitPixParams::sinLawAng(double side_1, double side_2, double angle_1)
{
    double angle_2;

    angle_2 = asin((side_2) * sin(angle_1) / side_1);

    return angle_2;
}

// Law of sines, case 2: two angles and a side are known, calculate the oposite side of angle_2.
double OrbitPixParams::sinLawSide(double angle_1, double angle_2, double side_1)
{
    double side_2;

    side_2 = side_1 * sin(angle_2) / sin(angle_1);

    return side_2;
}

// Law of cosines: two sides and the enclosed angle are known, calculate the third side.
double OrbitPixParams::cosLaw(double side_1, double side_2, double angle)
{
    double side_3;

    side_3 = sqrt(pow(side_1, 2) + pow(side_2, 2) - 2 * side_1 * side_2 * cos(angle));

    return side_3;
}

// Find the max allowed fov angle (when the fov angle sides gets tangent to the Earth's surface)
void OrbitPixParams::maxFovCalc()
{
    double side_1, side_2, angle_1;
    side_1 = r + h;
    side_2 = r;
    angle_1 = PI / 2;
    maxFov = 2 * sinLawAng(side_1, side_2, angle_1);
}

// Find the max allowed angle (when the external side of fov angle gets tangent to the Earth's surface)
void OrbitPixParams::maxViewAngCalc()
{
    maxViewAng = maxFov / 2 - fov / 2;
}

// Check if fov or view angle is out of the allowed range
bool OrbitPixParams::checkCond()
{
    bool ok = true;

    if (fov > maxFov)
    {
        errFov = true;
        errMsg = "Fov angle is greater than the max allowed value";
        ok = false;
    }

    else if (fabs(viewAng) > maxViewAng)
    {
        errViewAng = true;
        errMsg = "View angle is greater than the max allowed value";
        ok = false;
    }

    return ok;
}

// Calculate the length of a straight line, starting from the satellite and ending on the planet's surface (/| when this angle is given).
double OrbitPixParams::strtLineLenCalc(double ang_1)
{
    double ang_2, ang_3, lineLen;

    ang_2 = 2 * PI - sinLawAng(r, r + h, ang_1);
    ang_3 = 2 * PI - ang_1 - ang_2;
    lineLen = sinLawSide(ang_1, ang_3, r);

    return lineLen;
}

// Calculate the lenth of all sides of the angles resulting after the segmetation of the fov into px parts.
void OrbitPixParams::dAngSidesCalc()
{
    vector<double> dAngSidesVec(px + 1);
    double ang_1;

    for (int i = 0; i <= px; i++)
    {
        ang_1 = viewAng + fov / 2 - i * dViewAng;
        dAngSidesVec[i] = strtLineLenCalc(ang_1);
    }

    this->dAngSidesVec = dAngSidesVec;
}

// Calculate the (centered) line of sight for each pixel.
void OrbitPixParams::losCalc()
{
    vector<double> losVec(px);
    vector<double> angVec(px);
    double ang_1;

    if (checkCond())
    {
        //side_1 = r;
        //side_2 = r + h;
        for (int i = 0; i < px; i++)
        {
            ang_1 = viewAng + (fov / 2) - (i + 1) * dViewAng + (dViewAng / 2);
            losVec[i] = strtLineLenCalc(ang_1); // in each step, store the calculated line of sight
            angVec[i] = ang_1; // in each step, store the angle used
        }
        this->losVec = losVec;
        this->angVec = angVec;
    }
}


void OrbitPixParams::pixSizeCalc()
{
    vector<double> pixVec(px);
    double crd, theta;

    if (checkCond())
    {
        dAngSidesCalc();
        for (int i = 0; i < px; i++)
        {
            crd = cosLaw(dAngSidesVec[i], dAngSidesVec[i+1], dViewAng);
            theta = 2 * asin(crd / (2 * r));
            pixVec[i] = r * theta;
        }

        this->pixVec = pixVec;
    }
}

//-----------------------------------------------------------------------------
// SETTERS:
//-----------------------------------------------------------------------------

void OrbitPixParams::setH(double h)
{
    errFov = false;
    errViewAng = false;
    this->h = h;
    maxFovCalc(); // when the h changes, recalculate the max allowed fov angle
    maxViewAngCalc(); // ...and the max allowed view angle
}

void OrbitPixParams::setFov(double fov)
{
    errFov = false;
    errViewAng = false;
    this->fov = fov;
    dViewAng = fov / px; // when the fov changes, recalculate the dViewAng
}

void OrbitPixParams::setAng(double viewAng)
{
    errFov = false;
    errViewAng = false;
    this->viewAng = viewAng;
}

void OrbitPixParams::setR(double r)
{
    errFov = false;
    errViewAng = false;
    this->r = r;
    maxFovCalc(); // when the r changes, recalculate the max allowed fov angle
    maxViewAngCalc(); // ... and the max allowed view angle
}

void OrbitPixParams::setPx(double px)
{
    this->px = px;
    dViewAng = fov / px; // when the number of pixels changes, recalculate the dViewAng
}

//-----------------------------------------------------------------------------
// GETTERS:
//-----------------------------------------------------------------------------

double OrbitPixParams::getmaxViewAng()
{
    return maxViewAng;
}

double OrbitPixParams::getMaxFov()
{
    return maxFov;
}

bool OrbitPixParams::getErrFov()
{
    return errFov;
}

bool OrbitPixParams::getErrViewAng()
{
    return errViewAng;
}

string OrbitPixParams::getErrMsg()
{
    return errMsg;
}

vector<double> OrbitPixParams::getPixVec()
{
    return pixVec;
}

vector<double> OrbitPixParams::getDAngSizeVec()
{
    return dAngSidesVec;
}

vector<double> OrbitPixParams::getLosVec()
{
    return losVec;
}

vector<double> OrbitPixParams::getAngVec()
{
    return angVec;
}


//-----------------------------------------------------------------------------
// PRINT TO FILE:
//-----------------------------------------------------------------------------

bool OrbitPixParams::printToFile(string fileName, string angMeas)
{
    FILE *f;
    double angi;
    stringstream angSs;
    string angPr;
    bool ok;

    f = fopen(fileName.c_str(), "w");
    if (f != NULL)
    {
        angSs << "angle" << " (" << angMeas << ")";
        angPr = angSs.str();
        fprintf(f, "%s \t %s \t %s \t %s \n", "pixel", angPr.c_str(), "LoS (km)", "Size (m)");
        fprintf(f, "%s \n", "-------------------------------------------------");
        for (int i = 0; i < px; i++)
        {
            if (angMeas == "rad")
                angi = angVec[i];
            else if (angMeas == "deg")
                angi = 180 * angVec[i] / PI;
            else if (angMeas == "grad")
                angi = 200 * angVec[i] / PI;

            fprintf(f, "%d \t %4.4f \t %4.4f \t %4.2f \n", i + 1, angi, losVec[i], pixVec[i] * 1000);
        }

        fclose(f);
        ok = true;
    }
    else
        ok = false;

    return ok;
}
