#CXX := g++

#VPATH := src:inc
# vpath %.hpp inc
# vpath %.cpp src

OBJ_DIR := obj/
DEP_DIR := dep/
SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix $(OBJ_DIR), \
	$(patsubst %.cpp,%.o, $(SRCS)))
DEPS := $(subst $(OBJ_DIR),$(DEP_DIR),$(OBJS:%.o=%.d))

#$(info $(OBJS))

INCLUDES := -Iinc/

TARGET := target

include local.mk

.PHONY : all
all: $(TARGET) $(DEPS)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ_DIR)%.o:%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $(INCLUDES) -o $@ $<

clean:
	rm $(OBJ_DIR) $(DEP_DIR) $(TARGET) -r -f

$(DEP_DIR)%.d:%.cpp
	@set -e; rm -f $@; mkdir -p $(dir $@); $(CXX) -MM $< $(INCLUDES) > $@.$$$$; \
	sed 's,\(.*\)\.o,$(subst $(DEP_DIR),$(OBJ_DIR),$(dir $@))\1.o $@,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)
