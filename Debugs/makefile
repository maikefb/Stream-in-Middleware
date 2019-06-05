all: s.exe c.exe

s.exe : serv.cpp
	gcc $< -pthread -o $@
c.exe : cli.cpp
	gcc $< -pthread -o $@
clean:
	rm *.exe