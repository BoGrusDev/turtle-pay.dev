# Turtle Pay Live

* docker-compose up -d --build

* **Get Docker**
* docker ps
* Name: TPlivels
 
* **Copy**
* docker cp TP_prod_20220707.sql d284068a09dc:/var/TP_prod_20220707.sql

* **Create database TP_prod**

* **Terminal**
* docker exec -it d284068a09dc bash
* cd var
* mysql -u root -p TP_prod < TP_prod_20220707.sql (password)

* docker cp a06681000573:/usr/local/etc/php/php.ini php.ini

docker cp TP_prod_20220707.sql d284068a09dc:/var/TP_prod_20220707.sql
# turtle-pay.dev
# turtle-pay.dev
