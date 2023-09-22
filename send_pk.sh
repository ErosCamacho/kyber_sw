#!/bin/bash
echo "Enviando pk ... "
read -p "IP: " IP

if [[ $IP == "192.168.2.101" ]] 
then 
	name="eros"
	dir="/home/eros/Share/kyber_SW/pub_keys"
else
	name="xilinx"
	dir="/home/xilinx/kyber_SW/pub_keys"
fi

scp gen_keys/pk.bin $name@$IP:$dir

echo "Completado ... "

