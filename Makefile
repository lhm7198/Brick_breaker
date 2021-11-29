TARGET	=	3-codiots
CC	=	g++
LINKER	=	g++

# directory
SRCDIR		=	src
OBJDIR		=	obj
BINDIR		=	bin
LIBS		=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm        = rm -f

$(BINDIR)/$(TARGET) : $(OBJECTS)
	@$(LINKER) $(OBJECTS) -o $@ $(LIBS)
	@echo "Linking complete!"

$(OBJECTS) : $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
