# GNU Make solution makefile autogenerated by GENie
# Type "make help" for usage help

ifndef config
  config=debug
endif
export config

PROJECTS := Engine Game

.PHONY: all clean help $(PROJECTS)

all: $(PROJECTS)

Game: 
	@echo "==== Building Game ($(config)) ===="
	@${MAKE} --no-print-directory -C ../Project -f Game.make

Engine: 
	@echo "==== Building Engine ($(config)) ===="
	@${MAKE} --no-print-directory -C ../Project -f Engine.make

clean:
	@${MAKE} --no-print-directory -C ../Project -f Game.make clean
	@${MAKE} --no-print-directory -C ../Project -f Engine.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "   debug"
	@echo "   release"
	@echo "   debug64"
	@echo "   release64"
	@echo "   debug32"
	@echo "   release32"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Game"
	@echo "   Engine"
	@echo ""
	@echo "For more information, see https://github.com/bkaradzic/genie"
