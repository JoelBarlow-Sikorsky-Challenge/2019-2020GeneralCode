#include "ClawController.h";

#define ZERO_SPEED 10

ClawController::ClawController(int limitSWPorts[2], int stepperPorts[2], bool zero = true)
{
    xLim = new Sensor(limitSWPorts[0]);
    yLim = new Sensor(limitSWPorts[1]);
    xMot = new StepperMotor(stepperPorts[0]);
    yMot = new StepperMotor(stepperPorts[1]);
    if (zero)
        this->zero();
}

/**
 * Sets the position of the claw on the xy plane
 * */
int ClawController::setPos(int x, int y)
{
    int mX = _x - x;
    int mY = _y - y;

    //Verify new position is within the claw plane
    if (!INRANGE(mX, 0, xMax) || !INRANGE(mX, 0, yMax))
        return -1;

    //Move the motors
    xMot->step(mX);
    yMot->step(mY);

    //Set New Position
    _x = x;
    _y = y;
}

int ClawController::zero()
{
    while (true)
    {
        int both = 0;
        if (!xLim->Read())
        {
            both++;
            xMot->step(-1);
        }
        if (!yLim->Read())
        {
            both++;
            yMot->step(-1);
        }
        if (both == 0)
            return;
        delay(ZERO_SPEED);
    }
}