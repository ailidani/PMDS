################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../paxos/detail/command.cpp \
../paxos/detail/command_dispatcher.cpp \
../paxos/detail/error.cpp \
../paxos/detail/io_thread.cpp \
../paxos/detail/parser.cpp \
../paxos/detail/paxos_context.cpp \
../paxos/detail/tcp_connection.cpp 

OBJS += \
./paxos/detail/command.o \
./paxos/detail/command_dispatcher.o \
./paxos/detail/error.o \
./paxos/detail/io_thread.o \
./paxos/detail/parser.o \
./paxos/detail/paxos_context.o \
./paxos/detail/tcp_connection.o 

CPP_DEPS += \
./paxos/detail/command.d \
./paxos/detail/command_dispatcher.d \
./paxos/detail/error.d \
./paxos/detail/io_thread.d \
./paxos/detail/parser.d \
./paxos/detail/paxos_context.d \
./paxos/detail/tcp_connection.d 


# Each subdirectory must supply rules for building sources it contributes
paxos/detail/%.o: ../paxos/detail/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -D_FILE_OFFSET_BITS=64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


