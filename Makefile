
SDIR = src
TDIR = tests
BDIR = build

CC = gcc
CFLAGS = -Iinclude -I.
CFILES = $(SDIR)/*.c

TPREF = test_
UPATH = unity/unity.c
OUTPUT = main.bin

all: compile

compile: $(CFILES)
	@mkdir -p $(BDIR)
	$(CC) $(CFLAGS) $^ -o $(BDIR)/$(OUTPUT)

test: testcompile
	@for testbin in $(BDIR)/$(TPREF)*.bin; do \
		echo ===$$testbin===; \
		./$$testbin; \
		echo; \
	done

testcompile:
	@mkdir -p $(BDIR)
	@for testfile in $(TDIR)/*; do \
		srcfile="$(SDIR)/$${testfile#$(TDIR)/$(TPREF)}"; \
		if [ -f $$srcfile ]; then \
			stripped="$${srcfile#$(SDIR)/}"; \
			outfile="$(BDIR)/$(TPREF)$${stripped%.c}.bin"; \
			$(CC) $(CFLAGS) $(UPATH) $$testfile $$srcfile -o $$outfile; \
		fi; \
	done

