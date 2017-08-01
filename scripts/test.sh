#!/bin/bash
# affiche_param.sh

cmd="pico2wave -l ";
lang=$1;
cmd1=" -w data/output.wav \"";
msg=$2;
cmd3="\"";			     

foo=$cmd$lang$cmd1$msg$cmd3
$foo;
