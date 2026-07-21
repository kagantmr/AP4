CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Isrc -Ilib/raylib/src
LDFLAGS := -Llib/raylib/src -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
TARGET := ap4
SRC := $(shell find src -name '*.cpp')

.PHONY: all raylib clean

all: $(TARGET)

raylib:
	@if [ ! -f lib/raylib/src/libraylib.a ]; then \
		echo "Building local raylib..."; \
		$(MAKE) -C lib/raylib/src PLATFORM=PLATFORM_DESKTOP; \
	fi

$(TARGET): raylib $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
