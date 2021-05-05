APPNAME = potato
SRCFOLDER = src/
BINFOLDER = bin/
EXECUTABLES = $(APPNAME) $(APPNAME)_asan $(APPNAME)_msan $(APPNAME)_tsan $(APPNAME)_ubsan

CC = cc
CC2 = clang
CFLAGS = -g -Wall -Wextra
LIBS = -pthread

all: $(EXECUTABLES)

$(APPNAME): $(SRCFOLDER)$(APPNAME).c
	$(CC) $(CFLAGS) $(SRCFOLDER)$(APPNAME).c -o $(BINFOLDER)$(APPNAME) $(LIBS)

$(APPNAME)_asan: $(SRCFOLDER)$(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=address $(SRCFOLDER)$(APPNAME).c -o $(BINFOLDER)$(APPNAME)_asan $(LIBS)

$(APPNAME)_msan: $(SRCFOLDER)$(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=memory $(SRCFOLDER)$(APPNAME).c -o $(BINFOLDER)$(APPNAME)_msan $(LIBS)

$(APPNAME)_tsan: $(SRCFOLDER)$(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=thread $(SRCFOLDER)$(APPNAME).c -o $(BINFOLDER)$(APPNAME)_tsan $(LIBS)

$(APPNAME)_ubsan: $(SRCFOLDER)$(APPNAME).c
	$(CC2) $(CFLAGS) -fsanitize=undefined $(SRCFOLDER)$(APPNAME).c -o $(BINFOLDER)$(APPNAME)_ubsan $(LIBS)

.PHONY: memcheck
memcheck:
	valgrind ./$(BINFOLDER)$(APPNAME)

.PHONY: memcheck_full
memcheck_full:
	valgrind --leak-check=full ./$(BINFOLDER)$(APPNAME)


.PHONY: helgrind
helgrind:
	valgrind --tool=helgrind --quiet ./$(BINFOLDER)$(APPNAME)

.PHONY: rebuild
rebuild: clean $(BINFOLDER)$(APPNAME)

.PHONY: lint
lint:
	cpplint --filter=-readability/casting $(SRCFOLDER)$(APPNAME).c

.PHONY: gitignore
gitignore:
	echo $(EXECUTABLES) | tr " " "\n" > .gitignore

.PHONY: clean
clean:
	rm -rf $(EXECUTABLES)