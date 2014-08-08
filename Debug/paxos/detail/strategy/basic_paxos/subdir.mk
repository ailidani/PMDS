################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../paxos/detail/strategy/basic_paxos/factory.cpp 

OBJS += \
./paxos/detail/strategy/basic_paxos/factory.o 

CPP_DEPS += \
./paxos/detail/strategy/basic_paxos/factory.d 


# Each subdirectory must supply rules for building sources it contributes
paxos/detail/strategy/basic_paxos/%.o: ../paxos/detail/strategy/basic_paxos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


