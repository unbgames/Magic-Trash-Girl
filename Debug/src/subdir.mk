################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Fader.cpp \
../src/Musics.cpp \
../src/Sound.cpp \
../src/animatedsprite.cpp \
../src/backgroundblock.cpp \
../src/backgroundsectorlibraryhandler.cpp \
../src/blockborder.cpp \
../src/boss.cpp \
../src/camera.cpp \
../src/enemy.cpp \
../src/game.cpp \
../src/gamepadinput.cpp \
../src/graphics.cpp \
../src/hudelement.cpp \
../src/hudplayerhp.cpp \
../src/keyboardinput.cpp \
../src/main.cpp \
../src/mainmenu.cpp \
../src/menu.cpp \
../src/menubackground.cpp \
../src/menubutton.cpp \
../src/pausemenu.cpp \
../src/player.cpp \
../src/playerprojectile.cpp \
../src/portal.cpp \
../src/quadtree.cpp \
../src/rat.cpp \
../src/sectorbackground.cpp \
../src/sprite.cpp \
../src/textcaches.cpp \
../src/vacuumcleaner.cpp \
../src/vacuumcone.cpp 

OBJS += \
./src/Fader.o \
./src/Musics.o \
./src/Sound.o \
./src/animatedsprite.o \
./src/backgroundblock.o \
./src/backgroundsectorlibraryhandler.o \
./src/blockborder.o \
./src/boss.o \
./src/camera.o \
./src/enemy.o \
./src/game.o \
./src/gamepadinput.o \
./src/graphics.o \
./src/hudelement.o \
./src/hudplayerhp.o \
./src/keyboardinput.o \
./src/main.o \
./src/mainmenu.o \
./src/menu.o \
./src/menubackground.o \
./src/menubutton.o \
./src/pausemenu.o \
./src/player.o \
./src/playerprojectile.o \
./src/portal.o \
./src/quadtree.o \
./src/rat.o \
./src/sectorbackground.o \
./src/sprite.o \
./src/textcaches.o \
./src/vacuumcleaner.o \
./src/vacuumcone.o 

CPP_DEPS += \
./src/Fader.d \
./src/Musics.d \
./src/Sound.d \
./src/animatedsprite.d \
./src/backgroundblock.d \
./src/backgroundsectorlibraryhandler.d \
./src/blockborder.d \
./src/boss.d \
./src/camera.d \
./src/enemy.d \
./src/game.d \
./src/gamepadinput.d \
./src/graphics.d \
./src/hudelement.d \
./src/hudplayerhp.d \
./src/keyboardinput.d \
./src/main.d \
./src/mainmenu.d \
./src/menu.d \
./src/menubackground.d \
./src/menubutton.d \
./src/pausemenu.d \
./src/player.d \
./src/playerprojectile.d \
./src/portal.d \
./src/quadtree.d \
./src/rat.d \
./src/sectorbackground.d \
./src/sprite.d \
./src/textcaches.d \
./src/vacuumcleaner.d \
./src/vacuumcone.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -ISDL2 -I"/media/gabriel/RAID/Trabalhos/IDJ/idj-game-final/headers" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


