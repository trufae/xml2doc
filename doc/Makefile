PREFIX = /usr
DOCS = ../README ../TODO ../BUGS

all:
	@printf "\e[32mUse make in the parent directory.\e[0m\n"

build:
	@printf "\e[32mBuilding documentation...\e[0m\n"
	export PATH=$(PATH):$(PWD)/src/                   ;
	for A in *.xml; do xml2doc -oP $$A $$A.pdf ; done ;
	xml2doc -oM manpage.xml manpage.man               ;
	gzip manpage.man                                  ;
	@printf "\e[32mDONE\e[0m\n"
	
mrproper: clean
	rm -f Makefile
clean:
	@printf "\e[32mCleaning documentation...\e[0m\n"
	rm -f *.pdf *.man *.html *.txt

install: build
	@printf "\e[32mInstalling documentation...\e[0m\n"
	@mkdir -p $(PREFIX)/share/man/man1
	cp -f manpage.man.gz $(PREFIX)/share/man/man1/xml2doc.1.gz
	gzip -f $(PREFIX)/share/man/man1/xml2doc.1
	@mkdir -p $(PREFIX)/share/doc/xml2doc
	for A in $(DOCS); do cp -f $$A $(PREFIX)/share/doc/xml2doc/ ;done

remove:
	@printf "\e[32mDeinstalling documentation...\e[0m\n"
	rm -rf $(PREFIX)/share/doc/xml2doc/
