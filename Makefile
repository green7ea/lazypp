CXXFLAGS += -MD -pipe -Wall -Wextra -std=c++17

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
PROG = lazy

.PHONY: all clean

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(PROG) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(DEPS) $(PROG)

-include $(DEPS)
