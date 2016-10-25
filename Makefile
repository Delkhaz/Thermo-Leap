OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ./x64/libLeap.so -Wl,-rpath,./x64
  else
    LEAP_LIBRARY := ./x86/libLeap.so -Wl,-rpath,./x86
  endif
else
  # OS X
  LEAP_LIBRARY := ./libLeap.dylib
endif

thermo_leap: thermo_leap.cpp
	$(CXX) -Wall -g -I../include thermo_leap.cpp -o thermo_leap $(LEAP_LIBRARY)
ifeq ($(OS), Darwin)
	install_name_tool -change @loader_path/libLeap.dylib ./libLeap.dylib Sample
endif

clean:
	rm -rf thermo_leap thermo_leap.dSYM:
