PROJECT_MODULES = src/serial.c \
		  src/encoder_base.c \
		  src/odometry_base.c \
		  src/cnfg_peripherals.c \
		  src/motor.c \
		  src/closed_system_drive.c \
		  src/i2c.c                 \
		  src/lld_gyroscope.c        \
		  src/kinematics.c            \
		  ../robo_lib/lld_red_driver.c \
		  ../robo_lib/lld_bb_driver.c \

PROJECT_TESTS   = tests/test_encoder_base.c \
				  tests/test_odometry_base.c \
				  tests/test_lld_motor.c \
				  tests/test_speed_filter_graphs.c \
				  tests/test_closed_system_drive.c \
				  tests/test_i2c.c \
				  tests/test_lld_gyroscope.c \
				  tests/test_kinematics.c         \
                  
# C source files
PROJECT_CSRC 	=  src/main.c \
					$(PROJECT_MODULES) $(PROJECT_TESTS)			 
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include/ \
				  ../robo_lib/ \
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1    

# Additional .mk files are included here
