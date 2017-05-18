# WIP

# FancyNas
A simple Nas system with info display


# PARTS
* pcduino v3
* 128x64 oled display
* arduino nano
* step up converter 5->12V
* 12V PC fan
* Relais/MOSFET
* DS... One Wire Temp Sensor

# CASE PLATES
* 2x 25x15x0.5 (black)
* 2x 15x10.5x0.5
* 2x 15.5x10.5x0.5

# PYTHON SETUP
* install python3 net-tools python3-serial psutils
* download the python folder
* chmod +x nas_disp_updater.py
* chmod +x auto_run.sh
* add the auto_run path to your /etc/rc.local

# CHANGE HOSTNAME
* /etc/hostname 
* /etc/hosts

# AUTO STANDBY HDD
* sudo apt-get install hdparm
* sudo hdparm -S 60 /dev/sda #for each hd
