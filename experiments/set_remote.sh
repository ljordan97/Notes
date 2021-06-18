#!/bin/bash

#This script allows the chargeCmd build to use your username and IP
#Author: Levi Jordan

echo "Enter username and IP like so: username@192.168.0.XX"
read LOGIN
exporter="export CHARGE_USER_AND_IP="
exporter+=${LOGIN}
echo ${exporter} >> ~/.bashrc
echo '~/.bashrc updated and re-sourced'
source ~/.bashrc
