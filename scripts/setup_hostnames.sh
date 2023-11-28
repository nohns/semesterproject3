#!/bin/bash
echo "Installing mdns-publisher..."
rm -rf /usr/lib/python3.11/EXTERNALLY-MANAGED
apt install libdbus-glib-1-dev libgirepository1.0-dev
pip install mdns-publisher

echo "Copying hostname publish script + resources to /home/pi/scripts/..."
mkdir -p /home/pi/scripts/
chown -R pi:pi /home/pi/scripts/
cp resources/publish_mdns_cnames.py /home/pi/scripts/
cp resources/.mdns-aliases /home/pi/
chmod +x /home/pi/scripts/publish_mdns_cnames.py
chown pi:pi /home/pi/scripts/publish_mdns_cnames.py
chown pi:pi /home/pi/.mdns-aliases

echo "Installing hostname publish service to /etc/systemd/system/..."
cp resources/avahi-mdns-cname.service /etc/systemd/system/
chmod 755 /etc/systemd/system/avahi-mdns-cname.service
chown root:root /etc/systemd/system/avahi-mdns-cname.service

echo "Enabling and starting hostname publish service..."
systemctl daemon-reload
systemctl enable avahi-mdns-cname.service
systemctl start avahi-mdns-cname.service

echo "Adding hostnames to /etc/hosts..."
echo "127.0.0.1       touch.pi.local" | sudo tee -a /etc/hosts
echo "127.0.0.1       config.pi.local" | sudo tee -a /etc/hosts