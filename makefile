make: 
	make calls
	clang++ ./cachat/main.cpp -o cachat # compile against own object-file for custom system calls 


test: 
	clang++ ./cachat/main.cpp -o ut -lCMD --std=c++17
	./ut -f ./test_file.cac