#!/bin/bash

mem_usage_kb=$1
is_loopcount_based=$2
timeout=$3

#for core in {0..47}; do
#for core in `seq 0 2 95`; do
#for core in {0..95}; do
#for core in {0..35}; do
#    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#    ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#done
#for core in {0..95}; do
#    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#done

#./mat_mult $mem_usage_kb $is_loopcount_based $timeout &



#for core in {0..23}; do
#    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#done
#for core in {24..47}; do
#    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
#done


for core in {0..47}; do
    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
    taskset -c $core ./mat_mult $mem_usage_kb $is_loopcount_based $timeout &
done


wait
