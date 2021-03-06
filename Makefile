CC = gcc
#modify the CFLAGS variable as needed.  specifically you will probably need to modify the include directory arguments
CFLAGS = -O2 -Wall -Wextra -Wno-unused-parameter -pedantic -pipe -g
LIBS = -lncurses -lm
OBJDIR = .build
OBJECTS = main.o level.o monster.o util.o arraylist.o
OBJECTS :=  $(addprefix ${OBJDIR}/,${OBJECTS})

snowballrl: $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECTS) -o snowballrl

${OBJDIR}/%.o : %.c
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi #create directory if it doesn't exist
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) snowballrl
