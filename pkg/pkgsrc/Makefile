# $NetBSD$
#

DISTNAME=	xml2doc-20030510
WRKSRC=		${WRKDIR}/xml2doc
CATEGORIES=	textproc
MASTER_SITES=	http://xml2doc.sourceforge.net/src/
EXTRACT_SUFX=	.tgz

MAINTAINER=	pancake@phreaker.net
HOMEPAGE=	http://xml2doc.sourceforge.net/src/
COMMENT=	XML to document formats converter

USE_BUILDLINK2=		yes
USE_PKGLOCALEDIR=	yes
GNU_CONFIGURE=		yes
CONFIGURE_ENV+=		CFLAGS="-I${PREFIX}/include"
CONFIGURE_ENV+=		LDFLAGS="-L${PREFIX}/lib"
CFLAGS+=		-I${PREFIX}/include
USE_GMAKE=		yes

.include 	"../../mk/bsd.prefs.mk"
BUILD_DEFS+=		XML2DOC_USE_PDF

.if !defined(XML2DOC_USE_PDF) || ${XML2DOC_USE_PDF} != YES
CONFIGURE_ARGS+=	--disable-pdf
.else
.include "../../print/pdflib/buildlink2.mk"
.endif

MANCOMPRESSED=		xml2doc.1.gz

.include "../../textproc/libxml2/buildlink2.mk"
.include "../../mk/bsd.pkg.mk"
