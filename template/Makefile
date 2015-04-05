###############################################################################
#                              COMMON SETTINGS                                #
###############################################################################
EXEC_NAME = solution.x
CUSTOM_LD_FLAGS = 
CUSTOM_CC_FLAGS = 

OBJS = \
main.o

###############################################################################
#                            INCLUDE AND LIB DIRS                             #
###############################################################################
BOOST_DIR = /usr/local/include/boost
JAM_DIR = ${JAM_ROOT}

###############################################################################
#                                    FLAGS                                    #
###############################################################################

SHELL = bash
CXX = clang++
CC = clang
OPT_LEVEL = -O3
ifdef DEBUG
  OPT_LEVEL = -g
endif
CCFLAGS = -c ${OPT_LEVEL} -I${JAM_DIR}/include -I${BOOST_DIR} -I. \
					${CUSTOM_CC_FLAGS}
ifdef VERBOSE
  CCFLAGS += -DVERBOSE
endif
CXXFLAGS = $(CCFLAGS) -std=c++1y
LDFLAGS = -L/usr/local/lib

###############################################################################
#                                    RULES                                    #
###############################################################################

default: $(EXEC_NAME)

$(EXEC_NAME): $(OBJS:.o=.d) $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(CUSTOM_LD_FLAGS) -o $@

-include $(OBJS:.o=.d)

%.d: %.cpp
	$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< | sed "s|$*.o|& $@|g" > $@'

%.d: %.c
	$(SHELL) -ec '$(CC) -M $(CCFLAGS) $< | sed "s|$*.o|& $@|g" > $@'

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@

clean:
	$(RM) -rf $(OBJS) $(OBJS:.o=.d) $(EXEC_NAME)

