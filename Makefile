.PHONY: start next test add save commit setup check

# make start P=<leetcode url or slug>   (p= works too)
P ?= $(p)
start:
	@test -n "$(P)" || { echo "usage: make start P=<leetcode url or slug>"; exit 2; }
	python3 lc.py start $(P)

# start the first unticked problem in ROADMAP.md
next:
	python3 lc.py next

test:
	python3 lc.py test

add:
	python3 lc.py add

save:
	python3 lc.py save

# commit the current problem as "feat: solved N. Title [Difficulty]" (hook saves it into problems/)
commit:
	python3 lc.py commit

# one-time per clone: install the pre-commit hook
setup:
	git config core.hooksPath .githooks

# lc.py's own tests
check:
	python3 -m pytest tests -q
