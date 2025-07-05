STYLE_DIR ?= /usr/share/zdoc

docs = user-manual.pdf

all: $(images) $(docs) output

output:
	mkdir -p output
	mv *.pdf output

clean:
	rm -f $(docs) $(images) *.png
	rm -rf output/

STYLE_CLASS = document
include $(STYLE_DIR)/Makefile.rules
