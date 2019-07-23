#!/bin/sh
#读取数据
sed '/^#/d' config.xml | sort > config.store
tr [,:\(\)] [' '' '' '' '] < config.store > config.store1
rm -f config.store
wc -l config.store1 | tr [config.store1] ["             "] > node_num
g++ GPSR.cc -l curses -o GPSR
./GPSR
rm -f GPSR config.store1 node_num

