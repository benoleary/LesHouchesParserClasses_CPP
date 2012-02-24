################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../LHPC_CPP/BOLlib/Classes/AsciiXmlParser.cpp \
../LHPC_CPP/BOLlib/Classes/CommentedTextParser.cpp \
../LHPC_CPP/BOLlib/Classes/StringParser.cpp \
../LHPC_CPP/BOLlib/Classes/UsefulStuff.cpp 

OBJS += \
./LHPC_CPP/BOLlib/Classes/AsciiXmlParser.o \
./LHPC_CPP/BOLlib/Classes/CommentedTextParser.o \
./LHPC_CPP/BOLlib/Classes/StringParser.o \
./LHPC_CPP/BOLlib/Classes/UsefulStuff.o 

CPP_DEPS += \
./LHPC_CPP/BOLlib/Classes/AsciiXmlParser.d \
./LHPC_CPP/BOLlib/Classes/CommentedTextParser.d \
./LHPC_CPP/BOLlib/Classes/StringParser.d \
./LHPC_CPP/BOLlib/Classes/UsefulStuff.d 


# Each subdirectory must supply rules for building sources it contributes
LHPC_CPP/BOLlib/Classes/%.o: ../LHPC_CPP/BOLlib/Classes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


