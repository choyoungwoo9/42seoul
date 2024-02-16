# #!/bin/bash

mariadb-install-db --datadir=/var/lib/mysql
# mkdir -p /run/mysqld/
# chown -R mysql:mysql /run/mysqld/
# chown -R mysql:mysql /var/lib/mysql

mysqld_safe &

until mysqladmin ping; do
  sleep 1
done


# # # 루트 비밀번호 설정 및 사용자/데이터베이스 생성
# # # mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY 'password';"
# # # mysql -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${MYSQL_ROOT_PASSWORD}');"
mysql -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};"
mysql -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
mysql -e "GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';"
mysql -e "FLUSH PRIVILEGES;"

mysqladmin shutdown

exec mysqld

# while true :
# do
#     sleep 1
# done