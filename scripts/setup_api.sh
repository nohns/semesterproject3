#!/bin/bash
echo "Copying embedded api service unit into systemd..."
cp resources/embedded-api.service /etc/systemd/system/
chmod 755 /etc/systemd/system/embedded-api.service

echo "Enabling and starting embedded api service..."
systemctl daemon-reload
systemctl enable embedded-api.service
systemctl start embedded-api.service