//#include "elbow_driver.h"
//
//
//#define DRIVER RED
//
//// *******************arm driver PWM config******************* //
//
//#define PWM_frequency		500000
//#define PWM_period			10000
//
//
//
//// *******************arm driver PWM config******************* //
//
//
//const arm_encoder_t right_elbow_encoder =
//        {
//                .encoder_ptr = &SPID2,
//                .encoder_pins = {
//                        .cs_encoder = CS_RIGHT_ENCODER_ELBOW,
//                        .clk_encoder = CLK_ENCODER_RIGHT,
//                        .miso_encoder = MISO_ENCODER_RIGHT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//
//const arm_encoder_t left_elbow_encoder =
//        {
//                .encoder_ptr = &SPID1,
//                .encoder_pins = {
//                        .cs_encoder = CS_LEFT_ENCODER_ELBOW,
//                        .clk_encoder = CLK_ENCODER_LEFT,
//                        .miso_encoder = MISO_ENCODER_LEFT
//                },
//                .encoder_conf = {
//                        .cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0,
//                        .end_cb = NULL
//                }
//        };
//
//// **********************close sys config********************** //
//
//#define ENCODER_DEADZONE 1
//
//
//// ***************************PID coef************************** //
//
//const PID_t elbow_PID = {
//  .coef = {.kp = 3500, .ki = 500, .kd = 0},
//  .error = {.P = 0, .prev_P = 0, .I = 0, .D = 0}
//};
//
//// ***************************PID coef************************** //
//
//// ***************************angle lim************************* //
//
//const angle_lim_t right_angle_lim_elbow= {
//  .max_angle = 62.6660F,
//  .min_angle = 22.9394F
//};
//
//const angle_lim_t left_angle_lim_elbow = {
//  .max_angle = 18.2812F,
//  .min_angle = 334.9511F
//};
//
//// ***************************angle lim************************** //
//
//
//// ***********************left arm config*********************** //
//
//const line_driver_t left_elbow_line = {
//		.alt_func_num = 1,
//		.ch_pwm_num = 2,
//		.line_1 = LEFT_UP_ELBOW,
//		.line_2 = LEFT_DOWN_ELBOW,
//		.pwm_line = LEFT_PWM_ELBOW
//};
//
//const pwm_ctx_t left_elbow_pwm_ctx =
//{
//		.control = left_elbow_line,
//		.driver_ptr = &PWMD1
//};
//
//const control_driver_t left_elbow_control =
//{
//		.bridge_shoulder[ONCE_SHOULDER] = left_elbow_pwm_ctx
//};
//
//// ***********************left arm config*********************** //
//
//
//// ***********************right arm config*********************** //
//
//const line_driver_t right_elbow_line = {
//		.alt_func_num = 3,
//		.ch_pwm_num = 3,
//		.line_1 = RIGHT_UP_ELBOW,
//		.line_2 = RIGHT_DOWN_ELBOW,
//		.pwm_line = RIGHT_PWM_ELBOW
//};
//
//const pwm_ctx_t right_elbow_pwm_ctx =
//{
//		.control = right_elbow_line,
//		.driver_ptr = &PWMD8
//};
//
//const control_driver_t right_elbow_control =
//{
//		.bridge_shoulder[ONCE_SHOULDER] = right_elbow_pwm_ctx
//};
//
//// ***********************final struct declaration*********************** //
//
//// *** tracking structures for left arm *** //
//const traking_cs_t left_cs_elbow = {
//	.control = left_elbow_control,
//	.arm_PID = elbow_PID,
//	.arm_encoder = left_elbow_encoder
//};
//
//
//
//// *** tracking structures for right arm *** //
//const traking_cs_t right_cs_elbow = {
//	.control = right_elbow_control,
//	.arm_PID = elbow_PID,
//	.arm_encoder = right_elbow_encoder
//};
//
//const arm_angle_t left_angle = {
//		.angle_dead_zone = ENCODER_DEADZONE,
//		.angle_lim = left_angle_lim_elbow
//};
//
//const arm_angle_t right_angle = {
//		.angle_dead_zone = ENCODER_DEADZONE,
//		.angle_lim = right_angle_lim_elbow
//};
//
//// structure for both arms
//const arm_info_t elbow_info_left =
//{
//		.arm_angle = left_angle,
//		.traking_cs = left_cs_elbow
//};
//
//const arm_info_t elbow_info_right =
//{
//		.arm_angle = right_angle,
//		.traking_cs = right_cs_elbow
//};
//
//
//// ***********************final struct declaration*********************** //
//
//arm_ctx_t elbow_driver;
///**
// * @details initialize arm driver
// */
//void elbow_init(void)
//{
//	static bool isInitialized   = false;
//
//	if (isInitialized)
//		return;
//
//	elbow_driver.type = DRIVER;
//	elbow_driver.down = &elbow_down;
//	elbow_driver.up = &elbow_up;
//	elbow_driver.off = &elbow_off;
//
//	elbow_driver.arm[LEFT] = elbow_info_left;
//	elbow_driver.arm[RIGHT] = elbow_info_right;
//
//	driver_init(&elbow_driver);
//	acs_init(&elbow_driver);
//}
//
//
///**
// * @details the function controls the raising of the arm up
// * @param[in] side - left or right side of hand
// * @param[in] period - PWM period
// */
//void elbow_up(arm_side_t side, uint16_t period)
//{
//	arm_up(side, &elbow_driver, period);
//}
//
///**
// * @details the function controls the raising of the arm down
// * @param[in] side - left or right side of hand
// * @param[in] period - PWM period
// */
//void elbow_down(arm_side_t side, uint16_t period)
//{
//	arm_down(side, &elbow_driver, period);
//}
//
///**
// * @details the function disables the selected arm
// * @param[in] side - left or right side of hand
// */
//void elbow_off(arm_side_t side)
//{
//	arm_off(side, &elbow_driver);
//}
//
///**
// * @details the function set input angle
// * @param[in] side - left or right side of hand
// * @param[in] target_angle - setpoint angle
// */
//void elbow_set_angle(float target_angle, arm_side_t side)
//{
//  acs_set_angle(target_angle, side, elbow_driver.arm);
//}
//
///**
// * @details the function update current state of arm
// * @param[in] dt - function call period
// */
//void elbow_update_angle(float dt)
//{
//  acs_update_angle(dt, RIGHT, &elbow_driver);
//  acs_update_angle(dt, LEFT, &elbow_driver);
//}
//
///**
// * @details the function get encoder struct
// * @param[in] encoder_side - left of right encoder
// * @return encoder struct
// */
//
////arm_encoder_t elbow_get_encoder_ctx(arm_side_t encoder_side)
////{
////    switch (encoder_side) {
////        case LEFT:
////            return left_elbow_encoder;
////            break;
////        case RIGHT:
////            return right_elbow_encoder;
////            break;
////        default:
////        	break;
////    }
////}
