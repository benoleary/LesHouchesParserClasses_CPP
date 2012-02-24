################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.cpp \
../LHPC_CPP/ParticleCodesAndData/PdgData.cpp \
../LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.cpp 

OBJS += \
./LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.o \
./LHPC_CPP/ParticleCodesAndData/PdgData.o \
./LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.o 

CPP_DEPS += \
./LHPC_CPP/ParticleCodesAndData/NineDigitSlhaCodes.d \
./LHPC_CPP/ParticleCodesAndData/PdgData.d \
./LHPC_CPP/ParticleCodesAndData/SevenDigitSlhaCodes.d 


# Each subdirectory must supply rules for building sources it contributes
LHPC_CPP/ParticleCodesAndData/%.o: ../LHPC_CPP/ParticleCodesAndData/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


