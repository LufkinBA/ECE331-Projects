TARGET = mmult
OBJS = mmult.o main.o
CFLAGS = -Wall -g
LIBS = -lm -lrt
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
clean: 
	rm -f $(TARGET) $(OBJS) core*
