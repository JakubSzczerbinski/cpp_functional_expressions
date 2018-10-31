
CXX=clang++
CXX_FLAGS=-Werror -Wall -Wextra -std=c++14

cpp_function_expressions: cpp_function_expressions.cpp
	${CXX} ${CXX_FLAGS} cpp_function_expressions.cpp -o cpp_function_expressions

clean:
	rm -f cpp_function_expressions
