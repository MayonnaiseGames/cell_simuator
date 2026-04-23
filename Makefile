#--------------------
#Use of Makefile
#--------------------

#make o for compiling libraries
#make o_clean for cleaning just libraries
#make all does everything
#make run does everything and runs
#make clean just cleans the main

CXX      := g++
CXXFLAGS := -std=c++23 -Iimgui -Iglad -IGLFW
LDFLAGS  := -lglfw -lGL -lm -lpthread -ldl -lrt -lX11

# App source (compiled normally, no caching)
SRC := src/*.cpp

# Library sources (compiled once into .o files)
LIB_SRC := \
glad/glad.c \
imgui/imgui.cpp \
imgui/imgui_draw.cpp \
imgui/imgui_tables.cpp \
imgui/imgui_widgets.cpp \
imgui/imgui_demo.cpp \
imgui/backends/imgui_impl_glfw.cpp \
imgui/backends/imgui_impl_opengl3.cpp

LIB_OBJ := $(LIB_SRC:.cpp=.o)
LIB_OBJ := $(LIB_OBJ:.c=.o)

OUT := CAPSE

# Default build
all: $(OUT)

# Link everything
$(OUT): $(LIB_OBJ)
	$(CXX) $(CXXFLAGS) $(SRC) $(LIB_OBJ) -o $(OUT) $(LDFLAGS)

# Compile libraries only
o: $(LIB_OBJ)

# Compile rules for libs
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run
run: all
	./$(OUT)
	rm -f $(OUT)

# Clean just executable
clean:
	rm -f $(OUT)

# Clean only library objects
clean_o:
	rm -f $(LIB_OBJ)