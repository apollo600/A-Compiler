.PHONY: run all

all: 
	$(MAKE) -C ../front-end/

run: ../front-end/parser.out
	$(MAKE) -C ../front-end/
	$< ${SRC} -o ./main.ll 2>&1 > ${OUTPUT}