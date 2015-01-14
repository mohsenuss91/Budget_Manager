# budget_manager MAKEFILE

CXXFLAGS =      -O2 -g -Wall -fmessage-length=0
OBJS =          main.o classes.o
TARGET =        budget_manager

$(TARGET):      $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp classes.h
	g++ -c main.cpp

classes.o: classes.cpp classes.h
	g++ -c classes.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run:    $(TARGET)
	./$(TARGET)

# END OF MAKE FILE