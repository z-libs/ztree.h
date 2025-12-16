
BUNDLER = z-core/zbundler.py
SRC = src/ztree.c
DIST = ztree.h

all: bundle

bundle:
	@echo "Bundling $(DIST)..."
	python3 $(BUNDLER) $(SRC) $(DIST)

init:
	git submodule update --init --recursive

.PHONY: all bundle init


