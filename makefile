DIRSERV = ProgServer
DIRCLI  = ProgClient
DIRSYS  = System
DIREXE	= Executable
FLAGRASP = -I/usr/local/include/ -lraspicam -lraspicam_cv
FLAGOPENCV = `pkg-config --cflags --libs opencv`


all: $(DIRSERV)/mctr_server.exe $(DIREXE)/mctr_client.exe $(DIREXE)/QTstream.exe

$(DIRSERV)/mctr_server.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/mctr_server.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/mctr_server.cpp -pthread -o $(DIREXE)/mctr_server.exe $(FLAGOPENCV) $(FLAGRASP)

$(DIREXE)/mctr_client.exe : $(DIRSYS)/invoke.cpp $(DIRCLI)/mctr_client.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRCLI)/mctr_client.cpp -pthread -o $(DIREXE)/mctr_client.exe $(FLAGOPENCV) $(FLAGRASP)

$(DIREXE)/QTstream.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/QTstream.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/QTstream.cpp -pthread -o $(DIREXE)/QTstream.exe $(FLAGOPENCV) $(FLAGRASP)



clean:
	rm */*.exe


