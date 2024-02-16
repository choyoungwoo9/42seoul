#!/bin/bash

# rm -rf /var/www/html/* \

# if [ ! -f "/var/www/html/wp-config.php" ]; then
#     cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php
# fi

if [ ! -f "/var/www/html/wp-config.php" ]; then

cp -r /wordpress/* /var/www/html/ \
&& cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php \
&& sed -i "s/database_name_here/${MYSQL_DATABASE}/g" /var/www/html/wp-config.php \
&& sed -i "s/username_here/${MYSQL_USER}/g" /var/www/html/wp-config.php \
&& sed -i "s/password_here/${MYSQL_PASSWORD}/g" /var/www/html/wp-config.php \
&& sed -i "s/localhost/db/g" /var/www/html/wp-config.php \

fi

mkdir -p /run/php

exec "$@"
