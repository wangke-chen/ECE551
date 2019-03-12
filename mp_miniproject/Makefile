SOURCES=myShell.cpp myShell_class.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

compress: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(OBJS)
%.o: %.cpp myShell_class.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm compress *~ *.o