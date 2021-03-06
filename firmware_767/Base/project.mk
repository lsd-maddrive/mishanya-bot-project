PROJECT_MODULES = src/serial.c \
		  src/encoder_base.c \
	         
PROJECT_TESTS   = tests/test_encoder_base.c \
                  
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
