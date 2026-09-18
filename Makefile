.PHONY: start test add save setup check

# make start P=<leetcode url or slug>   (p= works too)
P ?= $(p)
start:
	@test -n "$(P)" || { echo "usage: make start P=<leetcode url or slug>"; exit 2; }
	python3 lc.py start $(P)

test:
	python3 lc.py test

add:
	python3 lc.py add

save:
	python3 lc.py save

# one-time per clone: install the pre-commit hook
setup:
	git config core.hooksPath .githooks

# lc.py's own tests
check:
	python3 -m pytest tests -q
