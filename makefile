DIRSERV = ProgServer
DIRCLI  = ProgClient
DIRSYS  = System
DIREXE	= Executable

all: $(DIREXE)/mctr_server.exe $(DIREXE)/mctr_client.exe $(DIREXE)/QTstream.exe

$(DIREXE)/mctr_server.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/mctr_server.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/mctr_server.cpp -pthread -o $(DIREXE)/mctr_server.exe `pkg-config --cflags --libs opencv` -I/usr/local/include/ -lraspicam -lraspicam_cv

$(DIREXE)/mctr_client.exe : $(DIRSYS)/invoke.cpp $(DIRCLI)/mctr_client.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRCLI)/mctr_client.cpp -pthread -o $(DIREXE)/mctr_client.exe `pkg-config --cflags --libs opencv` -I/usr/local/include/ -lraspicam -lraspicam_cv

$(DIREXE)/QTstream.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/QTstream.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/QTstream.cpp -pthread -o $(DIREXE)/QTstream.exe `pkg-config --cflags --libs opencv` -I/usr/local/include/ -lraspicam -lraspicam_cv


webcan:	$(DIRSERV)/mctr_server.exe $(DIREXE)/mctr_client.exe $(DIREXE)/QTstream.exe

$(DIREXE)/mctr_server.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/mctr_server.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/mctr_server.cpp -pthread -o $(DIREXE)/mctr_server.exe `pkg-config --cflags --libs opencv` 

$(DIREXE)/mctr_client.exe : $(DIRSYS)/invoke.cpp $(DIRCLI)/mctr_client.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRCLI)/mctr_client.cpp -pthread -o $(DIREXE)/mctr_client.exe `pkg-config --cflags --libs opencv`

$(DIREXE)/QTstream.exe : $(DIRSYS)/invoke.cpp $(DIRSERV)/QTstream.cpp
	g++ $(DIRSYS)/invoke.cpp $(DIRSYS)/usercall.cpp $(DIRSERV)/QTstream.cpp -pthread -o $(DIREXE)/QTstream.exe `pkg-config --cflags --libs opencv`


clean:
	rm */*.exe


