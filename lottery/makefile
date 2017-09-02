CC:=gcc
CFLAGS:=-Iinclude
CFLAGS+=-c
TARGET:=bin/main
DEPEND:=obj/main.o
DEPEND+=obj/lottery.o
DEPEND+=obj/lotlink.o
DEPEND+=obj/lotcontrol.o
DEPEND+=obj/lotview.o

$(TARGET):$(DEPEND)
	$(CC) -o $@ $^ -lm
obj/%.o:src/%.c
	$(CC) -o $@ $(CFLAGS) $^ -Wall



do:
	./bin/main


clean:
	rm -rf $(DEPEND)
	clear

	




