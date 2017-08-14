CC:=gcc
DEPEND:=obj/main.o
DEPEND+=obj/lottery.o
DEPEND+=obj/lotlink.o
DEPEND+=obj/lotcontrol.o
DEPEND+=obj/lotview.o

#obj/%.i:src/%.c
#	$(CC) -E $^ -o $@ -I include
#obj/%.s:obj/%.i
#	$(CC) -S $^ -o $@ -Wall
#obj/%.o:obj/%.s
#	$(CC) -c $^ -o $@
obj/%.o:src/%.c
	$(CC) -c $^ -o $@ -Wall -I include -lm
bin/main:$(DEPEND)
	$(CC)    $^ -o $@
	bin/main




clean:
	rm -rf $(DEPEND)
	rm -rf src/*.c~
	rm -rf bin/main~
	clear

	



#DEPEND:=src/main.c
#DEPEND+=src/lottery.c
#DEPEND+=src/lotcontrol.c
#DEPEND+=src/lotview.c
#bin/main:$(DEPEND)
#	$(CC)    $^ -o $@ -Wall -I include

