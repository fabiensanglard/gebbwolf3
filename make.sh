cd src
pdflatex -output-directory ../output book.tex
cd imgs
find . -name "*.eps" -exec epstopdf '{}' \;
cd ..
cd ..
cp output/book.pdf build/book.pdf
