APPNAME = cache
SRCFOLDER = src/
BINFOLDER = bin/
EXECUTABLES = $(APPNAME)

G++ = g++
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = -pthread

all: $(EXECUTABLES)

$(APPNAME): $(SRCFOLDER)*.cpp
	$(G++) $(CFLAGS) $(SRCFOLDER)*.cpp -o $(BINFOLDER)$(APPNAME) $(LIBS)


.PHONY: memcheck
memcheck:
	valgrind ./$(BINFOLDER)$(APPNAME)

.PHONY: memcheck_full
memcheck_full:
	valgrind --leak-check=full ./$(BINFOLDER)$(APPNAME)

.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind ./$(BINFOLDER)$(APPNAME)

.PHONY: rebuild
rebuild: clean $(EXECUTABLES)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(SRCFOLDER)$(APPNAME).c

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(BINFOLDER)$(EXECUTABLES)