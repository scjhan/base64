# Base64 encode and decode

## Build libbase64
```shell
mkdir lib
cd ./src/base
g++ -std=c++11 -c base64.cc
ar cr libbase64.a base64.o
```
That will create a static lib "`libbase64`" at `lib/`

## Build base64 test
```shell
mkdir bin
cd ./src
g++ -std=c++11 -I./ -L../lib -o main main.cc testor.cc -lbase64.a
```
That will create a execute file `main` at `bin/`

## Run base64 test
```shell
cd ./bin
./main
```
Simple output like this:
```shell
base64::Decode(SGVsbG8gV29ybGQ=) : Hello World
base64::Decode(Q2hlbkp1bmhhbg==) : ChenJunhan
base64::Decode(TmV0ZWFzZQ==) : Netease
base64::Encode(Hello World) : SGVsbG8gV29ybGQ=
base64::Encode(ChenJunhan) : Q2hlbkp1bmhhbg==
base64::Encode(Netease) : TmV0ZWFzZQ==
```
