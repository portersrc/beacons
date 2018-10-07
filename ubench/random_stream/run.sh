#!/bin/bash
set -x

./random_stream_one 10000000:50000000
./random_stream_two 200:500
