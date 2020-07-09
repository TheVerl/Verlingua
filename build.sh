rm -rf bin/Verlingua-Build-*
python constructer/noUpdate.py
cd source
make all
cd ..
#rm -rf build/*.o
