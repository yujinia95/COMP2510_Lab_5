CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = tic_tac_toe.o main.o
TARGET = tic_tac_toe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~