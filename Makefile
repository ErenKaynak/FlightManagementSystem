CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = src
INCDIR = include
BUILDDIR = build

_SRCS = $(wildcard $(SRCDIR)/*.cpp)
_OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(_SRCS))

TARGET = $(BUILDDIR)/fms

all: $(TARGET)

$(TARGET): $(_OBJS)
	$(CXX) $(CXXFLAGS) $(_OBJS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
