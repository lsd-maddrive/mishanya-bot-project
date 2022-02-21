#* Variables
PYTHON := python3
OS := $(shell uname -o)

.PHONY: prepare-project
prepare-project:
	$(PYTHON) -m venv venv
	PYTHONPATH=venv ; . venv/bin/activate
	pip install -r requirements.txt
	pipx install clang-format
