#include "BarlowUtils.h";

class ClawController
{
private:
    int _x;
    int _y;
    int xMax;
    int yMax;

    Sensor<SensorType::Digital> *xLim;
    Sensor<SensorType::Digital> *yLim;
    StepperMotor *lMot;
    StepperMotor *rMot;

public:
    ClawController(int limitSWPorts[2], int stepperPorts[2], bool zero = true);
    ~ClawController();
    int setPos(int x, int y);
    int moveAtAngle(float angle, int dist);
    int zero();
    int center() { return setPos(AVG(0, this->xMax), AVG(0, this->yMax)); };
};