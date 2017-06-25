# GRUB_CMDLINE_LINUX_DEFAULT="quiet splash isolcpus=1,2,3 nohz_full=1,2,3 nosmep nosmap"

# Disable logical CPU pairs
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online

# Set IRQ affinity mask to CPU 0
cd /proc/irq/
echo 1 | tee */smp_affinity

# Set CPU frequency scaling to performance mode for all cpus
cd /sys/devices/system/cpu/

sudo cpupower frequency-set -f 2600000

# echo performance | tee cpu*/cpufreq/scaling_governor
# echo 1900000 | tee cpu*/cpufreq/scaling_max_freq
# echo 1800000 | tee cpu*/cpufreq/scaling_min_freq





