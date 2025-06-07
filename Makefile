FLAGS = -Wall -Wextra -g
COMP = g++

ALG_OBJS = rec.o memo.o dp.o dpo.o

main: main.cpp ${ALG_OBJS} main_alg.o testing.o
	${COMP} ${FLAGS} main.cpp ${ALG_OBJS} main_alg.o testing.o -o main.exe

main_alg.o: src/edit_distance.cpp inc/edit_distance.h
	${COMP} ${FLAGS} -c src/edit_distance.cpp -o main_alg.o

rec.o: src/recursive.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/recursive.cpp -o rec.o

memo.o: src/memoization.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/memoization.cpp -o memo.o

dp.o: src/dynamic_prog.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/dynamic_prog.cpp -o dp.o

dpo.o: src/dynamic_prog_opt.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/dynamic_prog_opt.cpp -o dpo.o

testing.o: src/testing.cpp inc/testing.h
	${COMP} ${FLAGS} -c src/testing.cpp -o testing.o
