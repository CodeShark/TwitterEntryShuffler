#!/bin/bash
set -o xtrace
c++ -std=c++11 -stdlib=libc++ -l ssl -l crypto ShuffleEntries.cpp -o ShuffleEntries
