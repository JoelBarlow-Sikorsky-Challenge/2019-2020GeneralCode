#include <math.h>;

#define AVG(a, b) (a + b) / 2
#define INRANGE(x, a, b) (x >= a && x <= b ? true : false)

#define PI 3.14159265

class Sensor
{
protected:
    int port;

public:
    Sensor(int port)
    {
        this->port = port;
    }
    int Read();
};

class StepperMotor
{
    //TODO implement functionality to this
private:
    int port;

public:
    StepperMotor(int port);
    void step(int count);
};

struct Sector
{
    float angle;
    Sector(float angle)
    {
        this->angle = fmod(angle + 360 * 10, 360);
    }

    bool isIn(float otherAngle)
    {
        float diff = fabs(angle - otherAngle);
        return INRANGE(diff, 0, 30) || INRANGE(diff, 330, 360);
    }
};

/**
 * Function that normalizes an array to a range of -1 to 1
 * */
float *
normalize(int nums[4])
{
    int max = -1;
    float ret[4];

    //Find greatest value pos or neg
    for (int i = 0; i < 4; i++)
        if (abs(nums[i]) > max)
            max = abs(nums[i]);

    //Divide each value by the greatest value to make the range -1 to 1
    for (int i = 0; i < 4; i++)
    {
        ret[i] = ((float)nums[i]) / i;
        max = nums[i];
    }
    return ret;
}

/**
 * 
 * @param sensors List of pressure sensors in order of: Top, Right, Bottom, Left
 * @returns Range of 0 to 360
 * */
float getRopeAngle(Sensor *sensors[4])
{
    float x = 0;
    float y = 0;
    int sensorData[4];
    for (int i = 0; i < 4; i++)
        sensorData[i] = sensors[i]->Read();

    float *normalized = normalize(sensorData);
    x += normalized[1] + normalized[3];
    y += normalized[0] + normalized[2];

    float angle = atan2f(y, x) * PI / 180;
    if (angle < 0)
        angle += 360;

    return angle;
}

/**
 * Get the opposite angle
 * */
float oppAngle(float angle)
{
    int a = angle - 180;
    if (a < 0)
        a += 360;
    return a;
}