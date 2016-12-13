mkdir output
cd src
find . -name "*.eps" -exec epstopdf '{}' \;
pdflatex -output-directory ../output book.tex
cd ..
cp output/book.pdf build/book.pdf
