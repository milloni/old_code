MNTCW_TARGET = mntcw
MNTCW_OBJECTS = mntcw.o util.o
MNTCW_SOURCES = mntcw.cc util.cc
CXXFLAGS= -Wall -Wextra -lgmp -pthread

.PHONY: default
default: all

.PHONY: all
all: $(MNTCW_TARGET)

$(MNTCW_TARGET): $(MNTCW_OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(MNTCW_OBJECTS): %.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) -rf $(MNTCW_OBJECTS) $(MNTCW_TARGET)

