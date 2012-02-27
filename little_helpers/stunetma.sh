#!/bin/bash

# stupid network manager, by Lars Winterfeld

# these files will be symbolically linked according to the profile, like /etc/conf.d/net -> net.at_work
FILE_NUM=2
FILE_0="/etc/conf.d/net"
FILE_1="/etc/resolv.conf"

# each profile contains the following information
# NAME: if the name is e.g. "at_work", the files /etc/conf.d/net.at_work and /etc/resolv.conf.at_work must exist
# INTERFACE: the network interface to be restarted or stopped
# PRE_TEST: if this command does not exit successfully, the profile is not tried. may be empty
# POST_TEST: after setting the profile, this is tested. the exit status decides, if
#            SUCCESS is executed and no other profiles are tried or
#            FAILURE is executed and the next profile is tried
# SUCCESS_CMD: if the POST_TEST successes, this command is run. may be empty
# SUCCESS_CMD: if the POST_TEST successes, these services are started. may be empty
# FAILURE_CMD: if the POST_TEST fails, this command is run. may be empty
# FAILURE_CMD: if the POST_TEST fails, these services are started. may be empty

# the number of profiles
PROFILE_NUM=5

PROFILE_0_NAME="poststr"
PROFILE_0_INTERFACE="eth0"
PROFILE_0_PRE_TEST=""
PROFILE_0_POST_TEST="ping -c1 -w1 manifest"
PROFILE_0_SUCCESS_CMD=""
PROFILE_0_SUCCESS_SERVICES="cupsd netmount ntp-client sshd"
PROFILE_0_FAILURE_CMD=""
PROFILE_0_FAILURE_SERVICES=""

PROFILE_1_NAME="uniwlan"
PROFILE_1_INTERFACE="wlan0"
PROFILE_1_PRE_TEST="ifconfig $PROFILE_1_INTERFACE up && iwlist $PROFILE_1_INTERFACE scan | grep TU-WLAN"
PROFILE_1_POST_TEST="ping -c1 -w1 nic.com"
PROFILE_1_SUCCESS_CMD=""
PROFILE_1_SUCCESS_SERVICES="ntp-client"
PROFILE_1_FAILURE_CMD="ifconfig $PROFILE_1_INTERFACE down"
PROFILE_1_FAILURE_SERVICES=""

PROFILE_2_NAME="wichtshausen_wlan"
PROFILE_2_INTERFACE="wlan0"
PROFILE_2_PRE_TEST="ifconfig $PROFILE_2_INTERFACE up && iwlist $PROFILE_1_INTERFACE scan | grep WLAN-CF2D13"
PROFILE_2_POST_TEST="ping -c1 -w1 nic.com"
PROFILE_2_SUCCESS_CMD=""
PROFILE_2_SUCCESS_SERVICES="ntp-client openvpn.manifest_remote netmount"
PROFILE_2_FAILURE_CMD="ifconfig $PROFILE_2_INTERFACE down"
PROFILE_2_FAILURE_SERVICES=""

PROFILE_3_NAME="wichtshausen_wired"
PROFILE_3_INTERFACE="eth0"
PROFILE_3_PRE_TEST=""
PROFILE_3_POST_TEST="ping -c1 -w1 nic.com"
PROFILE_3_SUCCESS_CMD=""
PROFILE_3_SUCCESS_SERVICES="ntp-client openvpn.manifest_remote netmount"
PROFILE_3_FAILURE_CMD=""
PROFILE_3_FAILURE_SERVICES=""

PROFILE_4_NAME="dhcp"
PROFILE_4_INTERFACE="eth0"
PROFILE_4_PRE_TEST=""
PROFILE_4_POST_TEST="ping -c1 -w1 nic.com"
PROFILE_4_SUCCESS_CMD=""
PROFILE_4_SUCCESS_SERVICES="ntp-client"
PROFILE_4_FAILURE_CMD=""
PROFILE_4_FAILURE_SERVICES=""

for (( p=0; p<$PROFILE_NUM; p++ ))
do
	NAME="PROFILE_${p}_NAME"
	NAME=${!NAME}
	INTERFACE="PROFILE_${p}_INTERFACE"
	INTERFACE=${!INTERFACE}
	PRE_TEST="PROFILE_${p}_PRE_TEST"
	PRE_TEST=${!PRE_TEST}
	POST_TEST="PROFILE_${p}_POST_TEST"
	POST_TEST=${!POST_TEST}
	SUCCESS_CMD="PROFILE_${p}_SUCCESS_CMD"
	SUCCESS_CMD=${!SUCCESS_CMD}
	SUCCESS_SERVICES="PROFILE_${p}_SUCCESS_SERVICES"
	SUCCESS_SERVICES=${!SUCCESS_SERVICES}
	FAILURE_CMD="PROFILE_${p}_FAILURE_CMD"
	FAILURE_CMD=${!FAILURE_CMD}
	FAILURE_SERVICES="PROFILE_${p}_FAILURE_SERVICES"
	FAILURE_SERVICES=${!FAILURE_SERVICES}
	
	# run pre-test
	if bash -c "$PRE_TEST"
	then
		echo "Testing profile \"$NAME\" on interface $INTERFACE"
		
		# configure files
		for (( f=0; f<$FILE_NUM; f++ ))
		do
			FILE="FILE_$f"
			FILE=${!FILE}
			ln -sf "${FILE}.${NAME}" "${FILE}"
		done
		
		# restart interface
		/etc/init.d/net.$INTERFACE restart
		
		# run post-test
		if bash -c "$POST_TEST"
		then
			# run SUCCESS commands
			bash -c "$SUCCESS_CMD"
			
			# start SUCCESS services
			for s in $SUCCESS_SERVICES
			do
				/etc/init.d/$s start
			done
			
			# no need to test more profiles
			break
		else
			# run FAILURE commands
			bash -c "$FAILURE_CMD"
			
			# start FAILURE services
			for s in $FAILURE_SERVICES
			do
				/etc/init.d/$s start
			done
			
			# stop interface
			/etc/init.d/net.$INTERFACE stop
		fi
	else
		echo "Not testing profile \"$NAME\" on interface $INTERFACE"
	fi
	
done
