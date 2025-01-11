# configurations
CC = gcc
CFLAGS = -Wall
LIBS = -lm # math
OBJDIR = obj

# output file
TARGET = main
OBJS = $(OBJDIR)/lex.o $(OBJDIR)/extern.o $(OBJDIR)/main.o

# compile final executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

# compile main.c
$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) -c main.c $(CFLAGS) -o $(OBJDIR)/main.o

# compile lex.c
$(OBJDIR)/lex.o: lex.c lex.h | $(OBJDIR)
	$(CC) -c lex.c $(CFLAGS) -o $(OBJDIR)/lex.o

# compile extern.c
$(OBJDIR)/extern.o: extern.c extern.h | $(OBJDIR)
	$(CC) -c extern.c $(CFLAGS) -o $(OBJDIR)/extern.o

# create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

