mkdir doc
doxygen
#"C:\Program Files\HTML Help Workshop\hhc.exe" api_doc\index.hhp
copy api_doc\api_doc.chm doc
rmdir /Q/S api_doc