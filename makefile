CC = g++
  CFLAGS  = -g -Wall
  TARGET = ffetch

  $(TARGET): $(TARGET).cpp get_functions.hpp utils.hpp 
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
	
  clean:
	$(RM) $(TARGET)