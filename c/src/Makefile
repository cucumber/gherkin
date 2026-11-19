# Compiler and tools. These already default to something sensible for the
# current OS (make's built-in CC is "cc", AR is "ar"), so only set them here
# if they're not already set - this lets you override them on the command
# line or via the environment, e.g. `make CC=clang` or
# `CC=arm-linux-gnueabihf-gcc make`.
CC ?= gcc
AR ?= ar
LD = $(CC)

CFLAGS ?= -Wall -Werror -g -fPIC
LDFLAGS ?=
ARFLAGS ?= cr
SOFLAGS ?= -shared

# Cross-compiling for Windows using mingw needs a few adjustments: no
# -fPIC, a dedicated archiver, and an .exe extension on the binaries.
ifeq ($(CC),i686-w64-mingw32-gcc)
	AR = i686-w64-mingw32-ar
	CFLAGS = -Wall -Werror -g
	EXT = .exe
endif

GENERATE_DEPS_FLAGS=-MMD -MP -MF $(basename $@).d
LDLIBS=-lm
RM_CMD=rm -rf
MKDIR_CMD=mkdir -p

VERSION=$(shell cat ../VERSION)

all: \
  cli \
	../bin/gherkin_generate_tokens$(EXT) \
	libs_so
.PHONY: all

cli: ../bin/gherkin$(EXT)
.PHONY: cli

libs: ../libs/libgherkin.a
.PHONY: libs

libs_so: ../libs/libgherkin.so.$(VERSION)
.PHONY: libs_so

clean:
	$(RM_CMD) ../bin ../objs ../libs
.PHONY: clean

UTILITIES_OBJS= \
	../objs/file_reader.o \
	../objs/file_utf8_source.o \
	../objs/print_utilities.o \
	../objs/string_utilities.o \
	../objs/unicode_utilities.o \
	../objs/utf8_source.o \
	../objs/incrementing_id_generator.o
-include $(UTILITIES_OBJS:.o=.d)

PARSER_OBJS= \
	../objs/parser.o \
	../objs/token_scanner.o \
	../objs/file_token_scanner.o \
	../objs/string_token_scanner.o \
	../objs/token_matcher.o \
	../objs/token.o \
	../objs/token_queue.o \
	../objs/item_queue.o \
	../objs/gherkin_line.o \
	../objs/error.o \
	../objs/error_list.o \
	../objs/dialect.o
-include $(PARSER_OBJS:.o=.d)

AST_OBJS= \
	../objs/ast_builder.o \
	../objs/ast_node.o \
	../objs/gherkin_document.o \
	../objs/feature.o \
	../objs/rule.o \
	../objs/scenario.o \
	../objs/background.o \
	../objs/comment.o \
	../objs/data_table.o \
	../objs/doc_string.o \
	../objs/example_table.o \
	../objs/step.o \
	../objs/table_cell.o \
	../objs/table_row.o \
	../objs/tag.o
-include $(AST_OBJS:.o=.d)

COMPILER_OBJS= \
	../objs/compiler.o
-include $(COMPILER_OBJS:.o=.d)

PICKLES_OBJS= \
	../objs/pickle.o \
	../objs/pickle_ast_node_id.o \
	../objs/pickle_cell.o \
	../objs/pickle_row.o \
	../objs/pickle_step.o \
	../objs/pickle_string.o \
	../objs/pickle_table.o \
	../objs/pickle_tag.o
-include $(PICKLES_OBJS:.o=.d)

EVENT_OBJS= \
	../objs/event.o \
	../objs/error_event.o \
	../objs/gherkin_document_event.o \
	../objs/pickle_event.o \
	../objs/source_event.o \
	../objs/ast_printer.o \
	../objs/pickle_printer.o
-include $(EVENT_OBJS:.o=.d)

GENERATE_TOKEN_OBJS= \
	../objs/token_formatter_builder.o \
	../objs/gherkin_generate_tokens.o
-include $(GENERATE_TOKEN_OBJS:.o=.d)

GHERKIN_CLI_OBJS= \
	../objs/gherkin_cli.o
-include $(GHERKIN_CLI_OBJS:.o=.d)

../objs/%.o: %.c Makefile
	$(MKDIR_CMD) $(dir $@)
	$(CC) -c $(CFLAGS) $(GENERATE_DEPS_FLAGS) -I ../include -I . $< -o $@

../libs/libgherkin.a: $(UTILITIES_OBJS) $(PARSER_OBJS) $(AST_OBJS) $(COMPILER_OBJS) $(PICKLES_OBJS) $(EVENT_OBJS) Makefile
	$(MKDIR_CMD) $(dir $@)
	$(AR) $(ARFLAGS) $@ $(UTILITIES_OBJS) $(PARSER_OBJS) $(AST_OBJS) $(COMPILER_OBJS) $(PICKLES_OBJS) $(EVENT_OBJS)

../libs/libgherkin.so.$(VERSION): $(UTILITIES_OBJS) $(PARSER_OBJS) $(AST_OBJS) $(COMPILER_OBJS) $(PICKLES_OBJS) $(EVENT_OBJS) Makefile
	$(MKDIR_CMD) $(dir $@)
	$(CC) $(SOFLAGS) $(UTILITIES_OBJS) $(PARSER_OBJS) $(AST_OBJS) $(COMPILER_OBJS) $(PICKLES_OBJS) $(EVENT_OBJS) -o $@

../bin/gherkin_generate_tokens$(EXT): ../libs/libgherkin.a $(GENERATE_TOKEN_OBJS) Makefile
	$(MKDIR_CMD) $(dir $@)
	$(LD) $(LDFLAGS) $(GENERATE_TOKEN_OBJS) -L../libs/ -lgherkin $(LDLIBS) -o $@

../bin/gherkin$(EXT): ../libs/libgherkin.a $(GHERKIN_CLI_OBJS) Makefile
	$(MKDIR_CMD) $(dir $@)
	$(LD) $(LDFLAGS) $(GHERKIN_CLI_OBJS) -L../libs/ -lgherkin $(LDLIBS) -o $@
