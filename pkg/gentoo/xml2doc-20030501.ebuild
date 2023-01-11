# Copyright 1999-2003 Gentoo Technologies, Inc.
# Distributed under the terms of the GNU General Public License v2
# $Header: $

DESCRIPTION="xml2doc is a simple xml processor that outputs pdf,html,txt,manpage,abiword..files"

HOMEPAGE="http://xml2doc.sf.net"
SRC_URI="http://xml2doc.sourceforge.net/src/${P}.tgz"
LICENSE="GPL-2"
SLOT="0"
KEYWORDS="x86"
IUSE="pdflib"

DEPEND=">=dev-libs/libxml2-2.5.1
		pdflib? >=media-libs/pdflib-4.0.3"

RDEPEND=""

S=${WORKDIR}/${PN}

src_compile() {
	
	if use pdflib
	then
		econf --disable-pdf || die
	else
		econf || die	
	fi
	emake || die

}

src_install() {
	
	dobin ${S}/src/xml2doc || die
	dodoc README TODO BUGS ${S}/doc/TAGS.xml*
	#xml2doc uses itself to create the manpage :-)
	${S}/src/xml2doc -oM ${S}/doc/manpage.xml xml2doc.1
	doman xml2doc.1
	docinto	examples
	dodir /usr/share/doc/${PF}/examples
	mv ${S}/examples/* ${D}/usr/share/doc/${PF}/examples
	rm ${D}/usr/share/doc/${PF}/examples/Makefile*

}

