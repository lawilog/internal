iptables -F
iptables -P INPUT DROP
iptables -P OUTPUT ACCEPT
iptables -P FORWARD DROP

# accept pruely local connections
iptables -A INPUT -i lo -j ACCEPT
iptables -A OUTPUT -o lo -j ACCEPT

# accept already established connections (in and out)
iptables -A INPUT -i eth0 -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A OUTPUT -o eth0 -m state --state RELATED,ESTABLISHED -j ACCEPT

# accept ssh from everywhere
iptables -A INPUT -p tcp --dport ssh -j ACCEPT

# accept incoming OpenVPN from everywhere
#iptables -A INPUT -p udp --dport 1194 -j ACCEPT

# allow 192.168.*.* and 10.6.*.* to access all services
#iptables -A INPUT -s 192.168.0.0/16 -j ACCEPT
iptables -A INPUT -s 192.168.66.0/29 -j ACCEPT
iptables -A INPUT -s 10.6.0.0/16 -j ACCEPT

# accept TCP rpcbind, nfs, vnc, X11 from 192.168.*.*
#for port in 111 2049 5901:5904 6001:6004
#do
#	iptables -A INPUT -s 192.168.0.0/16 -p tcp --dport $port -j ACCEPT
#done

# accept UDP nfs
#iptables -A INPUT -s 192.168.0.0/16 -p udp --dport 2049 -j ACCEPT

# log
# dont log:
iptables -A INPUT -p tcp --dport 135:139 -j DROP
iptables -A INPUT -p tcp --dport 445 -j DROP
#multicast:
iptables -A INPUT -d 224.0.0.0/4 -j DROP
# send other stuff to syslog
iptables -A INPUT -j LOG --log-level 6 --log-prefix "FIREWALL:input "
iptables -A FORWARD -j LOG --log-level 6 --log-prefix "FIREWALL:forward "
# iptables -A OUTPUT -j LOG --log-level 6 --log-prefix "FIREWALL:output "

# output
# iptables -L -v
