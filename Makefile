# Make file for the PUS Extension of the CORDET Framework
#
################################################################################

CC = gcc
#CC = clang
INCLUDES = -I./src -I./lib/cordetfw/src -I./tests -I./tests/PusConfig -I./lib/cordetfw/lib/fwprofile/src

# Compiler flags for test cases 
CFLAGS_TE = -g2 -O0
# Compiler flags for C code libraries (fwprofile and cordetfw)
CFLAGS_LIB = -g2 -O0
# Compiler flags for PUS Extension code
CFLAGS = -W -Wall -Wextra -pedantic -g2 -O0 -fprofile-arcs -ftest-coverage -fno-exceptions
# Linker flags
LFLAGS =

# Libraries
LIBS = -pthread

HEADERS = $(shell find . -name *.h)

# Source files in FW Profile library
SRCS_FW = $(shell find ./lib/cordetfw/lib/fwprofile/src -name *.c)       
# Source files in CORDET FW library
SRCS_CR = $(shell find ./lib/cordetfw/src -name *.c)       
# Test Suite source files
SRCS_TE = $(shell find ./tests -name *.c)
# C source files of PUS Extension
SRCS_TSC = $(shell find ./src -name *.c)                    

# gcov files
GCOV = $(patsubst %,$(ODIR)/%,$(SRCS_TSC:.c=.gcov))

# Object directory
ODIR = bin

# Object files
OBJS_FW = $(patsubst %,$(ODIR)/%,$(SRCS_FW:.c=.o))
OBJS_CR = $(patsubst %,$(ODIR)/%,$(SRCS_CR:.c=.o))
OBJS_TE = $(patsubst %,$(ODIR)/%,$(SRCS_TE:.c=.o))
OBJS_TSC = $(patsubst %,$(ODIR)/%,$(SRCS_TSC:.c=.o))

OBJS_DIR = $(dir $(OBJS_FW) $(OBJS_CR) $(OBJS_TE) $(OBJS_TSC))

# Executables
MAIN = $(ODIR)/CrPsTestSuite

.PHONY: clean test create_dir coverage run-test coverage-info coverage-cp info

# Print the name of a make variable (e.g. 'make print-SRCS_FW')
print-%: ; @echo $* is $($*)

all: test

info:
	@echo $(shell echo $$0)

# Build the test suite
test: create_dir $(MAIN)

$(MAIN): $(OBJS_FW) $(OBJS_CR) $(OBJS_TSC) $(OBJS_TE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS_FW) $(OBJS_CR) $(OBJS_TSC) $(OBJS_TE) $(LFLAGS) $(LIBS)

$(OBJS_FW): $(ODIR)/%.o: %.c
	$(CC) $(CFLAGS_LIB) $(INCLUDES) -c $< -o $@

$(OBJS_CR): $(ODIR)/%.o: %.c
	$(CC) $(CFLAGS_LIB) $(INCLUDES) -c $< -o $@

$(OBJS_TSC): $(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_TE): $(ODIR)/%.o: %.c
	$(CC) $(CFLAGS_TE) $(INCLUDES) -c $< -o $@

$(GCOV): $(ODIR)/%.gcov: %.c
	@gcov -b -r -o $(shell dirname $@) $<
	

$(OBJS_FW): $(HEADERS)
$(OBJS_CR): $(HEADERS)
$(OBJS_TSC): $(HEADERS)
$(OBJS_TE): $(HEADERS)

# Run the test suite
run-test: 
	$(MAIN)
	
run-test-valgrind:	
	valgrind --leak-check=yes $(MAIN)

# Generate the test coverage information 
gen-lcov: 
	@lcov --capture --directory --rc lcov_branch_coverage=1 $(ODIR)/src -o coverage.info
	@lcov --rc lcov_branch_coverage=1 --remove coverage.info '/usr/*' 'src/Dum/*' 'src/Lpt/*' 'src/Scd/*' -o filtered_coverage.info
	@genhtml --branch-coverage filtered_coverage.info --output-directory lcov

gen-gcov: $(GCOV)
	@mv *.gcov $(ODIR)
	 
# Clean all generated files 
clean:
	@$(RM) filtered_coverage.info
	@$(RM) coverage.info
	@$(RM) *.gcov
	@$(RM) -r lcov
	@$(RM) -r $(ODIR)

create_dir:
	@mkdir -p $(OBJS_DIR)

