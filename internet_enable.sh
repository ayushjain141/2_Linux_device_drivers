########################################################################################
# This script alone can enable the connection to internet in Beagle Bone Black.
# ( Tested only for internet over USB )
#
# Usage -
#        1. Place the script in the root directory.
#        2. Run with cmd : chmod +x  internet_enable.sh
########################################################################################

sudo /sbin/route add default gw 192.168.7.1
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
ping google.com
