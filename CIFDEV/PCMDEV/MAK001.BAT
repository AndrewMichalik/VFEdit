cd %1
del object\*.obj
nmake >>..\err.txt
cd ..
