
PROGRAM= myapp
CC= gcc
#cppflags are used for preprocessor (convention?)
CPPFLAGS= -MMD -Iinclude
CFLAGS= -Wall -Wextra -std=c99
LDFLAGS= -Llib
LDLIBS= -lglfw3 -lcglm -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

# -I flag tells where to search for includes to the compiler (preprocessor flag)
# -L flag tells to the linker where to search for libs
# and -L flag shoudl go before the -l step

BUILD ?= debug

SRC= src/main.c \
		 src/glad.c \
		 src/utils/file_read.c \
		 src/object.c \
		 src/shader.c
		 
OBJS= $(SRC:%.c=%.o)
DEPS= $(OBJS:%.o=%.d)

ifeq ($(BUILD),release)
    CFLAGS += -O2 -DNDEBUG
else ifeq ($(BUILD),debug)
    CFLAGS += -g -O0 -DDEBUG
else
    $(error Invalid BUILD value. Use 'debug' or 'release')
endif

all: $(PROGRAM)

$(PROGRAM): $(OBJS)                
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(PROGRAM) 

-include $(DEPS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean: # make clean after running and debugging for example
	rm -f $(OBJS) $(DEPS) $(PROGRAM)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) BUILD=release

config:
	@echo "Program: $(PROGRAM)"
	@echo "Current build: $(BUILD)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LDLIBS: $(LDLIBS)"

.PHONY: all clean debug release config
