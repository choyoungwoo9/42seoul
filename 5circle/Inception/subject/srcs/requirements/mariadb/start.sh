# #!/bin/bash
# set -e

# mkdir -p /run/mysqld/
# chown -R mysql:mysql /run/mysqld/

# MySQL 서버를 안전하게 시작
mysqld_safe --skip-networking &

echo "Here! 1"

# MySQL이 시작될 때까지 기다림
until mysqladmin ping; do
  sleep 1
done

echo "Here! 2"

# 루트 비밀번호 설정 및 사용자/데이터베이스 생성
mysql -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${MYSQL_ROOT_PASSWORD}');"
mysql -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};"
mysql -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
mysql -e "GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';"
mysql -e "FLUSH PRIVILEGES;"

echo "Here! 3"

# MySQL 서버 종료
mysqladmin shutdown

echo "Here! 4"

# MySQL 서버를 포그라운드에서 실행
exec mysqld

# mysqld_safe &
# mysql_pid=$!

# until mysqladmin ping; do
#     echo 'Waiting for MariaDB to become available...'
#     sleep 1
# done
# echo 'MariaDB is available'

# mysql -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
# mysql -e "SELECT 1 FROM mysql.user WHERE user = '${MYSQL_USER}' AND host = '%'" | grep -q 1 || \
# mysql -e "CREATE USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
# mysql -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%'; FLUSH PRIVILEGES;"
# mysql -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${ROOT_PASSWORD}');"

# wait $mysql_pid
# exec "$@"

# #!/bin/bash
# set -e

# # MySQL/MariaDB를 백그라운드에서 시작
# mysqld_safe &
# mysql_pid=$!

# # MySQL/MariaDB가 시작될 때까지 기다림
# until mysqladmin ping >/dev/null 2>&1; do
#     echo 'Waiting for MariaDB to become available...'
#     sleep 1
# done
# echo 'MariaDB is available'

# # 초기 설정 스크립트 여기에 추가...
# ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD:-password}
# USER=${MYSQL_USER:-user}
# PASSWORD=${MYSQL_PASSWORD:-password}
# DATABASE=${MYSQL_DATABASE:-testdb}

# mysql -uroot -e "SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${ROOT_PASSWORD}');"
# mysql -uroot -p"${ROOT_PASSWORD}" -e "CREATE DATABASE IF NOT EXISTS ${DATABASE};"
# mysql -uroot -p"${ROOT_PASSWORD}" -e "GRANT ALL ON ${DATABASE}.* TO '${USER}'@'%' IDENTIFIED BY '${PASSWORD}'; FLUSH PRIVILEGES;"

# # MySQL/MariaDB 프로세스 종료 대기
# wait $mysql_pid
