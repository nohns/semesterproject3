#!/bin/bash
echo "Running Raspberry Pi initialization script..."
apt update
apt upgrade -y
apt install -y ca-certificates curl gnupg python3-flask python3-flask-cors python3-pyroute2

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

echo "--> Adding nginx touchscreen and config vhosts..."
cp resources/nginx/touch.pi.local /etc/nginx/sites-available/
cp resources/nginx/config.pi.local /etc/nginx/sites-available/
ln -s /etc/nginx/sites-available/touch.pi.local /etc/nginx/sites-enabled/
ln -s /etc/nginx/sites-available/config.pi.local /etc/nginx/sites-enabled/
systemctl reload nginx
echo "-----------------------"

# Setup hostnames
echo "--> Setting up touch.pi.local and config.pi.local hostnames..."
sh ./setup_hostnames.sh
echo "-----------------------"

echo "NOTICE: you are not done yet! You need to run deploy the frontend by running 'npm run deploy' from source/frontend/touch and source/frontend/configuration directories."