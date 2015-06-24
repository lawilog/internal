#!/bin/bash
(echo "I am $(whoami). PATH=$PATH"; /root/bin/hddstatus.sh 2>&1) | mailx -s "HDD Status" architect
