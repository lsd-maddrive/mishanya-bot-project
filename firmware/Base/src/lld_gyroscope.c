#include "lld_gyroscope.h"
#include "serial.h"

static bool flagInitGyro       = false;

float        angleGyroXYZ[3]   = {0, 0, 0};
float        angularSpeed[3]   = {0, 0, 0};
float        gyroDreif[3]      = {0, 0, 0};

static THD_WORKING_AREA(GyroThread, 256);
static THD_FUNCTION(CalculationAngle, arg)
{
    arg = arg;

    systime_t time = chVTGetSystemTime();
    while (1) {
        uint8_t i = 0;
        msg_t msg = readGyroSpeed(angularSpeed);

        if (msg == MSG_OK) {
            for (i = 0; i < 3; i++) {
                angularSpeed[i] -= gyroDreif[i];

                if (fabs(angularSpeed[i]) < 0.01)
                    angularSpeed[i] = 0;

                angleGyroXYZ[i] += (angularSpeed[i] * DELTA_TIME_GYRO / 1000);

                if (angleGyroXYZ[i] > 360) {
                    angleGyroXYZ[i] -= 360;
                }
                else if (angleGyroXYZ[i] < 0) {
                    angleGyroXYZ[i] += 360;
                }
            }
            palClearLine(LINE_LED3);
        }
        else {
            initI2C();
            palSetLine(LINE_LED3);
        }
        time = chThdSleepUntilWindowed(time, time + TIME_MS2I(DELTA_TIME_GYRO));
    }
}

void gyroscopeInit(uint8_t priority) {

    if (flagInitGyro) {
        return;
    }

    initI2C();
    uint8_t startBuf[2];
    startBuf[0] = CTRL_REG2;
    startBuf[1] = VALUE_CTRL_REG2;

    msg_t msg = i2cSimpleWrite(ADDRESS_GYROSCOPE, startBuf, sizeof(startBuf), 1000);
    if (msg != MSG_OK)
        palSetLine(LINE_LED1);
    chThdSleepMilliseconds(100);
    calculateDreifGyro(gyroDreif);
    chThdCreateStatic(GyroThread, sizeof(GyroThread), NORMALPRIO+priority, CalculationAngle, NULL);
    flagInitGyro = true;
}

msg_t gyroscopeRead(int16_t* rawValues) {
    uint8_t gyroValues[6] = {0};
    uint8_t i = 0;

    msg_t msg = i2cRegisterRead(ADDRESS_GYROSCOPE, DATA_REGISTER, gyroValues, sizeof(gyroValues), 10000);
    for (i = 0; i < 3; i++) {
        rawValues[i] = (int16_t)((uint16_t)(gyroValues[i * 2]) | ((uint16_t)(gyroValues[(i * 2) + 1]) << 8));
    }
    return msg;
}

msg_t readGyroSpeed(float *axisSpeed)
{
    int16_t gyroAxisValues[3] = {0, 0, 0};
    uint8_t i = 0;
    msg_t msg = gyroscopeRead(gyroAxisValues);
    if (msg == MSG_OK) {
        for (i = 0; i < 3; i++) {
            axisSpeed[i] = (float) gyroAxisValues[i] * 0.07;
        }
    }
    return msg;
    }

msg_t calculateDreifGyro(float* gyroRawData)
{
    msg_t msg = MSG_OK;
    int16_t tempBuf[15][3] = {{0}};
    int16_t superTemp[3]   = {0, 0, 0};
    uint8_t i, j;
    float xMean = 0, yMean = 0, zMean = 0;
    for (i = 0; i < 15; i++)
    {
        msg = gyroscopeRead(superTemp);
        if (msg == MSG_OK)
            for (j = 0; j < 3; j++)
            {
                tempBuf[i][j] = superTemp[j];
            }
    }
    for (i = 0; i < 15; i++)
    {
        xMean += tempBuf[i][0];
        yMean += tempBuf[i][1];
        zMean += tempBuf[i][2];
    }
    gyroRawData[0] = (xMean / 15) * 0.07;
    gyroRawData[1] = (yMean / 15) * 0.07;
    gyroRawData[2] = (zMean / 15) * 0.07;

    return msg;
}

float getAngleGyro(GyroAxis axis) {
    return angleGyroXYZ[axis];
}

float getAngularSpeedGyro(GyroAxis axis) {
    return angularSpeed[axis];
}