COPT      = -O3
CFLAGS    = $(COPT)
CSTRICT   = -Wall -Wextra -ansi
CXXOPT    = -O3
CXXFLAGS  = $(CXXOPT)
CXXSTRICT = -Wall -Wextra -ansi
LDFLAGS   = -lGL -lGLU -lglut
EXEC      = whims

default: $(EXEC)
all: $(EXEC)

CVideo.o: CVideo.cpp CVideo.h
	$(CXX) $(CXXFLAGS) -c CVideo.cpp -o CVideo.o

# ------- Main -------
$(EXEC):  CVideo.o main.o
	$(CXX) CVideo.o main.o $(LDFLAGS) -o $(EXEC)

lint: 
	$(MAKE) CFLAGS="$(CFLAGS) $(CSTRICT)" CXXFLAGS="$(CXXFLAGS) $(CXXSTRICT)"

clean: 
	rm -f *.o

distclean: clean
	rm -f $(EXEC)

