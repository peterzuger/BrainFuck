VERBOSE ?=
DEBUG   ?=

ifeq ($(VERBOSE),1)
	Q =
else
	Q = @
endif

CXXSRC  = $(wildcard *.cpp)

EXECUTABLES = $(CXXSRC:.cpp=)
TESTS = $(CXXSRC:.cpp=.test)

CC      = g
GCC     = $(Q)$(CC)cc
GXX     = $(Q)$(CC)++
ECHO    = @echo -e

ifeq ($(VERBOSE),1)
	RM   = rm -v
else
	RM   = @rm
endif

ifeq ($(DEBUG),1)
	DBGFLAGS = -g
else
	DBGFLAGS =
endif

OPTFLAGS= -O3
IFLAGS  =
WFLAGS  = -Wall -Wextra -Wpedantic -Wnull-dereference -Wshadow
WFLAGS += -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum
WFLAGS += -Wundef -Wconversion -Winline -Waddress
COMFLAGS= $(WFLAGS)

GCCFLAGS= $(OPTFLAGS) $(IFLAGS) $(COMFLAGS) $(DFLAGS)
CXXFLAGS= $(GCCFLAGS) -std=c++17

all: $(EXECUTABLES)

%: %.cpp
	$(ECHO) "G++\t$@"
	$(GXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) -f $(EXECUTABLES)
