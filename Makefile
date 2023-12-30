#######################################################################################################
# Copyright (C) Icon-Changer 2024                                                                     #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   14.08.2023  Gaina Stefan               Initial version.                                           #
#   30.12.2023  Gaina Stefan               Added copyright.                                           #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

export CC = gcc

export SRC := src
export OBJ := obj
export LIB := lib
export BIN := bin

export COVERAGE_REPORT := coverage_report

GENHTML       = vendor/lcov/genhtml.perl
GENHTML_FLAGS = --branch-coverage --num-spaces=4 --output-directory $(COVERAGE_REPORT)/

INFO_FILES = $(COVERAGE_REPORT)/icon-changer.info

### MAKE SUBDIRECTORIES ###
all:
	$(MAKE) -C icon-changer

### CLEAN SUBDIRECTORIES ###
clean:
	$(MAKE) clean -C icon-changer

### MAKE UNIT-TESTS ###
ut: create_dir
	$(MAKE) -C unit-tests
	$(MAKE) run_tests -C unit-tests
	perl $(GENHTML) $(INFO_FILES) $(GENHTML_FLAGS)

### CREATE DIRECTORY ###
create_dir:
	if not exist "$(COVERAGE_REPORT)" mkdir $(COVERAGE_REPORT)

### CLEAN UNIT-TESTS ###
ut-clean:
	$(RM) $(COVERAGE_REPORT)\*
	$(RM) $(COVERAGE_REPORT)\src\*
	rd /s /q $(COVERAGE_REPORT)\src
