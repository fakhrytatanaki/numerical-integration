main : ./src/dvector.c ./src/main.c ./src/math_expr_parser.c ./src/mathfuncs.c ./src/numerical_integ.c ./src/strsearch.c ./src/treenode.c ./src/vector.c
	gcc ./src/*.c -o integration_calculator
	@echo "a binary executable 'integration_calculator' is generated, execute using the command './integration_calculator'"

clean :
	rm ./integration_calculator
