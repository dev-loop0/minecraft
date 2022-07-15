CC := gcc-11
CXX := g++-11

C_WARNINGS := -Wall -Wextra -Wpedantic -Wpointer-arith -Wcast-align \
								-Wwrite-strings -Wredundant-decls -Wnested-externs -Winline \
								-Wno-long-long -Wuninitialized -Wno-unused-variable -Winit-self \
								-Wimplicit -Wunknown-pragmas -Wstrict-overflow -Warray-bounds \
								-Wchar-subscripts -Wmissing-include-dirs -Wtautological-compare \
								-Wparentheses -Wundef -Wcomment -Wno-redundant-decls -Wno-unused-function \
								-Wno-unused-parameter -Wno-unused-but-set-parameter
CXX_WARNINGS := -Wall -Wextra -Wpedantic -Wpointer-arith -Wcast-align \
								-Wwrite-strings -Wredundant-decls -Winline -Wno-long-long -Wuninitialized \
								-Wno-unused-variable -Winit-self -Wunknown-pragmas -Wstrict-overflow \
								-Warray-bounds -Wchar-subscripts -Wmissing-include-dirs -Wtautological-compare \
								-Wparentheses -Wundef -Wcomment -Wno-redundant-decls -Wno-unused-function \
								-Wno-unused-parameter -Wno-unused-but-set-parameter
C_FLAGS := -std=gnu11 -g $(C_WARNINGS)
CXX_FLAGS := -std=gnu++17 -g $(CXX_WARNINGS)
LD_FLAGS := -O0 -g

C_SOURCES := $(shell find . -type f -name "*.c" -print)
CXX_SOURCES := $(shell find . -type f -name "*.cpp" -print)

C_HEADERS := $(shell find . -type f -name "*.h" -print)
CXX_HEADERS := $(shell find . -type f -name "*.hpp" -print)

SOURCES := $(C_SOURCES) $(CXX_SOURCES)
HEADERS := $(C_HEADERS) $(CXX_HEADERS)

OBJECTS := $(C_SOURCES:.c=.o) $(CXX_SOURCES:.cpp=.o)

INCLUDES := . ./glad/include /usr/include/eigen3 /usr/include/boost
INCLUDE_FLAGS := $(addprefix -I",$(addsuffix ",$(INCLUDES)))

LIBRARIES := m GL X11 pthread Xrandr Xi dl glfw png
LIBRARY_FLAGS := $(addprefix -l",$(addsuffix ",$(LIBRARIES)))

BINARY := ./minecraft

.PHONY: all

all: $(BINARY)
	# @perl -ne " \
	# 	BEGIN {%escapes = (TODO => 32, FIXME => 33, NOTE => 36, BUG => 31, HACK => 31, ISSUE => 31, BROKEN => 31)} \
	# 	chomp; \
	# 	\$$. = 0 if eof; \
	# 	if(/(^.*?\/\/\W*?)(TODO|FIXME|NOTE|BUG|HACK|ISSUE|BROKEN|REVIEW)(?=:)/i){ \
	# 		print \"At \$$ARGV, line \$$.:\n\$$1\x1b[1m\x1b[\" . \$$escapes{uc \$$2} . \"m\$$2\x1b[0m\$$'\n\" \
	# 	} \
	# " $(SOURCES) $(HEADERS)

%.o: %.c
	$(CC) $(C_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

./minecraft: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBRARY_FLAGS) -o $(BINARY)

clean:
	rm $(OBJECTS)
