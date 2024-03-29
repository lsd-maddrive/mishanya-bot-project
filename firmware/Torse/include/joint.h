#ifndef INCLUDE_PART_ARM_DRIVER_H
#define INCLUDE_PART_ARM_DRIVER_H

#include "common.h"
#include "lld_bridge_system.h"
#include "PID.h"
#include "arm_encoder.h"
#include "lld_bb_driver.h"
#include "lld_red_driver.h"


typedef enum {
    LEFT = 0,
    RIGHT = 1,
    NONE_SIDE = 2
} arm_side_t;

typedef enum {
    ELBOW = 0,
    V_SHOULDER = 1,
    H_SHOULDER = 2,
    NONE = 3
} part_arm_type_t;

typedef struct {
    float min_angle;                              // min angle encored read
    float max_angle;                              // max angle encored read
}angle_lim_t;

typedef struct {
    float min_norm_angle;                        // min angle encored read
    float max_norm_angle;                        // max angle encored read
}angle_normalize_lim_t;

typedef struct {
    float shift_from_zero;                      // offset of zero minimum angle
    bool zero_between_angle;                    // flag indicating whether zero is betwenn the max and min angle
}normalize_info_t;

typedef struct {
    bool reach_target_angle;                     // target angle flag
    volatile float target_angle;                 // value of target angle
}target_angle_t;


typedef struct {
    angle_lim_t local_angle_lim;
    target_angle_t target_angle;
    uint8_t angle_dead_zone;              // deadzone of encoder
}arm_angle_t;

typedef struct {
  arm_encoder_t     arm_encoder;                  // encoder struct
  PID_t             arm_PID;                      // PID struct
  control_driver_t  control;
} traking_cs_t;

typedef struct{
  traking_cs_t      traking_cs;
  arm_angle_t       arm_angle;
} arm_info_t;

typedef struct {
  driver_t type;                                  // typedef (search for description in this file)
  void (* up) (arm_side_t, uint16_t);             // ptr function up
  void (* down) (arm_side_t, uint16_t);           // ptr function down
  void (* off) (arm_side_t);                      // ptr function off arm
  arm_info_t arm[2];                              // two arms
  angle_lim_t global_angle_lim;
  float working_interval;
} joint_t;


void joint_up(arm_side_t side, joint_t *joint, uint16_t period);
void joint_down(arm_side_t side, joint_t *joint, uint16_t period);
void joint_off (arm_side_t side, joint_t *joint);



#endif
