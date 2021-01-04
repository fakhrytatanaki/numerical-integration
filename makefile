main : ./src/dvector.c ./src/main.c ./src/math_expr_parser.c ./src/mathfuncs.c ./src/numerical_integ.c ./src/strsearch.c ./src/treenode.c ./src/vector.c
	gcc ./src/*.c -o integral_calculator
	@echo "a binary executable 'integral_calculator' is generated, execute using the command './integral_calculator'"
