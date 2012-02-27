#!/bin/bash
mail_from="lars.winterfeld@tu-ilmenau.de"
mail_server="smail.tu-ilmenau.de"
mail_user="lawi9838"

read -p "To: " mail_to
read -p "Subject: " mail_subject
mail_msg_file="`tempfile`"
nano "$mail_msg_file"
echo "I will send the following message:"
echo "From: $mail_from"
echo "To: $mail_to"
echo "Subject: $mail_subject"
cat "$mail_msg_file"
echo "-------------------------------"
echo "If you want to sent it now, then enter the password for $mail_user on $mail_server or just hit enter, if you do not want to send it."
mail_pass=""
suc=0
while [ $suc -eq 0 ]
do
	read -s -p "Password: " mail_pass
	echo
	if [ -z "$mail_pass" ]
	then
		echo "Your message is still stored in $mail_msg_file"
		break
	else
		sendEmail \
		-f "$mail_from" \
		-s "$mail_server" -o username="$mail_user" -o password="$mail_pass" \
		-t "$mail_to" \
		-u "$mail_subject" \
		-o message-file="$mail_msg_file" && suc=1 || suc=0
	fi
done
test -z "$mail_pass" || rm "$mail_msg_file"
