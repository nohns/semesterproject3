#!/bin/bash
echo "Installing mdns-publisher..."
pip install mdns-publisher

echo "Copying hostname publish script to /home/pi/scripts/..."
mkdir -p /home/pi/scripts/
chown -R pi:pi /home/pi/scripts/
cp resources/publish_mdns_cnames.py /home/pi/scripts/
chmod +x /home/pi/scripts/publish_mdns_cnames.py
chown pi:pi /home/pi/scripts/publish_mdns_cnames.py

echo "Installing hostname publish service to /etc/systemd/system/..."
cp resources/avahi-mdns-cname.service /etc/systemd/system/
chmod 755 /etc/systemd/system/avahi-mdns-cname.service
chown root:root /etc/systemd/system/avahi-mdns-cname.service

echo "Enabling and starting hostname publish service..."
systemctl daemon-reload
systemctl enable avahi-mdns-cname.service
systemctl start avahi-mdns-cname.service

