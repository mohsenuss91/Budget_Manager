# budget_manager MAKEFILE

CXXFLAGS =      -O2 -g -Wall -fmessage-length=0 -std=c++11 -ggdb
OBJS =          main.o classes.o
TARGET =        budget_manager

$(TARGET):      $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAGS)

main.o: main.cpp classes.h
	g++ -c main.cpp  $(CXXFLAGS)

classes.o: classes.cpp classes.h
	g++ -c classes.cpp  $(CXXFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

run:    $(TARGET)
	./$(TARGET)

# END OF MAKE FILE
