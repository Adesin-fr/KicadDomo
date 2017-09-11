Import('env')
env.Replace( UPLOADHEXCMD='"$UPLOADER" -C ~/.platformio/packages/tool-avrdude/avrdude.conf -c usbasp -p m328p -Uhfuse:w:0xDA:m -Uefuse:w:0xE2:m -Ulfuse:w:0xFF:m -U flash:w:$SOURCES:i')
