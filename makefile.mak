CC = g++
OBJ = compute.o method.o open.o print.o read.o


scheduler: $(OBJ) scheduler.cpp scheduler.hpp
	@echo "Creating scheduler"
	$(CC) -o $@ $^ 
%.o: %.cpp %.hpp
	@echo "Creating object file..."
	$(CC) -c $< -o $@
clean:
	@echo "Deleting object and binary files"
	rm -rvf *.o scheduler


