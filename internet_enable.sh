####
# this script alone can  
####

sudo /sbin/route add default gw 192.168.7.1
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
ping google.com

####
# compile with cmd : chmod +x  internet_enable.sh  
###


