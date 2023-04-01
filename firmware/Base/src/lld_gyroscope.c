#include "lld_gyroscope.h"
#include "serial.h"

static bool flagInitGyro       = false;

float        angleGyroXYZ[3]   = {0, 0, 0};
float        angularSpeed[3]   = {0, 0, 0};

static THD_WORKING_AREA(GyroThread, 256);
static THD_FUNCTION(CalculationAngle, arg)
{
    arg = arg;

    systime_t time = chVTGetSystemTime();
    while(1) {
        uint8_t i = 0;
        msg_t msg = gyroscopeRead(angularSpeed);

        if(msg == MSG_OK) {
            for(i = 0; i < 3; i++) {
                angleGyroXYZ[i] += angularSpeed[i] * DELTA_TIME_GYRO;

                if(angleGyroXYZ[i] > 360) {
                    angleGyroXYZ[i] -= 360;
                }
                else if(angleGyroXYZ[i] < 0) {
                    angleGyroXYZ[i] += 360;
                }
            }
        }
        else {
            i2cStopDriver();
            initI2C();
            dbgprintf("angle X:%d angle Y:%d angle Z:%d\n\r", -1, -1, -1);
        }
        time = chThdSleepUntilWindowed( time, time + TIME_MS2I(DELTA_TIME_GYRO));
    }
}

void gyroscopeInit(uint8_t priority) {

    if(flagInitGyro) {
        return;
    }

    initI2C();
    uint8_t startBuf[2];
    debug_stream_init();
    startBuf[0] = CTRL_REG2;
    startBuf[1] = VALUE_CTRL_REG2;

    msg_t msg = i2cSimpleWrite(ADDRESS_GYROSCOPE, startBuf, sizeof(startBuf), 1000);
    if(msg!=MSG_OK)
        palSetLine(LINE_LED1);

    chThdCreateStatic(GyroThread, sizeof(GyroThread), NORMALPRIO+priority, CalculationAngle, NULL);
    flagInitGyro = true;

}

msg_t gyroscopeRead(float* rawValues) {
    uint8_t gyroValues[6] = {0};
    uint8_t i = 0;

    msg_t msg = i2cRegisterRead(ADDRESS_GYROSCOPE, DATA_REGISTER, gyroValues, sizeof(gyroValues), 10000);
    for(i = 0; i < 3; i++) {
        rawValues[i] = (float)((uint16_t)(gyroValues[i * 2]) | ((uint16_t)(gyroValues[(i * 2) + 1]) << 8));
        dbgprintf("X1:%d X2:%d Y1:%d Y2:%d Z1:%d Z2:%d\n\r", (int)gyroValues[0],
                  (int)gyroValues[1],  (int)gyroValues[2], (int)gyroValues[3], (int)gyroValues[4], (int)gyroValues[5]);
    }


    return msg;

}

float getAngleGyro(GyroAxis axis) {
    return angleGyroXYZ[axis];
}

float getAngularSpeedGyro(GyroAxis axis) {
    return angularSpeed[axis];
}