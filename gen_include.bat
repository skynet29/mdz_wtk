rmdir /Q/S include
mkdir include
copy mdz_wtk.h include
cd include
for /F "tokens=2" %%i IN (mdz_wtk.h) do copy ..\%%i .
cd ..
#doxygen
#"C:\Program Files\HTML Help Workshop\hhc.exe" api_doc\index.hhp
#copy api_doc\api_doc.chm doc
#rmdir /Q /S api_doc
