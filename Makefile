PKG_CONFIG_PATH := /usr/lib/x86_64-linux-gnu/pkgconfig
CFLAGS := $(shell pkg-config --cflags glfw3 glew)
LDFLAGS := $(shell pkg-config --libs glfw3 glew)

fraktals: main.o functions.o
	g++ $(CFLAGS) -o fraktals main.o functions.o $(LDFLAGS)

functions.o: functions.cpp
	g++ $(CFLAGS) -c functions.cpp

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

clean:
	rm -f fraktals main.o functions.o