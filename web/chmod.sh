#!/bin/sh

echo "change mod"
chmod 777 -R /var/www
echo "change own"
chown -R www-data:www-data /var/www 
