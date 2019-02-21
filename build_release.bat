cmake -Bbuild/release -H. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="C:\\LibErrorInterceptor" -DCMAKE_GENERATOR_PLATFORM=x64
cd %cd%/build/release
cmake --build . --config Release
cd %~dp0
