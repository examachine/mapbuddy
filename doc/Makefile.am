

docdir = $(pkgdatadir)/doc

doc_DATA = mapbuddy.ps

mapbuddy.dvi:
	latex $(srcdir)/mapbuddy.tex 

mapbuddy.ps: mapbuddy.dvi
	dvips mapbuddy.dvi -o mapbuddy.ps

clean-local:
	-rm -f *.dvi *~

distclean-local:
	-rm -f *.dvi *.aux *.bbl *.blg *.lo* *.toc 
	-rm -rf auto
