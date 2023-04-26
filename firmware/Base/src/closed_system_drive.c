#include "closed_system_drive.h"
#include "serial.h"

/* 5 - 100% // TODO пересчитать для об/сек
 * 1    - 20% */
#define COEF_SPEED (float)20
#define MAX_SPEED  (float)5
#define MIN_SPEED  (float)(-5)

uint8_t driveInit         = 0;

RegulatorValueMotor regulatorMotor1;
RegulatorValueMotor regulatorMotor2;
RegulatorValueMotor regulatorMotor3;

PIregulator motorForward = {
    .kp              = 0.3,
    .ki              = 0.1,
    .integSaturation = 80 / COEF_SPEED,
    .pDeadZone       = 0,
};

PIregulator motorRevs = {
    .kp              = 0.3,
    .ki              = 0.1,
    .integSaturation = 80 / COEF_SPEED,
    .pDeadZone       = 0,
};

static THD_WORKING_AREA(regulator, 256);
static THD_FUNCTION(CalculationReg, arg){
    arg = arg;
    systime_t time = chVTGetSystemTimeX();
    while (1)
    {
        regulatorMotor1.realSpeed = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_1);
        regulatorMotor1.pErrSpeed = regulatorMotor1.refSpeed - regulatorMotor1.realSpeed;

        if (regulatorMotor1.refSpeed < 0)
        {
            regulatorMotor1.intgSpeed         += regulatorMotor1.pErrSpeed * motorRevs.ki;
            regulatorMotor1.intgSpeed          = CLIP_VALUE(regulatorMotor1.intgSpeed,
                                                            -motorForward.integSaturation, motorForward.integSaturation);
            regulatorMotor1.speedControlValue  = (motorRevs.kp * regulatorMotor1.pErrSpeed + regulatorMotor1.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor1.refSpeed > 0)
        {
            regulatorMotor1.intgSpeed         += regulatorMotor1.pErrSpeed * motorForward.ki;
            regulatorMotor1.intgSpeed          = CLIP_VALUE(regulatorMotor1.intgSpeed,
                                                            -motorRevs.integSaturation, motorRevs.integSaturation);
            regulatorMotor1.speedControlValue  = (motorForward.kp * regulatorMotor1.pErrSpeed + regulatorMotor1.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor1.refSpeed == 0)
        {
            if (fabsf(regulatorMotor1.refSpeed - regulatorMotor1.realSpeed) > 5)
            {
                if (regulatorMotor1.realSpeed > 0)
                {
                    regulatorMotor1.intgSpeed         += regulatorMotor1.pErrSpeed * motorRevs.ki;
                    regulatorMotor1.intgSpeed          = CLIP_VALUE(regulatorMotor1.intgSpeed,
                                                                    -motorRevs.integSaturation, motorRevs.integSaturation);
                    regulatorMotor1.speedControlValue  = (motorRevs.kp * regulatorMotor1.pErrSpeed + regulatorMotor1.intgSpeed) * COEF_SPEED;
                }
                else
                {
                    regulatorMotor1.intgSpeed         += regulatorMotor1.pErrSpeed * motorForward.ki;
                    regulatorMotor1.intgSpeed          = CLIP_VALUE(
                        regulatorMotor1.intgSpeed, -motorForward.integSaturation, motorForward.integSaturation);
                    regulatorMotor1.speedControlValue  = (motorForward.kp * regulatorMotor1.pErrSpeed + regulatorMotor1.intgSpeed) * COEF_SPEED;
                }
            }
            else
            {
                ResetSpeedRegulatorWheel1();
                regulatorMotor1.speedControlValue = 0;
            }
        }

        regulatorMotor2.realSpeed = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_2);
        regulatorMotor2.pErrSpeed = regulatorMotor2.refSpeed - regulatorMotor2.realSpeed;

        if (regulatorMotor2.refSpeed < 0)
        {
            regulatorMotor2.intgSpeed         += regulatorMotor2.pErrSpeed * motorRevs.ki;
            regulatorMotor2.intgSpeed          = CLIP_VALUE(regulatorMotor2.intgSpeed,
                                                            -motorRevs.integSaturation, motorRevs.integSaturation);
            regulatorMotor2.speedControlValue  = (motorRevs.kp * regulatorMotor2.pErrSpeed + regulatorMotor2.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor2.refSpeed > 0)
        {
            regulatorMotor2.intgSpeed         += regulatorMotor2.pErrSpeed * motorForward.ki;
            regulatorMotor2.intgSpeed          = CLIP_VALUE(regulatorMotor2.intgSpeed,
                                                            -motorForward.integSaturation, motorForward.integSaturation);
            regulatorMotor2.speedControlValue  = (motorForward.kp * regulatorMotor2.pErrSpeed + regulatorMotor2.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor2.refSpeed == 0)
        {
            if (fabsf(regulatorMotor2.refSpeed - regulatorMotor2.realSpeed) > 5)
            {
                if (regulatorMotor2.realSpeed > 0)
                {
                    regulatorMotor2.intgSpeed         += regulatorMotor2.pErrSpeed * motorRevs.ki;
                    regulatorMotor2.intgSpeed          = CLIP_VALUE(regulatorMotor2.intgSpeed,
                                                                    -motorRevs.integSaturation, motorRevs.integSaturation);
                    regulatorMotor2.speedControlValue  = (motorRevs.kp * regulatorMotor2.pErrSpeed + regulatorMotor2.intgSpeed) * COEF_SPEED;
                }
                else
                {
                    regulatorMotor2.intgSpeed         += regulatorMotor2.pErrSpeed * motorForward.ki;
                    regulatorMotor2.intgSpeed          = CLIP_VALUE(
                        regulatorMotor2.intgSpeed, -motorForward.integSaturation, motorForward.integSaturation);
                    regulatorMotor2.speedControlValue  = (motorForward.kp * regulatorMotor2.pErrSpeed + regulatorMotor2.intgSpeed)   * COEF_SPEED;
                }
            }
            else
            {
                ResetSpeedRegulatorWheel2();
                regulatorMotor2.speedControlValue = 0;
            }
        }
        regulatorMotor3.realSpeed = odometryGetWheelSpeed(REVS_PER_SEC, ENCODER_3);
        regulatorMotor3.pErrSpeed = regulatorMotor3.refSpeed - regulatorMotor3.realSpeed;
        if (regulatorMotor3.refSpeed < 0)
        {
            regulatorMotor3.intgSpeed        += regulatorMotor3.pErrSpeed * motorRevs.ki;
            regulatorMotor3.intgSpeed         = CLIP_VALUE(regulatorMotor3.intgSpeed,
                                                           -motorRevs.integSaturation, motorRevs.integSaturation);
            regulatorMotor3.speedControlValue = (motorRevs.kp * regulatorMotor3.pErrSpeed + regulatorMotor3.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor3.refSpeed > 0)
        {
            regulatorMotor3.intgSpeed         += regulatorMotor3.pErrSpeed * motorForward.ki;
            regulatorMotor3.intgSpeed          = CLIP_VALUE(regulatorMotor3.intgSpeed,
                                                            -motorForward.integSaturation, motorForward.integSaturation);
            regulatorMotor3.speedControlValue  = (motorForward.kp * regulatorMotor3.pErrSpeed + regulatorMotor3.intgSpeed) * COEF_SPEED;
        }
        else if (regulatorMotor3.refSpeed == 0)
        {
            if (fabsf(regulatorMotor3.refSpeed - regulatorMotor3.realSpeed) > 5)
            {
                if (regulatorMotor3.realSpeed > 0)
                {
                    regulatorMotor3.intgSpeed        += regulatorMotor3.pErrSpeed * motorRevs.ki;
                    regulatorMotor3.intgSpeed         = CLIP_VALUE(regulatorMotor3.intgSpeed,
                                                                   -motorRevs.integSaturation, motorRevs.integSaturation);
                    regulatorMotor3.speedControlValue = (motorRevs.kp * regulatorMotor3.pErrSpeed + regulatorMotor3.intgSpeed) * COEF_SPEED;
                }
                else
                {
                    regulatorMotor3.intgSpeed         += regulatorMotor3.pErrSpeed * motorForward.ki;
                    regulatorMotor3.intgSpeed          = CLIP_VALUE(
                        regulatorMotor3.intgSpeed, -motorForward.integSaturation, motorForward.integSaturation);
                    regulatorMotor3.speedControlValue  = (motorForward.kp * regulatorMotor3.pErrSpeed + regulatorMotor3.intgSpeed) * COEF_SPEED;
                }
            }
            else
            {
                ResetSpeedRegulatorWheel3();
                regulatorMotor3.speedControlValue = 0;
            }
        }

        lldSetMotorPower(MOTOR_1, regulatorMotor1.speedControlValue, 1);
        lldSetMotorPower(MOTOR_2, regulatorMotor2.speedControlValue, 1);
        lldSetMotorPower(MOTOR_3, regulatorMotor3.speedControlValue, 1);

        time = chThdSleepUntilWindowed(time, TIME_MS2I(20) + time);
    }
}

void driveCSInit(uint8_t prio){
    if (driveInit)
    {
        return;
    }
    lldMotorInit(MOTOR_1);
    lldMotorInit(MOTOR_2);
    lldMotorInit(MOTOR_3);
    odometryInit();
    debug_stream_init();
    chThdCreateStatic(regulator, sizeof(regulator), NORMALPRIO + prio, CalculationReg, NULL);
    driveInit = 1;
}

void setRefSpeed(type_motor motor_n, float speed, SpeedUnits units){
    speed = CLIP_VALUE(speed, MIN_SPEED, MAX_SPEED);
    if (motor_n == MOTOR_1) {
        regulatorMotor1.refSpeed = speed * units;
    }
    else if (motor_n == MOTOR_2)
    {
        regulatorMotor2.refSpeed = speed * units;
    }
    else if (motor_n == MOTOR_3)
    {
        regulatorMotor3.refSpeed = speed * units;
    }
}

void ResetSpeedRegulatorWheel1(void)
{
    regulatorMotor1.refSpeed          = 0;
    regulatorMotor1.speedControlValue = 0;
    regulatorMotor1.intgSpeed         = 0;
    regulatorMotor1.pErrSpeed         = 0;
}

void ResetSpeedRegulatorWheel2(void)
{
    regulatorMotor2.refSpeed          = 0;
    regulatorMotor2.speedControlValue = 0;
    regulatorMotor2.intgSpeed         = 0;
    regulatorMotor2.pErrSpeed         = 0;
}
void ResetSpeedRegulatorWheel3(void)
{
    regulatorMotor3.refSpeed          = 0;
    regulatorMotor3.speedControlValue = 0;
    regulatorMotor3.intgSpeed         = 0;
    regulatorMotor3.pErrSpeed         = 0;
}
