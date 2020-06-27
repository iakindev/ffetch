CC = g++
  CFLAGS  = -g -Wall
  TARGET = fetch

  $(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
	
  clean:
	$(RM) $(TARGET)