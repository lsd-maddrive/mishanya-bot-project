PROJECT_MODULES = src/encoder.c \
				  src/serial.c \
				  src/PID.c \

PROJECT_TESTS   = tests/test_encoder.c \

# C source files
PROJECT_CSRC 	=  src/main.c \
					$(PROJECT_MODULES) $(PROJECT_TESTS)			 
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include/
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1    

# Additional .mk files are included here
