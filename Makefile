# Declaration of variables
CC = g++
CC_FLAGS = -w -Iinclude -std=c++17 -m64
CC_LIBS = -Llib -lglew32s -lglfw3 -lopengl32
CC_LINKER = 
 
# File names
EXEC = build/tumbleweed.exe
SOURCES = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

ifdef ComSpec
    RM = cmd /c del
		EXEC := $(subst /,\,$(EXEC))
		OBJECTS := $(subst /,\,$(OBJECTS))
		CC_LIBS += -lGdi32
		CC_LINKER += -mwindows
else
    RM = rm -f
endif 
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(CC_FLAGS) $(OBJECTS) $(CC_LIBS) $(CC_LINKER) -o $(EXEC)
	$(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	$(RM) $(EXEC) $(OBJECTS)