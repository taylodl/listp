OBJS=value.o symbol.o cons.o
LINKTARGET=listp
REBUILDABLES=$(OBJS) $(LINKTARGET)

# make clean (remove all rebuildables)
clean:
	rm -f $(REBUILDABLES)

# make all (equivalent to make listp)
all: $(LINKTARGET)

# make listp (will build all $(OBJS) first)
$(LINKTARGET): $(OBJS)
	gcc -o $@ $^

# build .o files from their respective .c source
%.o: %.c
	gcc -c $< -o $@

# Dependency rules
symbol.o: symbol.h aliases.h
cons.o: symbol.h cons.h aliases.h
value.o: value.h symbol.h cons.h aliases.h

