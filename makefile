DIRSERV = ProgServer
DIRCLI  = ProgClient
DIRSYS  = System

all: $(DIRSERV)/mctr_server.exe $(DIRCLI)/mctr_client.exe $(DIRSERV)/QTstream.exe

$(DIRSERV)/mctr_server.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/mctr_server.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/mctr_server.cpp -pthread -o $(DIRSERV)/mctr_server.exe `pkg-config --cflags --libs opencv`


$(DIRCLI)/mctr_client.exe : $(DIRSYS)/invoke.cpp $(DIRCLI)/mctr_client.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRCLI)/mctr_client.cpp -pthread -o $(DIRCLI)/mctr_client.exe `pkg-config --cflags --libs opencv`


$(DIRSERV)/QTstream.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/QTstream.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/QTstream.cpp -pthread -o $(DIRSERV)/QTstream.exe `pkg-config --cflags --libs opencv`



clean:
	rm */*.exe


