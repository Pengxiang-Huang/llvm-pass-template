CLANG ?= clang
OPT   ?= opt

# pass name 
PASS_OPT ?= my-legacy-pass

PLUGIN := ../../install/lib/MyLegacyPass.so

# Exactly one C file in this directory
CFILE := $(wildcard *.c)
LL    := test.ll
OPTBC := test_opt.bc
OPTLL := test_opt.ll
OUT   := out.txt
BIN   := test
SUBDIRS := $(wildcard */)

all: pass bin 

pass: $(LL) 
	$(OPT) -load $(PLUGIN) -$(PASS_OPT) $(LL) -o $(OPTBC) > $(OUT) 2>&1
	@echo "Wrote $(OUT)"
	cat out.txt
	llvm-dis $(OPTBC) -o $(OPTLL)

bin: $(BIN)

$(BIN): $(CFILE)
	$(CLANG) -O0 -g \
	  -Xclang -load -Xclang $(PLUGIN) \
	  -o $(BIN) $(CFILE)

$(LL): $(CFILE)
	$(CLANG) -O0 -g -S -emit-llvm -o $(LL) $(CFILE)

clean:
	rm -f $(OPTBC) $(OPTLL) $(LL) $(OUT) $(BIN)
