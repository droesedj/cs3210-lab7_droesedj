################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../circle.cpp \
../dynamicdraw.cpp \
../gcontext.cpp \
../image.cpp \
../line.cpp \
../main.cpp \
../matrix.cpp \
../point.cpp \
../poly.cpp \
../shape.cpp \
../triangle.cpp \
../viewcontext.cpp \
../x11context.cpp 

OBJS += \
./circle.o \
./dynamicdraw.o \
./gcontext.o \
./image.o \
./line.o \
./main.o \
./matrix.o \
./point.o \
./poly.o \
./shape.o \
./triangle.o \
./viewcontext.o \
./x11context.o 

CPP_DEPS += \
./circle.d \
./dynamicdraw.d \
./gcontext.d \
./image.d \
./line.d \
./main.d \
./matrix.d \
./point.d \
./poly.d \
./shape.d \
./triangle.d \
./viewcontext.d \
./x11context.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


