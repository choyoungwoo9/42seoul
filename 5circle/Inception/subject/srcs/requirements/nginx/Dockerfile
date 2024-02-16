# syntax=docker/dockerfile:1
FROM debian:bullseye

RUN apt-get update
RUN apt-get install nginx -y

RUN apt-get install openssl -y
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout nginx-selfsigned.key \
    -out nginx-selfsigned.crt \
    -subj "/C=KR/ST=Seoul/L=Seoul/O=42/OU=IT Department/CN=."

COPY start.sh /start.sh

RUN chmod +x /start.sh

ENTRYPOINT ["/start.sh"]
CMD ["nginx", "-g", "daemon off;"]