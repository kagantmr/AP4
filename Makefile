CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Isrc -Ilib/raylib/src
LDFLAGS := -Llib/raylib/src -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
TARGET := ap4
SRC := $(shell find src -name '*.c')

.PHONY: all raylib clean

all: $(TARGET)

raylib:
	@if [ ! -f lib/raylib/src/libraylib.a ]; then \
		echo "Building local raylib..."; \
		$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP; \
	fi

$(TARGET): raylib $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
