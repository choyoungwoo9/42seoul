#!/bin/bash

var=$(uname -a)
printf "#Architecture : ${var}\n"
var=$(cat /proc/cpuinfo | grep "physical id" | sort -u | wc -l)
printf "#CPU Physical : ${var}\n"
var=$(cat /proc/cpuinfo | grep "processor" | sort -u | wc -l)
printf "#vCPU : ${var}\n"
free --mega | grep Mem | awk '{printf"#Memory Usage: %d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}'
var=$(df -BM | grep LVM | awk '{sum+=$3}END{print sum}' | tr -d '\n')
var2=$(df -BG | grep LVM | awk '{sum+=$2}END{print sum}' | tr -d '\n')
var3=$(df -BM | grep LVM | awk '{sum1+=$3 ; sum2+=$2}END{printf "%d", sum1 / sum2 * 100}' | tr -d '\n')
printf "#Disk Usage: ${var}/${var2} (${var3}%%)\n"
var=$(mpstat | tail -1 | awk '{print 100 - $NF}' | tr -d '\n')
printf "#CPU load: ${var}\n"
var=$(who -b | awk '{printf"%s %s", $3, $4}')
printf "#Last boot: ${var}\n"
var=$(lsblk | grep 'lvm' | wc -l | awk '{if($1>0)print"yes";else print"no"}')
printf "#LVM use: ${var}\n"
var=$(ss -t | grep ESTAB | wc -l)
printf "#Connections TCP : ${var}\n"
var=$(who | wc -l)
printf "#User log: ${var}\n"
var=$(ip link | grep link/ether | awk '{print"("$2")"}')
printf "#Network: ${var}\n"
var=$(ls /var/log/sudo/*/* | wc -l)
printf "#Sudo : ${var}\n"