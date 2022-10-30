#* Variables
OS := $(shell uname -o)

# ===================================================================
# Development. Start Work
# ===================================================================

POETRY_VERSION ?= 1.2.0

#* Poetry
.PHONY: poetry-install
poetry-install:
	curl -sSL https://install.python-poetry.org | $(PYTHON) - --version ${POETRY_VERSION}

.PHONY: poetry-remove
poetry-remove:
	curl -sSL https://install.python-poetry.org | $(PYTHON) - --uninstall

#* Environment control
.PHONY: env-init
env-init: env-install-deps env-tools-install

.PHONY: env-install-deps
env-install-deps:
	poetry install --no-interaction

.PHONY: env-tools-install
env-tools-install:
	poetry run pre-commit install
	poetry run pre-commit install --hook-type commit-msg