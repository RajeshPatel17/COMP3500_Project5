CC = g++
OBJ = compute.o method.o open.o print.o read.o

scheduler: $(OBJ) scheduler.cpp scheduler.hpp
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