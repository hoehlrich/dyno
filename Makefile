APP = dyno

DEPENDENCIES := -lftd2xx -lpthread -lrt

UNAME := $(shell uname)

# Embed in the executable a run-time path to libftd2xx
LINKER_OPTIONS := -Wl,-rpath /usr/local/lib

CFLAGS = -Wall -Wextra $(DEPENDENCIES) $(LINKER_OPTIONS) -L/usr/local/lib

all: $(APP)

$(APP): main.c	
	$(CC) main.c -o $(APP) $(CFLAGS)
	
clean:
	-rm -f *.o ; rm $(APP)

