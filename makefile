CPP = g++
CPPFLAGS = -g

SRCS = main.cpp Scene.cpp Task.cpp Vector.cpp Ray.cpp util.cpp SceneObject.cpp Material.cpp BRDF.cpp
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