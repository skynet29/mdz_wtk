del *.obj
rmdir /S/Q lib
call "C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Vc7\bin\VCVARS32.BAT"
cl -c -DDLLMDZ *.cpp 
cl -c *.c
mkdir lib
link /DLL /OUT:lib\mdz_wtk.dll *.obj kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib htmlhelp.lib comctl32.lib wsock32.lib vfw32.lib winmm.lib
del *.obj

rmdir /Q/S include
mkdir include
copy mdz_wtk.h include
cd include
for /F "tokens=2" %%i IN (mdz_wtk.h) do copy ..\%%i .
cd..

#mkdir doc
#doxygen
#"C:\Program Files\HTML Help Workshop\hhc.exe" api_doc\index.hhp
#copy api_doc\api_doc.chm doc
#rmdir /Q/S api_doc