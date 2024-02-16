# syntax=docker/dockerfile:1
FROM debian:bullseye

RUN apt-get update && \
	apt-get install mariadb-server -y

COPY conf/mysql.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

COPY start.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/start.sh

ENTRYPOINT ["start.sh"]
# CMD ["mysqld"]