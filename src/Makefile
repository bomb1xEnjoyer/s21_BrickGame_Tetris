CC = gcc

VERSION = 1.0-1

FOLDER_SRC = ./brick_game/tetris/
FOLDER_GUI = ./gui/cli/

EXEC = tetris
EXECUTABLE = brick_game.a

MAIN = $(wildcard main.c)
MAIN_O = $(patsubst %.c, %.o, $(MAIN))

SRC = $(wildcard $(FOLDER_SRC)*.c $(FOLDER_GUI)*.c)
HEADERS = $(wildcard $(FOLDER_SRC)*.h $(FOLDER_GUI)*.h)
OBJECTS = $(patsubst %.c, %.o, $(SRC))

CFLAGS = -std=c11 -Wall -Werror -Wextra -lm -lncurses
# LIBSFLAGS = -lcheck -lm -lrt -lpthread -lncurses -lm -D_GNU_SOURCE
LIBSFLAGS = -lcheck -lm -lsubunit -lrt -lpthread -D_GNU_SOURCE

VALGRIND = valgrind --tool=memcheck --leak-check=yes

TEST_FILES_C = tests/*.c
TEST_FILES_H = tests/*.h

CLANG = clang-format -style=Google

all: $(EXECUTABLE) install test gcov_report doxy

install: uninstall $(EXECUTABLE) $(MAIN)
	$(CC) -c $(MAIN) -o $(MAIN_O) $(CFLAGS) $(LIBSFLAGS) 
	$(CC) $(MAIN_O) $(EXECUTABLE) -o $(EXEC) $(CFLAGS) $(LIBSFLAGS) 
	rm -rf *.o
	mkdir ~/$(EXEC)
	install ./$(EXEC) ~/$(EXEC)/

$(EXECUTABLE): $(OBJECTS)
	ar rc $(EXECUTABLE) $(OBJECTS)
	ranlib $(EXECUTABLE)
	rm -rf $(OBJECTS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBSFLAGS)

uninstall: 
	rm -rf ~/$(EXEC) $(EXEC)

doxy: clean_doxy
	doxygen

dist:
	mkdir dist
	cp -a ./brick_game.c ./dist/
	cp -a ./brick_game/ ./dist/
	cp -a ./Makefile ./dist/ 
	cp -a ./gui/ ./dist/ 
	cp -a ./README.dvi ./dist/ 
	tar -czf $(EXEC)_$(VERSION).tar.gz ./dist/
	rm -rf ./dist/

clean_dist:
	rm -rf *.tar.gz

test: clean_test $(EXECUTABLE)
	$(CC) -o test $(TEST_FILES_C) $(EXECUTABLE) $(CFLAGS) $(LIBSFLAGS)
	./test

gcov_report: clean_test clean_report $(EXECUTABLE)
	$(CC) --coverage $(SOURCE) ${TEST_FILES_C} $(EXECUTABLE) $(CFLAGS) $(LIBSFLAGS) -o test
	./test
	gcovr -r . --html-details -o gcov_report.html
	# ~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	mkdir report
	mv *.html *.css report
	rm -rf *.gcno *.gcda

test_valgrind: test
	$(VALGRIND) ./test

clean_test:
	rm -rf test

clean_doxy:
	rm -rf doxygen

clean_report:
	rm -rf *.gcno *.gcda *.html *.css report

clean_highscore: 
	rm -rf highscore.txt

clean: clean_highscore clean_report clean_test clean_doxy
	rm -rf $(OBJECTS) $(EXECUTABLE) $(MAIN_O) $(EXEC)
