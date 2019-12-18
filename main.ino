#include "BarlowUtils.h";
#include "ClawController.h";

#define LIM_PORTS 3, 4
#define STEPPER_PORTS A0, A1
#define PRESSURE_PORTS A2, A3, A4, A5

#define COUNTER_DIST 5

Sector lastRope = NULL;

Sensor<SensorType::Analog> *pressureSensors[4];

ClawController *controller;

int cooldown = 5;

void setup()
{
    const int pins[] = {PRESSURE_PORTS};

    for (int i = 0; i < 4; i++)
        pressureSensors[i] = new Sensor<SensorType::Analog>(pins[i]);

    controller = new ClawController(new int[2]{LIM_PORTS}, new int[2]{STEPPER_PORTS});
    lastRope = Sector(getRopeAngle(pressureSensors));
}

void loop()
{
    Sector currentRope = Sector(getRopeAngle(pressureSensors));

    //If the cooldown has ended return
    if (cooldown <= 0)
    {
        if (currentRope.isIn(lastRope))
        {
            controller->moveAtAngle(oppAngle(currentRope.angle), COUNTER_DIST);
            cooldown = 6;
        }
    }
    else
    {
        cooldown--;
    }
    lastRope = currentRope;
}