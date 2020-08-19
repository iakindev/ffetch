CC = g++
  CFLAGS  = -g -Wall
  TARGET = ffetch

  $(TARGET): $(TARGET).cpp get_functions.hpp utils.hpp ascii_art.hpp 
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
	
  clean:
	$(RM) $(TARGET)

  install: $(TARGET)
	install $(TARGET) /usr/bin/
