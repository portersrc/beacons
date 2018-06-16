#!/bin/bash

mem_usage_kb=$1
timeout=$2

for core in {0..47}; do
    taskset -c $core ./mat_mult $mem_usage_kb $timeout &
done

wait
