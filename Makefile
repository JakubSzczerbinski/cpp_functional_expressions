
CXX=g++
CXX_FLAGS=-Werror -Wall -Wextra -std=c++14

cpp_function_expressions: cpp_function_expressions.cpp
	${CXX} ${CXX_FLAGS} cpp_function_expressions.cpp -o cpp_function_expressions

test: test.cpp container.hpp conjunction.hpp void.hpp iterator.hpp
	${CXX} ${CXX_FLAGS} test.cpp -o test

clean:
	rm -f cpp_function_expressions test
