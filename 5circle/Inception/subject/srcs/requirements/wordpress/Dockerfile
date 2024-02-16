# syntax=docker/dockerfile:1
FROM debian:bullseye

RUN apt update && apt upgrade -y \
    && apt install vim php7.4-fpm php7.4-mysqli wget -y \
    && sed -i 's/listen = \/run\/php\/php7.4-fpm.sock/listen = 9000/' /etc/php/7.4/fpm/pool.d/www.conf \
    && wget https://wordpress.org/latest.tar.gz \
    && tar -xzvf latest.tar.gz \
    && mkdir -p /var/www/html \
    && rm -rf /var/www/html/* \
    && cp -r wordpress/* /var/www/html/ \
    && cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php

COPY ./start.sh /
RUN chmod +x /start.sh

ENTRYPOINT ["/start.sh"]


CMD ["php-fpm7.4", "-F"]
