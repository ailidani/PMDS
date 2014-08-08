################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../paxos/detail/quorum/client_view.cpp \
../paxos/detail/quorum/server.cpp \
../paxos/detail/quorum/server_view.cpp \
../paxos/detail/quorum/view.cpp 

OBJS += \
./paxos/detail/quorum/client_view.o \
./paxos/detail/quorum/server.o \
./paxos/detail/quorum/server_view.o \
./paxos/detail/quorum/view.o 

CPP_DEPS += \
./paxos/detail/quorum/client_view.d \
./paxos/detail/quorum/server.d \
./paxos/detail/quorum/server_view.d \
./paxos/detail/quorum/view.d 


# Each subdirectory must supply rules for building sources it contributes
paxos/detail/quorum/%.o: ../paxos/detail/quorum/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


