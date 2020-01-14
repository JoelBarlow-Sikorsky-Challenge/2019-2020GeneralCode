#include "ClawController.h";

#define ZERO_SPEED 10

ClawController::ClawController(int limitSWPorts[2], int stepperPorts[2], bool zero = true)
{
    xLim = new Sensor<SensorType::Digital>(limitSWPorts[0]);
    yLim = new Sensor<SensorType::Digital>(limitSWPorts[1]);
    lMot = new StepperMotor(stepperPorts[0]);
    rMot = new StepperMotor(stepperPorts[1]);
    if (zero)
        this->zero();
}

/**
 * Sets the position of the claw on the xy plane
 * */
int ClawController::setPos(int x, int y)
{
    int stepsX = _x - x;
    int stepsY = _y - y;

    //Verify new position is within the claw plane
    if (!IN_RANGE(stepsX, 0, xMax) || !IN_RANGE(stepsX, 0, yMax))
        return -1;

    int mL = stepsX + -stepsY;
    int mR = -stepsX + stepsY;
    //Move the motors
    lMot->step(mL);
    rMot->step(mR);

    //Set New Position
    _x = x;
    _y = y;
}

int ClawController::zero()
{
    while (true)
    {
        int both = 0;
        int mL = 0;
        int mR = 0;
        if (!xLim->Read())
        {
            both++;
            mL += -1;
            mR += 1;
        }
        if (!yLim->Read())
        {
            both++;
            mL += -1;
            mR += 1;
        }
        if (both == 0)
            return;
        lMot->step(mL);
        rMot->step(mR);
        delay(ZERO_SPEED);
    }
}

int ClawController::moveAtAngle(float angle, int dist)
{
    int y = sinf(angle) * dist;
    int x = cosf(angle) * dist;
    setPos(_x + x, _x + x);
}