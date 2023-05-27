#include "test.h"
#include "serial.h"
#include "hal_queues.h"
#include "crc8.h"
#include "kinematics.h"

static const SerialConfig sdcfg = {
        .speed  = 115200,
        .cr1    = 0,
        .cr2    = 0,
        .cr3    = 0
};

void testJoystick(void) {
    debug_stream_init();
    initKinematics();
    sdStart(&SD4, &sdcfg);
    palSetPadMode(GPIOD, 0, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOD, 1, PAL_MODE_ALTERNATE(8));
    uint8_t readMagic      = 0;
    uint8_t crcRead        = 0;
    uint8_t crc            = 0;
    float realSpeed1       = 0;
    float realSpeed2       = 0;
    float realSpeed3       = 0;
    float realAngle        = 0;
    const uint8_t MAGIC[3] = {0x1f, 0x2b, 0x3b};
    uint8_t buf[12]        = {};
    float  valueSpeed[3]   ={0, 0, 0};
    uint8_t i              = 0;
    systime_t time         = chVTGetSystemTime();
    while (1) {
        for (i = 0; i < 3; ++i){
            sdRead(&SD4, (uint8_t*)&readMagic, 1);
            if (readMagic != MAGIC[i]){
                i = 0;
            }
        }
        sdRead(&SD4, (uint8_t*)&buf, 12);
        sdRead(&SD4, (uint8_t *)&crcRead, 1);
        crc = Crc8((uint8_t*)buf, sizeof(buf));
        if (crc == crcRead) {
            memcpy(valueSpeed, buf, sizeof(buf));
            setBaseSpeed(valueSpeed[0], valueSpeed[1], valueSpeed[2]);
           // dbgprintf("vx:%d vy:%d w:%d\n\r", (int32_t)(valueSpeed[0] * 100), (int32_t)(valueSpeed[1] * 100), (int32_t)(valueSpeed[2] * 100));
            realSpeed1  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_1);
            realSpeed2  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_2);
            realSpeed3  = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_3);
            realAngle   = getAngleGyro(Z);

            sdWrite(&SD3, (uint8_t *)&valueSpeed, 12);
            sdWrite(&SD3, (uint8_t*)&realSpeed1,  4);
            sdWrite(&SD3, (uint8_t*)&realSpeed2,  4);
            sdWrite(&SD3, (uint8_t*)&realSpeed3,  4);
            sdWrite(&SD3, (uint8_t*)&realAngle, 4);

            time = chThdSleepUntilWindowed(time, time + TIME_MS2I(10));
        }
    }
}
