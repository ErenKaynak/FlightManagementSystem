CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCDIR = src
INCDIR = include
BUILDDIR = build

# Find all .cpp files in src and its subdirectories
_SRCS = $(shell find $(SRCDIR) -name "*.cpp")
_OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(_SRCS))

TARGET = $(BUILDDIR)/fms

all: $(TARGET)

$(TARGET): $(_OBJS)
	$(CXX) $(CXXFLAGS) $(_OBJS) -o $@

# This rule handles .cpp files in subdirectories
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
