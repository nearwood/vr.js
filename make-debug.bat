
ECHO TODO: gyp and msbuild

copy build\vs2012\Debug\npvr.dll build\npvr\Debug\
copy manifest.json build\npvr\Debug\
copy third_party\sixense\bin\win32\release_dll\sixense.dll build\npvr\Debug\

regsvr32 /s /u bin\npvr.dll
regsvr32 /s build\npvr\debug\npvr.dll

