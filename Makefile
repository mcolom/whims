COPT      = -O3
CFLAGS    = $(COPT)
CSTRICT   = -Wall -Wextra -ansi
CXXOPT    = -O3
CXXFLAGS  = $(CXXOPT)
CXXSTRICT = -Wall -Wextra -ansi
LDFLAGS   = -lGL -lGLU -lglut -lpthread
EXEC      = whims

default: $(EXEC)
all: $(EXEC)

CVideo.o: CVideo.cpp CVideo.h
	$(CXX) $(CXXFLAGS) -c CVideo.cpp -o CVideo.o

joystick.o: joystick.cpp joystick.h
	$(CXX) $(CXXFLAGS) -c joystick.cpp -o joystick.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# ------- Main -------
$(EXEC):  CVideo.o joystick.o main.o
	$(CXX) CVideo.o joystick.o main.o $(LDFLAGS) -o $(EXEC)

lint: 
	$(MAKE) CFLAGS="$(CFLAGS) $(CSTRICT)" CXXFLAGS="$(CXXFLAGS) $(CXXSTRICT)"

clean: 
	rm -f *.o

distclean: clean
	rm -f $(EXEC)
