FROM debian:bullseye-slim

ENV MYSQL_DATABASE exampledb
ENV MYSQL_USER exampleuser
ENV MYSQL_PASSWORD examplepass

RUN apt-get update && \
	apt-get install mariadb-server -y && \
	service mysql start && \
    mysql -e "GRANT ALL ON *.* TO '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" && \
    mysql -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};" && \
    mysql -e "FLUSH PRIVILEGES;"

CMD ["bash"]