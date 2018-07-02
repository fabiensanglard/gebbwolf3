if [ ! -d output ]
then
   mkdir output
fi
cd src

epsToPDF () {	
    # Build path without extension.
	filename=$(basename "$1")
    extension="${filename##*.}"
    filename="${filename%.*}"
	dir=$(dirname $1)

	extensionless=$dir/$filename

  # -nt = newer than. -ot = older than.
	if [ "$extensionless".eps -nt "$extensionless".pdf ]; then
		echo "Convert $extensionless.eps to PDF."
    epstopdf "$extensionless".eps
  fi
  # epstopdf $filename
}

# Convert eps to pdf if necessary
find . -name "*.eps" | while read file; do epsToPDF "$file"; done
# find . -name "*.eps" -exec epstopdf '{}' \;


pdflatex -output-directory ../output book.tex
cd ..
if [ ! -d build ]
then
   mkdir build
fi
cp output/book.pdf build/book.pdf
