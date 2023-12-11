# these targets don't prooduce files
PHONY: main runday runall gprof clean clearscreen

# get all folders in format XX (day number)
# days = $(shell ls | grep -E '^[0-9]{2}$$')
days = $(wildcard [0-9]*/)

main:

runday: $(day)/sol.out 
	cd $(day) && ./sol.out && cd ..

$(day)/sol.out: $(day)/day$(day).cpp
	g++ -std=c++11 -o $@ $^ 

$(day)/sol_gprof.out: $(day)/day$(day).cpp
	g++ -std=c++11 -pg -o $@ $^ 

clearscreen:
	@clear

runall: ./[0-9]*
	@echo "\n"
	@for d in $^ ; do \
		 $(MAKE) -s runday day=$$d 2>/dev/null \
		 || (echo "day $$d could not be executed (run 'make run day=$$d' to see error output)") &&	echo "" ; \
	done

clean: ./[0-9]*
	for d in $^ ; do \
		rm -f $$d/sol.out;\
	done

gprof: $(day)/sol_gprof.out
	cd $(day) && ./sol_gprof.out && gprof sol.out gmon.out > analysis.txt && cd ..
	less $(day)/analysis.txt


