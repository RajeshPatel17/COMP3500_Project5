# to use "make"
# % make -f Makefile.mak *policy*
# 
# to run scheduler program
# ./scheduler file_name [FCFS|RR [time_quantum]|SRTF]
CC = g++ # g++ compiler
OBJ = compute.o method.o open.o print.o read.o # all required object files

scheduler: $(OBJ) scheduler.cpp scheduler.hpp # for compiling scheduler
	@echo "Creating scheduler"
	$(CC) -o $@ $^ 
debug: $(OBJ) scheduler.cpp scheduler.hpp
	@echo "Debugging program"
	$(CC) $(OBJ) scheduler.hpp -g scheduler.cpp -o scheduler.exe
%.o: %.cpp %.hpp
	@echo "Creating object file..."
	$(CC) -c $< -o $@
clean:
	@echo "Deleting object and binary files"
	rm -rvf *.o scheduler