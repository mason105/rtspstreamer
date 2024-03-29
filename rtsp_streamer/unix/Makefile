################################################################################

ROOT = ../..
COMMON = $(ROOT)/common
RTSP = $(ROOT)/rtsp_streamer

BOOST_VER=1_37

UNAME=$(shell uname)
ifeq ($(UNAME), Darwin)
    BOOST_FOOTER=xgcc40-mt-$(BOOST_VER)
else
    BOOST_FOOTER=-mt-$(BOOST_VER)
endif
	
BOOST_COMPLIRE=xgcc40
BOOST_INC = /usr/include/boost-$(BOOST_VER)
BOOST_LIB = /usr/lib

ifeq "$(RELEASE)" "yes"
OPTIMIZE_FLAGS = -O2
else
OPTIMIZE_FLAGS = -O0 -ggdb
endif

primary: all

include $(RTSP)/VERSION

DEFINES += -DVERSION=$(VERSION)
DEFINES += -DPACKAGE=$(PACKAGE)

CPPFLAGS = -pthread $(OPTIMIZE_FLAGS) $(CXXFLAGS) $(DEFINES) \
	-Wall -Werror -Wextra -pedantic -pedantic-errors \
	-fno-strict-aliasing -Wno-long-long -Wno-unused-parameter \

INCLUDES = \
        -I$(ROOT) \
		-I$(RTSP) \
		-I$(BOOST_INC)

################################################################################

CC = gcc
CPP = g++
LD = gcc

LDLIBS = -lstdc++ 
LDFLAGS = -L$(BOOST_LIB)

VPATH = ./
VPATH += ../
VPATH += ../../

################################################################################

PROG = $(PACKAGE)-$(VERSION).build

BUILDDIRS = \
    build build/rtsp_streamer build/common

MAIN_SRC = \
    $(RTSP)/main.cpp \

COMMON_SRC = \
	$(COMMON)/logger.cpp \
	$(COMMON)/service.cpp

PROG_SRC += $(MAIN_SRC)
PROG_SRC += $(COMMON_SRC)

PROG_DEPS = $(PROG_SRC:%.cpp=%.d)
DEPS += $(PROG_DEPS)
PROG_OBJS = $(PROG_SRC:%.cpp=%.o)
OBJS += $(PROG_OBJS)

PROG_LDLIBS += -lboost_date_time-$(BOOST_FOOTER)
PROG_LDLIBS += -lboost_filesystem-$(BOOST_FOOTER)
PROG_LDLIBS += -lboost_program_options-$(BOOST_FOOTER)
PROG_LDLIBS += -lboost_thread-$(BOOST_FOOTER)
PROG_LDLIBS += -lboost_regex-$(BOOST_FOOTER)

$(PROG): LDLIBS += $(PROG_LDLIBS)
$(PROG): $(PROG_OBJS)

################################################################################

UNITTEST = $(PACKAGE)-$(VERSION).unittest

UNITTEST_MAIN_SRC = \

UNITTEST_SRC = $(UNITTEST_MAIN_SRC)
UNITTEST_SRC += $(COMMON_SRC)

UNITTEST_DEPS = $(UNITTEST_SRC:%.cpp=%.d)
DEPS += $(UNITTEST_DEPS)
UNITTEST_OBJS = $(UNITTEST_SRC:%.cpp=%.o)
OBJS += $(UNITTEST_OBJS)

UNITTEST_LDLIBS = -lboost_unit_test_framework

$(UNITTEST): LDLIBS += $(PROG_LDLIBS) $(UNITTEST_LDLIBS)
$(UNITTEST): $(UNITTEST_OBJS)

################################################################################

all: $(PROG)

$(PROG):
	@echo "--- linking:" $@
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
	cp $@ $(RTSP)/$(PACKAGE)

check: $(UNITTEST)
	@echo "--- linking:" $@
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS) 

.PHONY:	clean

clean:
	@echo "--- clean rtsp_streamer ---"
	rm -f $(OBJS) $(DEPS) $(PROG) $(UNITTEST)
	rm -rf $(BUILDDIRS)
	rm -f $(RTSP)/$(PACKAGE)

################################################################################

%.d: %.cpp
	@mkdir -p $(BUILDDIRS)
	@echo "--- header deps:" $<
	@set -e; $(CPP) -MM $(CPPFLAGS) $(DEFINES) $(INCLUDES) $<\
		| sed 's?$(notdir $*)\.o[ :]*?$*.o $@ : ?g' > $@;\
		[ -s $@ ] || rm -f $@

.cpp.o:
	@echo "--- compile:" $<
	@$(CPP) -c $(CPPFLAGS) $(DEFINES) $(INCLUDES) $< -o $@

################################################################################

ifeq (,$(filter %clean show%,$(MAKECMDGOALS)))
-include $(DEPS) 
endif

################################################################################
