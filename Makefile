CXXFLAGS=-fsanitize=address -fsanitize=undefined -O0 -ggdb3 -std=c++11
LDFLAGS=-fsanitize=address -fsanitize=undefined
blockchain: Block.o Block_Chain_Header.o Block_Msg.o Main.o Sha256.o Sort_Array.o Sort_Element.o Transaction_Input_Msg.o Transaction_Msg.o Transaction_Output_Msg.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^

clean:
	rm -f blockchain *.o

