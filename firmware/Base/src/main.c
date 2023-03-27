#include <common.h>
#include <test.h>

static void testsRoutines(void)
{
    #if(MAIN_PROGRAM   == PROGRAM_TEST_ENCODER_BASE_ALL)
        test_encoder_base_all();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ENCODER_BASE_1)
        test_encoder_base(ENCODER_1);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ENCODER_BASE_2)
       test_encoder_base(ENCODER_2);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ENCODER_BASE_3)
       test_encoder_base(ENCODER_3);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ODOMETRY_BASE_ENC_1)
       testOdometryBase(ENCODER_1);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ODOMETRY_BASE_ENC_1)
       testOdometryBase(ENCODER_1);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ODOMETRY_BASE_ENC_2)
       testOdometryBase(ENCODER_2);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ODOMETRY_BASE_ENC_3)
       testOdometryBase(ENCODER_3);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_ODOMETRY_BASE_ALL)
       testOdometryBaseAll();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_1)
       testlldMotor(MOTOR_1);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_2)
       testlldMotor(MOTOR_2);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_3)
       testlldMotor(MOTOR_3);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_ALL)
       testlldMotorAll();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_PER_1)
       testlldMotorPer(MOTOR_1);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_PER_2)
       testlldMotorPer(MOTOR_2);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_PER_3)
       testlldMotorPer(MOTOR_3);
    #elif(MAIN_PROGRAM == PROGRAM_TEST_MOTOR_PER_ALL)
       testlldMotorPerAll();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_SPEED_FILTER_GRAPHS)
        test_speed_filter_graphs();
    #elif(MAIN_PROGRAM == PROGRAM_TEST_CLOSED_SYSTEM_DRIVE)
        testPISpeedMotor();
    #endif
}

int main(void)
{
    halInit();
    chSysInit();
    #if(MAIN_PROGRAM != PROGRAM_MASTER)
        testsRoutines();
    #endif
}
