FLAGS = -Wall
COMP = g++

ALG_OBJS = rec.o memo.o dp.o dpo.o

main: src/test.cpp inc/test.h ${ALG_OBJS}
	${COMP} ${FLAGS} -o test.exe src/test.cpp ${ALG_OBJS}

rec.o: src/recursive.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/recursive.cpp -o rec.o

memo.o: src/memoization.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/memoization.cpp -o memo.o

dp.o: src/dynamic_prog.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/dynamic_prog.cpp -o dp.o

dpo.o: src/dynamic_prog_opt.cpp inc/algorithms.h
	${COMP} ${FLAGS} -c src/dynamic_prog_opt.cpp -o dpo.o
