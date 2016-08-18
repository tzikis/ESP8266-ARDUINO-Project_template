#/bin/bash

randfolder=$RANDOM
tempdir="/tmp/$randfolder"
# sketch=$1
sketchname="sketch"

if [ -n "$1" ]; then fqbn=$1; else fqbn="esp8266com:esp8266:huzzah:CpuFrequency=80,UploadSpeed=115200,FlashSize=4M3M"; fi

./build/setup-file.sh $sketchname $tempdir &&\


export CODEBENDER_UPDATE_URL="\"http://testota.codebender.cc/api/update/e2b915e15d296c77699a52b7ac4bf3a184a2b168\""
export CODEBENDER_AUTO_VERSION="\"5\""

# /opt/arduino-1.6.7/arduino-builder -compile -logger=human -hardware /opt/arduino-1.6.7/hardware -tools /opt/arduino-1.6.7/tools-builder -tools /opt/arduino-1.6.7/hardware/tools/avr -built-in-libraries /opt/arduino-1.6.7/libraries -libraries /opt/arduino-1.6.7/libraries -fqbn=esp8266com:esp8266:huzzah:CpuFrequency=80,UploadSpeed=115200,FlashSize=4M3M -ide-version=10608  -build-path /projects/espressif-esp8266-arduino/output -warnings=all -prefs=build.warn_data_percentage=75  -verbose=true /projects/espressif-esp8266-arduino/esp8266-spiffs-httpUpdate.ino
mkdir -p /tmp/cbtest &&\
./arduino-builder-linux -compile -logger=machine -hardware ./hardware-linux -tools ./tools-builder-linux -tools ./hardware-linux/tools/avr -built-in-libraries ./libraries-linux -fqbn=$fqbn -ide-version=10608 -build-path "/tmp/cbtest" -warnings=none -prefs=build.warn_data_percentage=75 -verbose $tempdir/$sketchname.ino &&\
./bump-version.sh && \
version=$(cat /tmp/version) && \
echo -e "\n\nSuccessfuly built $sketchname. New version: $version"
