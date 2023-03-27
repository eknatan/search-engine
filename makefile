LDLIBS = -lcurlpp -lcurl -lgumbo -lsfml-network -lpthread 

CXX=g++-11
CC=$(CXX)

CXXFLAGS = -std=c++20 -Wall -pedantic -Wextra
CXXFLAGS += -Werror

CPPFLAGS = -I crawler/ -I parser/ -I index/ -I data_structures/ -I index_links/ -I rank_page/
CPPFLAGS += -I client/ -I input_output/ -I searcher/ 

OBJECTS = main.o 
OBJECTS += data_structures/queue_safe.o data_structures/unordered_set_safe.o 
OBJECTS += index/indexer_regular.o index/index_map.o
OBJECTS += index_links/index_links.o rank_page/rank_page.o
OBJECTS += parser/parser_url_internal.o parser/parser_words_internal.o
OBJECTS += crawler/crawler.o
OBJECTS += input_output/terminal.o input_output/server.o 
OBJECTS += searcher/searcher_regular.o
OBJECTS += application.o


run: main
	./main

main: $(OBJECTS) $(LDLIBS)

main.o: main.cpp 
parser_url_internal.o: parser/parser_url_internal.hpp parser/parser_url_internal.cpp
parser_words_internal.o: parser/parser_words_internal.hpp parser/parser_words_internal.cpp
index/indexer_regular.o: index/indexer_regular.hpp index/indexer_regular.cpp
index/index_map.o: index/index_map.hpp index/index_map.cpp
crawler/crawler.o: crawler/crawler.cpp
searcher/searcher_regular.o: searcher/searcher_regular.hpp searcher/searcher_regular.cpp
application.o: application.hpp application.cpp
input_output/server.o: input_output/server.hpp input_output/server.cpp
input_output/terminal.o: input_output/terminal.hpp input_output/terminal.cpp
data_structures/queue_safe.o: data_structures/queue_safe.hpp data_structures/queue_safe.cpp
index_links/index_links.o: index_links/index_links.cpp
data_structures/unordered_set_safe.o: data_structures/unordered_set_safe.hpp data_structures/unordered_set_safe.cpp
rank_page/rank_page.o: rank_page/rank_page.hpp rank_page/rank_page.cpp

clean:
	@$(RM) *.o */*.o main
