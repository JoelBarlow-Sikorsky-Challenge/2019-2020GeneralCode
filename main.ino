#include "BarlowUtils.h";
#include "ClawController.h";

#define LIM_PORTS 3, 4
#define STEPPER_PORTS A0, A1

#define P1 A2
#define P2 A3
#define P3 A4
#define P4 A5

#define COUNTER_DIST 5

Sector lastRope = NULL;

Sensor<SensorType::Analog> *pressureSensors[4];

ClawController *controller;

void setup()
{
    pressureSensors[0] = new Sensor<SensorType::Analog>(P1);
    pressureSensors[1] = new Sensor<SensorType::Analog>(P2);
    pressureSensors[2] = new Sensor<SensorType::Analog>(P3);
    pressureSensors[3] = new Sensor<SensorType::Analog>(P4);
    controller = new ClawController(new int[2]{LIM_PORTS}, new int[2]{STEPPER_PORTS});
    lastRope = Sector(getRopeAngle(pressureSensors));
}

void loop()
{
    Sector currentRope = Sector(getRopeAngle(pressureSensors));

    if (currentRope.isIn(lastRope))
        controller->moveAtAngle(oppAngle(currentRope.angle), COUNTER_DIST);
    lastRope = currentRope;
}