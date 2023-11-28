echo "Copying nginx touchscreen and config hosts..."
cp resources/nginx/touch.pi.local /etc/nginx/sites-available/
cp resources/nginx/config.pi.local /etc/nginx/sites-available/

echo "Enable nginx touchscreen and config hosts..."
ln -s /etc/nginx/sites-available/touch.pi.local /etc/nginx/sites-enabled/
ln -s /etc/nginx/sites-available/config.pi.local /etc/nginx/sites-enabled/

echo "Reloading nginx..."
systemctl reload nginx

echo "Done setting up nginx hosts!"