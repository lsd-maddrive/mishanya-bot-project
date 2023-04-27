PROJECT_MODULES = src/serial.c \
		  src/lld_control_servo.c \
		  src/elbow_driver.c \
		  src/arm_control_system.c \
		  src/joint.c \
		  src/arm_encoder.c \
	      src/vertical_shoulder_driver.c \
	      src/horizontal_shoulder_driver.c \
	      src/low_level.c \
	      src/arm_kinematic.c \
	      src/arm_calibration.c \
	      src/torse_proto.c \
	      src/message_handler.c \
	      src/control_system_handler.c \
	      ../robo_lib/PID.c \
		  ../robo_lib/lld_bb_driver.c \
		  ../robo_lib/lld_red_driver.c \
		  ../robo_lib/flash_f7.c \
		  ../robo_lib/crc32.c \
		  ../robo_lib/mproto.c \

PROJECT_TESTS   = tests/test_lld_control_servo.c tests/test_nonlinear_servo.c \
		  tests/test_arm_high_function.c \
		  tests/test_arm_control_system.c \
		  tests/test_PID.c \
		  tests/test_encoder.c \
		  tests/test_arm_kinematic.c \

# C source files
PROJECT_CSRC 	=  src/main.c \
					$(PROJECT_MODULES) $(PROJECT_TESTS)
# C++ source files
PROJECT_CPPSRC 	=
# Directories to search headers in
PROJECT_INCDIR	= include/ \
				  ../robo_lib/
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1

# Additional .mk files are included here