################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FaceFinder.cpp \
../Runner.cpp \
../Runner2.cpp \
../TemplateMatcher.cpp \
../TestUtils.cpp 

OBJS += \
./FaceFinder.o \
./Runner.o \
./Runner2.o \
./TemplateMatcher.o \
./TestUtils.o 

CPP_DEPS += \
./FaceFinder.d \
./Runner.d \
./Runner2.d \
./TemplateMatcher.d \
./TestUtils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv -I/usr/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


