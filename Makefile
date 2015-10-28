ifdef SYSTEMROOT
   RM = del /Q
   BIN=build/bin/kiv_os.exe
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      BIN=build/bin/kiv_os
      FixPath = $1
   endif
endif


CC=gcc
CFLAGS_LINK=-Wall -std=c99 -pedantic -mtune=native -march=native -Os
#CFLAGS=-Wall -std=gnu89 -pedantic -mtune=native -march=native -Os -fnoomit-frame-pointer
CFLAGS=-Wall -std=c99 -pedantic -mtune=native -march=native -Os



OBJ_SHELL=shell/shell.o shell/parse.o
SRC_SHELL=shell/shell.c shell/parse.c
OBJ_CP=utils/cp/cp.o
SRC_CP=utils/cp/cp.c
OBJ_MV=utils/mv/mv.o
SRC_MV=utils/mv/mv.c
OBJ_TOUCH=utils/touch/touch.o
SRC_TOUCH=utils/touch/touch.c
OBJ_RM=utils/rm/rm.o
SRC_RM=utils/rm/rm.c
OBJ_LS=utils/ls/ls.o
SRC_LS=utils/ls/ls.c

all: $(BIN)

$(OBJ_SHELL): $(SRC_SHELL)
	@echo -e "\nshell\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/shell\n"	
$(OBJ_CP): $(SRC_CP)
	@echo -e "\n\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/\n"	
$(OBJ_MV): $(SRC_MV)
	@echo -e "\n\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/\n"
$(OBJ_TOUCH): $(SRC_TOUCH)
	@echo -e "\n\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/\n"
$(OBJ_RM): $(SRC_RM)
	@echo -e "\n\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/\n"
$(OBJ_LS): $(SRC_LS)
	@echo -e "\n\n"
	$(CC) -c $(CFLAGS) $*.c -o $@
	@echo -e "\n/\n"	


################  MAIN ##################
	
$(BIN): $(OBJ_SHELL) $(OBJ_CP) $(OBJ_MV) $(OBJ_TOUCH) $(OBJ_RM) $(OBJ_LS)
	@echo -e "\n linking: kiv_os\n"
	$(CC) $(CFLAGS_LINK) $^ -o $@
	@echo -e "\n /linking: kiv_os\n"
	@echo -e "################  /MAIN ##################\n\n"
################  /MAIN   ##################


clean:
	$(RM) $(BIN)
	$(RM) $(OBJ_SHELL) $(OBJ_CP) $(OBJ_MV) $(OBJ_TOUCH) $(OBJ_RM) $(OBJ_LS)