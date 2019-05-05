CPP = g++
CPPFLAGS = -g

SRCS = main.cpp Task.cpp
OBJS = $(subst .cpp,.o,$(SRCS))

main: $(OBJS)
	$(CPP) -o main $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CPP) $(CPPFLAGS) -MM $^>>./.depend

clean:
	rm -f $(OBJS)

include .depend