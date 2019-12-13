#include "BarlowUtils.h";

class ClawController
{
private:
    int _x;
    int _y;
    int xMax;
    int yMax;

    Sensor *xLim;
    Sensor *yLim;
    StepperMotor *xMot;
    StepperMotor *yMot;

public:
    ClawController(int limitSWPorts[2], int stepperPorts[2], bool zero = true);
    ~ClawController();
    int setPos(int x, int y);
    int zero();
    int center() { return setPos(AVG(0, this->xMax), AVG(0, this->yMax)); };
};