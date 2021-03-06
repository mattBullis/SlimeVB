UNAME = $(shell uname)


CC 		= g++
CFLAGS 	= -Wall
LDFLAGS =

CXXDIR = ../bin/cxxtest-4.3
CXXTEST = $(CXXDIR)/bin/cxxtestgen
CXXFLAGS = --error-printer --have-eh

TESTS = collisionTest.h robotTest.h OrientTowardsTest.h rotateTest.h translateTest.h environmentTest.h

##
# List of cpp files to be compiled
# Note, if you add any cpp files to your project, you must also add them here
##
CPPFILES += main.cpp 
CPPFILES += Object.cpp
CPPFILES += drawing.cpp
CPPFILES += environment.cpp
CPPFILES += RenderEnv.cpp
CPPFILES += Slime.cpp
CPPFILES += Ball.cpp


##
# Lists all the cpp files in /src
# Note, this means you can make from /src, /lib, or /bin
##
SOURCES=$(addprefix ../src/,  $(CPPFILES))

OBJECTS = $(addprefix ../bin/,  $(CPPFILES:.cpp=.o)) 

GLUI = glui

##
# Linking the GLUI libraries
##
LINK_LIBS += -L../lib/$(GLUI)/lib/ -lglui
INCLUDE = -I../lib/$(GLUI)/include -I../src

##
# Linking GLUT and OpenGl for Mac
##
ifeq ($(UNAME), Darwin)
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = ../bin/gorobot
	TESTRUNNER = ../bin/testrobot
##
# Linking GLUT and OpenGl for Linux
##
else
	ifeq ($(UNAME), Linux)
		LINK_LIBS += -lglut -lGL -lGLU -lm -lpthread
		EXECUTABLE = ../bin/gorobot
		TESTRUNNER = ../bin/testrobot
##
# Linking GLUT and OpenGl for Windows
# Note, you must have freeGlut installed; see the Resource page for details
##
	else 
		GLUTINCLUDEPATH = C:\Dev-Cpp\mingw32\freeglut\include\
		GLUTLIBPATH = C:\Dev-Cpp\mingw32\freeglut\lib\
		LINK_LIBS += -L$(GLUTLIBPATH) -lfreeglut -lopengl32 -Wl,--subsystem,windows
		INCLUDE += -I$(GLUTPATH)
		EXECUTABLE = gorobot.exe

	endif
endif

##
# Sets up the /bin folder, checks for all cpp files, and compiles the executable
##
all: setup $(SOURCES) gorobot testrobot docs

setup:
	mkdir -p ../bin

gorobot: $(GLUI) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $(EXECUTABLE)

test.cpp: $(TESTS)
	$(CXXTEST) $(CXXFLAGS) -o test.cpp $(TESTS)

testrobot: ##$(GLUI) test.cpp ../bin/Robot.o ../bin/Object.o
	##$(CC) -I$(CXXDIR) $(LINK_LIBS) -o $(TESTRUNNER) ../bin/Robot.o ../bin/Object.o ../src/test.cpp ../bin/environment.o ../bin/Light.o ../bin/Wheel.o

tests: testrobot
	$(TESTRUNNER)
docs: 
	 doxygen documentation



##
# This creates the object files in the /bin folder
##
../bin/%.o: ../src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	\rm -rf test.cpp $(OBJECTS) $(EXECUTABLE) $(TESTRUNNER)
	 $(MAKE)  -C ../lib/$(GLUI) clean

$(GLUI):
	$(MAKE) -C ../lib/$(GLUI) all
