add_executable( openshotclock
  max7219.cpp
  openshotclock.cpp
  clock.cpp
)

target_link_libraries(openshotclock
pico_stdlib
hardware_rtc
)

pico_add_extra_outputs(openshotclock)