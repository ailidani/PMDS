################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../paxos/durable/heap.cpp \
../paxos/durable/sqlite.cpp \
../paxos/durable/storage.cpp 

OBJS += \
./paxos/durable/heap.o \
./paxos/durable/sqlite.o \
./paxos/durable/storage.o 

CPP_DEPS += \
./paxos/durable/heap.d \
./paxos/durable/sqlite.d \
./paxos/durable/storage.d 


# Each subdirectory must supply rules for building sources it contributes
paxos/durable/%.o: ../paxos/durable/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


