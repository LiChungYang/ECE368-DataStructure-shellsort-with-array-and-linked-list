CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa1
OBJS =  pa1.o shell_array.o shell_list.o
HOBJS = shell_array.h shell_list.h list_of_list.h
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose


$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

test: $(EXEC)
	./$(EXEC) -l examples/0.b outputl0.b
	diff outputl0.b examples/0sl.b
	./$(EXEC) -l examples/15.b outputl15.b
	diff outputl15.b examples/15sl.b
	./$(EXEC) -l examples/1K.b outputl1K.b
	diff outputl1K.b examples/1Ksl.b
	./$(EXEC) -a examples/0.b outputa0.b
	diff outputa0.b examples/0sa.b
	./$(EXEC) -a examples/15.b outputa15.b
	diff outputa15.b examples/15sa.b
	./$(EXEC) -a examples/1K.b outputa1K.b
	diff outputa1K.b examples/1Ksa.b

array: $(EXEC)
	./$(EXEC) -a examples/1M.b output1M.b
	./$(EXEC) -a examples/100K.b output100K.b
	./$(EXEC) -a examples/10K.b output10K.b
	./$(EXEC) -a examples/1K.b output1K.b
	./$(EXEC) -a examples/15.b output15.b

ll: $(EXEC)
	./$(EXEC) -l examples/1M.b outputll1M.b
	./$(EXEC) -l examples/100K.b outputll100K.b
	./$(EXEC) -l examples/10K.b outputll10K.b	
	./$(EXEC) -l examples/15.b outputll15.b

empty: $(EXEC)
	./$(EXEC) -l examples/0.b outputl.b
	./$(EXEC) -a examples/0.b outputa.b

memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) -a examples/15.b moutputs/outputArr
	$(VALGRIND) ./$(EXEC) -l examples/15.b moutputs/outputLL

%.o : %.c
	$(GCC) -c $< 

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f *.bin *.b
	/bin/rm -rf outputs
	/bin/rm -rf moutputs
	/bin/rm -f id? first? last? log?
