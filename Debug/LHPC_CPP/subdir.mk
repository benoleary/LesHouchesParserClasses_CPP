################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LHPC_CPP/LhefParser.cpp \
../LHPC_CPP/LhefParserExample.cpp \
../LHPC_CPP/SlhaParser.cpp \
../LHPC_CPP/SlhaParserExample.cpp 

OBJS += \
./LHPC_CPP/LhefParser.o \
./LHPC_CPP/LhefParserExample.o \
./LHPC_CPP/SlhaParser.o \
./LHPC_CPP/SlhaParserExample.o 

CPP_DEPS += \
./LHPC_CPP/LhefParser.d \
./LHPC_CPP/LhefParserExample.d \
./LHPC_CPP/SlhaParser.d \
./LHPC_CPP/SlhaParserExample.d 


# Each subdirectory must supply rules for building sources it contributes
LHPC_CPP/%.o: ../LHPC_CPP/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


