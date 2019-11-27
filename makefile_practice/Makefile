CXX := g++

OBJ_DIR := obj/

SRCS := main.cpp hello.cpp

OBJS := $(addprefix $(OBJ_DIR), \
	$(patsubst %.cpp,%.o, $(SRCS)))

#$(info $(OBJS))

TARGET := xx

include local.mk

.PHONY : all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJ_DIR)%.o:%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $<


clean:
	rm $(OBJ_DIR) $(TARGET) -r -f
