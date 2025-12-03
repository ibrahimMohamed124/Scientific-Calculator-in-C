# ------------------------------------------
#   Scientific Calculator Build System
#   Debug + Release + Auto Run
# ------------------------------------------

CC = gcc
DEBUG_CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
RELEASE_CFLAGS = -O2 -s `pkg-config --cflags gtk+-3.0`

LIBS = `pkg-config --libs gtk+-3.0` -lm

TARGET = scientific_calculator
SRC = scientific_calculator.c

all: build run

# -------------------
# DEBUG BUILD (Default)
# -------------------
build: $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(DEBUG_CFLAGS) $(LIBS)

# -------------------
# RELEASE BUILD
# -------------------
release:
	$(CC) -o $(TARGET)_release $(SRC) $(RELEASE_CFLAGS) $(LIBS)
	@echo "----------------------------------------"
	@echo " Release Build created:"
	@echo " --> $(TARGET)_release.exe"
	@echo "----------------------------------------"

# -------------------
# RUN after build
# -------------------
run:
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET)_release
