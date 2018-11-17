
CXX=g++
CXX_FLAGS=-Werror -Wall -Wextra -std=c++14

test: test.cpp container.hpp conjunction.hpp void.hpp iterator.hpp equality_comparable.hpp input_iterator.hpp output_iterator.hpp forward_iterator.hpp
	${CXX} ${CXX_FLAGS} test.cpp -o test && ./test

clean:
	rm -f cpp_function_expressions test
