TARGET = gps
OBJS = main.o gps.o 
CFLAGS = -Wall -g
LIBS = -lm  
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
clean:
	rm -f $(TARGET) $(OBJS) core*

