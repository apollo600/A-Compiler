.PHONY: run all clean

SRC = ./function_test2021/001_var_defn.sy 
IR = ./main.ll
OUTPUT = ./parser-output.txt

all: 
	$(MAKE) -C ../front-end/

run: ./parser.out
	$(MAKE) -C ../front-end/
	$< ${SRC} -o ${IR} 2>&1 > ${OUTPUT}

clean:
	$(MAKE) -C ../front-end/ clean