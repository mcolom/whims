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

CJoystick.o: CJoystick.cpp CJoystick.h
	$(CXX) $(CXXFLAGS) -c CJoystick.cpp -o CJoystick.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# ------- Main -------
$(EXEC):  CVideo.o CJoystick.o main.o
	$(CXX) CVideo.o CJoystick.o main.o $(LDFLAGS) -o $(EXEC)

lint: 
	$(MAKE) CFLAGS="$(CFLAGS) $(CSTRICT)" CXXFLAGS="$(CXXFLAGS) $(CXXSTRICT)"

clean: 
	rm -f *.o

distclean: clean
	rm -f $(EXEC)
