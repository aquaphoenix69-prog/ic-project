$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build build
exit $LASTEXITCODE
