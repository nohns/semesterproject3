#!/bin/bash
echo "Running Raspberry Pi initialization script..."
apt update
apt upgrade -y
apt install -y ca-certificates curl gnupg 

echo "--> Installing python dependencies..."
rm -rf /usr/lib/python3.11/EXTERNALLY-MANAGED
pip install flask flask-cors pyroute2
echo "------------------------"

# Install nodejs
echo "--> Installing nodejs..."
curl -fsSL https://deb.nodesource.com/gpgkey/nodesource-repo.gpg.key | sudo gpg --dearmor -o /usr/share/keyrings/nodesource.gpg
NODE_MAJOR=20
echo "deb [signed-by=/usr/share/keyrings/nodesource.gpg] https://deb.nodesource.com/node_$NODE_MAJOR.x nodistro main" | sudo tee /etc/apt/sources.list.d/nodesource.list
apt update
apt install -y nodejs build-essential
echo "------------------------"

# Installing nginx
echo "--> Installing nginx..."
apt install -y nginx
systemctl enable nginx
systemctl start nginx
echo "-----------------------"

# Setup hostnames
echo "--> Setting up DNS hostnames touch.pi.local and config.pi.local..."
sh ./setup_hostnames.sh
echo "-----------------------"

echo "--> Setting up nginx hosts for touch.pi.local and config.pi.local domains..."
sh ./setup_nginx.sh
echo "-----------------------"

# Source linux kernel
echo "--> Sourcing linux kernel..."
sed -i '/^#\sdeb-src /s/^#//' "/etc/apt/sources.list"
apt update
apt source linux
echo "-----------------------"

echo "NOTICE: you are not done yet! You need to run deploy the frontend by running 'npm run deploy' from source/frontend/touch and source/frontend/configuration directories."
