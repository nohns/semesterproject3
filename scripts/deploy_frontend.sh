#!/bin/bash
if [ -z "$1" ]; then
    echo "ERROR: No build directory specified! use 'touch' or 'configuration'"
    exit 1
fi

# Check that first argument is either 'touch' or 'configuration' 
if [ "$1" != "touch" ] && [ "$1" != "configuration" ]; then
    echo "ERROR: First argument must be either 'touch' or 'configuration'"
    exit 1
fi

# If 'touch' then define VHOST_DIR as 'touch.pi.local' and 'configuration' as 'config.pi.local'
if [ "$1" == "touch" ]; then
    VHOST_DIR="touch.pi.local"
elif [ "$1" == "configuration" ]; then
    VHOST_DIR="config.pi.local"
fi

echo "---> Building frontend..."
cd ../source/frontend/$1
npm i
npx vite build
echo "---------------------"

echo "---> Deploying frontend..."
mkdir -p /var/www/$VHOST_DIR/dist
cp -r dist/* /var/www/$VHOST_DIR/dist
chown -R pi:pi /var/www/$VHOST_DIR
echo "---------------------"