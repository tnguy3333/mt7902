sudo dmesg -c
sudo rmmod mt7902e
sudo rmmod mt792x-lib
sudo rmmod mt76-connac-lib
sudo rmmod mt76

make clean
make

sudo modprobe mac80211
sudo insmod mt76.ko
sudo insmod mt76-connac-lib.ko
sudo insmod mt792x-lib.ko
sudo insmod mt7902/mt7902e.ko