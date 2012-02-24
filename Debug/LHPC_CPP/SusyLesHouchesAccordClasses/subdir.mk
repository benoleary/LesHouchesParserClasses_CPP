################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LHPC_CPP/SusyLesHouchesAccordClasses/SlhaBlock.cpp \
../LHPC_CPP/SusyLesHouchesAccordClasses/SlhaOne.cpp \
../LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwo.cpp \
../LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.cpp 

OBJS += \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaBlock.o \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaOne.o \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwo.o \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.o 

CPP_DEPS += \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaBlock.d \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaOne.d \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwo.d \
./LHPC_CPP/SusyLesHouchesAccordClasses/SlhaTwoWithSpheno.d 


# Each subdirectory must supply rules for building sources it contributes
LHPC_CPP/SusyLesHouchesAccordClasses/%.o: ../LHPC_CPP/SusyLesHouchesAccordClasses/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


