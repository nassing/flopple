## Pour générer les motifs

patterns.o : list_str.h list_str.c patterns.h patterns.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c patterns.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c patterns.c

test_patterns.o : list_str.h list_str.c patterns.h patterns.c test_patterns.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_patterns.c

test_patterns : list_str.o patterns.o test_patterns.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address list_str.o patterns.o test_patterns.o -o test_patterns


## Pour les listes de chaines de caractères

list_str.o : list_str.h list_str.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c list_str.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c list_str.c

test_list_str.o : list_str.h list_str.c test_list_str.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_list_str.c

test_list_str : list_str.o test_list_str.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address list_str.o test_list_str.o -o test_list_str


## Pour le dicionnaire

dictionary.o : list_str.h list_str.c dictionary.h dictionary.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c dictionary.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c dictionary.c

test_dictionary.o : list_str.h list_str.c dictionary.h dictionary.c test_dictionary.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_dictionary.c

test_dictionary : list_str.o dictionary.o test_dictionary.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address list_str.o dictionary.o test_dictionary.o -o test_dictionary


## Pour gérer la compatibilité

compatible.o : list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c compatible.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c compatible.c

test_compatible.o : list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c test_compatible.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_compatible.c

test_compatible : list_str.o dictionary.o compatible.o test_compatible.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address list_str.o dictionary.o compatible.o test_compatible.o -o test_compatible


## Pour chercher le mot idéal

bestGuess.o : list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c bestGuess.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c bestGuess.c

test_bestGuess.o : patterns.h patterns.c list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c test_bestGuess.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_bestGuess.c

test_bestGuess : patterns.o list_str.o dictionary.o compatible.o bestGuess.o test_bestGuess.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address patterns.o list_str.o dictionary.o compatible.o bestGuess.o test_bestGuess.o -o test_bestGuess


## Pour gérer la lecture de fichiers

files.o : patterns.h patterns.c list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c files.h files.c solver.h solver.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c files.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c files.c

test_files.o : patterns.h patterns.c list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c files.h files.c solver.h solver.c test_files.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_files.c

test_files : patterns.o list_str.o dictionary.o compatible.o bestGuess.o files.o solver.o test_files.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address patterns.o list_str.o dictionary.o compatible.o bestGuess.o files.o solver.o test_files.o -o test_files


## Pour lancer le solveur

solver.o : patterns.h patterns.c list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c files.h files.c solver.h solver.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c solver.h
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c solver.c

test_solver.o : patterns.h patterns.c list_str.h list_str.c dictionary.h dictionary.c compatible.h compatible.c bestGuess.h bestGuess.c files.h files.c solver.h solver.c test_solver.c
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address -c test_solver.c

test_solver : patterns.o list_str.o dictionary.o compatible.o bestGuess.o files.o solver.o test_solver.o
	clang -std=c99 -Wall -Wextra -pedantic -g3 -fsanitize=address patterns.o list_str.o dictionary.o compatible.o bestGuess.o files.o solver.o test_solver.o -o test_solver

