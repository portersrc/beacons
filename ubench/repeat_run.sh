#!/bin/bash

for mem_usage_kb in `seq 50 50 1000`; do
    #{ time ./run.sh $mem_usage_kb 1 10 ; } &> result_$mem_usage_kb.txt
    #{ time ./run.sh $mem_usage_kb 1 1000 ; } &> result_$mem_usage_kb.txt
    ./run.sh $mem_usage_kb 0 60 &> result_$mem_usage_kb.txt
done
