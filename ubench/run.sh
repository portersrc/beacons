#!/bin/bash

mem_usage_kb=$1
is_loopcount_based=$2
timeout=$3

for core in {0..47}; do
    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
done

wait
