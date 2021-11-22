FROM 'php:7.4-apache'

RUN apt update \
    && apt install -y git libonig-dev libzip-dev unzip \
    && docker-php-ext-install pdo_mysql \
    && docker-php-ext-install mbstring zip bcmath \
    && pecl install xdebug \
    && docker-php-ext-enable xdebug

COPY ./ini/php.ini /usr/local/etc/php/php.ini
COPY ./ini/xdebug.ini /usr/local/etc/php/conf.d/xdebug.ini