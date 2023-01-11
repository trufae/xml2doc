PREFIX = /usr
XD=../src/xml2doc

all:
	@for A in *.xml; do $(XD) -oP $$A $$A.pdf 2> /dev/null ||\
		xml2doc -oP $$A $$A.pdf ; done
	@rm -f manpage.pdf
	@xml2doc -oM manpage.xml manpage.man

mrproper: clean
	rm -f Makefile

clean:
	@rm -f *.abw *.html *.txt *.pdf *.man

install:
	@printf "\e[32mInstalling examples...\e[0m\n"
	mkdir -p $(PREFIX)/share/doc/xml2doc/examples
	cp -f *.xml $(PREFIX)/share/doc/xml2doc/examples
	
remove:
	@printf "\e[32mDeinstalling examples...\e[0m\n"
	rm -rf $(PREFIX)/share/doc/xml2doc/examples
