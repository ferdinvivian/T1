
#!/bin/bash
# Script: batch_docx_to_txt_pdf.sh
# Deletes old .txt/.pdf and creates new .txt + .pdf from all .txt.docx files

echo "=== Batch DOCX to TXT + PDF Converter ==="

# 1. Delete all existing .txt and .pdf files
echo "Cleaning old files..."
rm -f *.txt *.pdf

# 2. Find all .txt.docx files
shopt -s nullglob
FILES=(*.txt.docx)

if [ ${#FILES[@]} -eq 0 ]; then
  echo "No .txt.docx files found in this folder"
  exit 1
fi

echo "Found ${#FILES[@]} files to convert"
echo ""

# 3. Convert each file
for INPUT in "${FILES[@]}"; do
  BASE="$(basename "$INPUT" .txt.docx)"
  TXT_OUT="${BASE}.txt"
  PDF_OUT="${BASE}.pdf"
  
  echo "Processing: $INPUT"
  
  # Step 1: Create .txt version - clean text, good for code
  echo "  -> Creating $TXT_OUT"
  libreoffice --headless --convert-to txt:Text "$INPUT" --outdir . > /dev/null
  
  # Step 2: Create .pdf version - keeps alignment + screenshots
  echo "  -> Creating $PDF_OUT"
  libreoffice --headless --convert-to pdf:writer_pdf_Export "$INPUT" --outdir . > /dev/null
  
  # LibreOffice names it file.txt.docx.pdf so rename
  if [ -f "${INPUT}.pdf" ]; then
    mv "${INPUT}.pdf" "$PDF_OUT"
  fi
  
  echo "  Done!"
  echo ""
done

echo "=== All Done! ==="
ls -lh *.txt *.pdf 2>/dev/null

echo "=== Fixing filenames ==="
for f in *.txt.txt; do mv "$f" "${f%.txt.txt}.txt"; done
for f in *.txt.pdf; do mv "$f" "${f%.txt.pdf}.pdf"; done



echo "=== All Done! ==="
ls -lh *.txt *.pdf 2>/dev/null

