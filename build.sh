rm -rf modules
mkdir modules
g++ -std=c++11 module.cpp -shared -fPIC -o modules/module.so `pkg-config webkit2gtk-web-extension-4.0 --libs --cflags`
g++ -std=c++11 test.cpp `pkg-config gtkmm-3.0 --libs --cflags` `pkg-config webkit2gtk-4.0 --libs --cflags`
