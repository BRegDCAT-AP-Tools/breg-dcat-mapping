FROM php:5.6-apache

RUN a2enmod rewrite
RUN a2enmod ssl

# install the PHP extensions we need
RUN apt-get update && apt-get install -y libpng-dev libjpeg-dev libpq-dev mysql-client \
	&& rm -rf /var/lib/apt/lists/* \
	&& docker-php-ext-configure gd --with-png-dir=/usr --with-jpeg-dir=/usr \
	&& docker-php-ext-install gd mbstring pdo pdo_mysql pdo_pgsql zip mysqli

COPY . /var/www/html

RUN chown -R www-data:www-data .