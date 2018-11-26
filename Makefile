all:
	pdflatex -shell-escape tn.tex

clean:
	rm -rf _minted-tn tn.aux tn.fdb_latexmk tn.fls tn.log tn.pdf tn.toc
