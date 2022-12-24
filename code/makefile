# Set the Compiler (C++)
COMP = g++

# Add debugger if you want (currently no debugger)
DB =
# Additional libraries required (currently no additional libraries)
ADDLIBS =

# Flag for objective & executable
OBJF = -c
EXEF = -o
# Name for executable
OUTF = oop

# Set all the Source files
SRCS = main.cpp entities.cpp
# Set all the Header files
HDRS = entities.h map.h
# Set documentation files
#DOCS = Readme.pdf
# All the corresponding object files will be all sources with .o
OBJS = ${SRCS:.cpp=.o}

# Set use of the option < make >
all: $(OBJS)
	$(COMP) $(DB) $(EXEF) $(OUTF) $(OBJS) $(ADDLIBS)

main.o: main.cpp
	$(COMP) $(DB) $(OBJF) $^
entities.o: entities.cpp
	$(COMP) $(DB) $(OBJF) $^


# Set use of the options < make rmObj > and < make rmExe >
rmObj:
	-rm -f $(OBJS)
rmExe:
	-rm -f $(OUTF)

# Set use of the option < make clean >
clean: rmObj rmExe

# Set use of the option < make rebuilt >
rebuilt: clean all

test: all clean

count:
	wc $(SRCS) $(HDRS) $(DOCS)