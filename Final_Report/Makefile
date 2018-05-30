TARGET=PFPR_Group51
default: all
TEX=/usr/local/apps/tex_live/current/bin/x86_64-linux/latex
all: pdf

pdf: ps
	ps2pdf $(TARGET).ps

ps: dvi
	dvips $(TARGET).dvi

dvi: $(TARGET).tex
	$(TEX) $(TARGET).tex
	#uncomment below for bibliography to compile
	#bibtex $(TARGET)
	$(TEX) $(TARGET).tex
	$(TEX) $(TARGET).tex

clean:
	rm -f $(TARGET).aux
	rm -f $(TARGET).dvi
	rm -f $(TARGET).log
	rm -f $(TARGET).out
	rm -f $(TARGET).ps
	rm -f $(TARGET).bbl
	rm -f $(TARGET).blg
	rm -f $(TARGET).toc
