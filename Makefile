CC = g++
CFLAGS_DEV = -std=c++17 -Wall -Werror -g
CFLAGS_RELEASE = -std=c++17 -O3 -pedantic -pedantic-errors \
								 -Wall -Werror -Wextra -Wpedantic -Wshadow \
								 -Wvla -Wswitch-enum -Wpointer-arith \
								 -Woverloaded-virtual -Wnull-dereference \
								 -Wmissing-include-dirs -Wlogical-op  \
								 -Wformat=2 -Wduplicated-cond \
								 -Wduplicated-branches -Wcast-qual

# Target executable
TARGET_DEV = main-dev
TARGET_RELEASE = main 

# Source files
SRCS = main.cpp  distances/distances.cpp KNN/KNN.cpp CSV/CSV.cpp

# Object files
OBJS_DEV = $(SRCS:.cpp=-dev.o)
OBJS_RELEASE = $(SRCS:.cpp=-release.o)

# Default target
all: dev release 

# Rule to compile .cpp files into .o files
%-dev.o: %.cpp
	$(CC) $(CFLAGS_DEV) -c $< -o $@

%-release.o: %.cpp
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@


# Rule to link object files into executable
$(TARGET_DEV): $(OBJS_DEV)
	$(CC) $(OBJS_DEV) -o $(TARGET_DEV)

$(TARGET_RELEASE): $(OBJS_RELEASE)
	$(CC) $(OBJS_RELEASE) -o $(TARGET_RELEASE)

dev: $(TARGET_DEV)

release: $(TARGET_RELEASE)

# Rule to clean up intermediate object files and executable
clean:
	rm -f $(OBJS_DEV) $(TARGET_DEV) $(OBJS_RELEASE) $(TARGET_RELEASE)
