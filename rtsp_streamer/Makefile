FILES = rtsp_streamer

################################################################################

#MAKE_OPT = --no-print-directory -j `grep -c processor /proc/cpuinfo`

all: compile $(FILES)

$(FILES): % : unix/build/%.build
	@echo "--- copying: $@"
	@cp -f $< $@

compile:
	@make $(MAKE_OPT) -C unix

clean:
	@make $(MAKE_OPT) -C unix clean

distclean:	clean

check:
	@make $(MAKE_OPT) -C unix check
	@unix/build/rtsp_streamer.unittest

docs:
	@echo "--- generating docs"
	@doxygen doc/doxygen.cfg > /dev/null # show only warnings and errors
	@make -C doc/api/latex refman.pdf
	@cp doc/api/latex/refman.pdf ./rtsp_streamer.pdf

################################################################################

