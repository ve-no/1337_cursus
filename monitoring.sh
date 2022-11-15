arch=$(uname -a)
pCPU=$(lscpu | awk '$1 == "CPU(s):" {print $2}')
vCPU=$(grep -c "processor" /proc/cpuinfo)
#  free - Display amount of free and used memory in the system
# -m: Display the amount of memory in mebibytes.
usage_m=$(free -m | awk '$1 == "Mem:" {printf("%d", $3)}')
total_m=$(free -m | awk '$1 == "Mem:" {printf("%dMB", $2)}')
porc_m=$(free -m | awk '$1 == "Mem:" {printf("(%.2f%%)", ($3 * 100) / $2)}')
# df -- display free disk space
# -h: "Human-readable" output.
Disk_Usage=$(df --total -h | awk '$1 == "total" {printf("%d/%dGb (%.2f%%)", $3 * 1024, $2, ($3 * 100) / $2)}')
# The current utilization rate of the processors
CPU_load=$(top -n 1 -b | grep load | awk '{print $11}' | tr -d ',')
# The date and time of the last reboot
# -b    Time of last system boot.
last_boot=$(who -b | awk '{print $3" "$4}')
# Whether LVM is active or not:
# lsblk - list block devices
LVM_use=$(lsblk | grep lvm | wc -l | awk '{if ($0 != 0) {print "yes"} else {print "no"}}')
# The number of active connections
con_TCP=$(ss -s | grep estab | awk '{print $4}' | tr -d ',')
# The number of users using the server
#  users - print the user names of users currently logged in to the current host
user_log=$(users | wc -w)
ip=$(hostname -I)
# ip - show / manipulate routing, network devices, interfaces and tunnels
# link   - network device.
mac=$(ip link | grep "link/ether" | awk '{print $2}')
sudo_cmd=$(grep "COMMAND" /var/log/sudo/sudo.log | wc -l)

wall    "#Architecture: $arch
    #CPU physical : $pCPU
    #vCPU : $vCPU
    #Memory Usage: $usage_m/$total_m $porc_m
    #Disk Usage: $Disk_Usage
    #CPU load: $(printf $CPU_load)%
    #Last boot: $last_boot
    #LVM use: $LVM_use
    #Connections TCP : $con_TCP ESTABLISHED
    #User log: $user_log
    #Network: IP $ip($mac)
    #Sudo : $sudo_cmd cmd"
