################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../paxos/client.cpp \
../paxos/configuration.cpp \
../paxos/server.cpp 

OBJS += \
./paxos/client.o \
./paxos/configuration.o \
./paxos/server.o 

CPP_DEPS += \
./paxos/client.d \
./paxos/configuration.d \
./paxos/server.d 


# Each subdirectory must supply rules for building sources it contributes
paxos/%.o: ../paxos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


