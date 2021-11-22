FROM 'php:7.4-apache'

# COPY --from=composer /usr/bin/composer /usr/bin/composer

RUN apt update \
    && apt install -y git \
    && docker-php-ext-install pdo_mysql
    # && composer require michelf/php-markdown

# ここいらない？
# RUN apt update \
#     && apt install -y npm \
#     && npm install -y marked

# RUN apt update
# RUN apt-get update \
    # && apt-get install -y \
    # git \
    # zip \
    # unzip \
    # vim \
    # libpng-dev \
    # libpq-dev \
    # && docker-php-ext-install pdo_mysql
# RUN apt install -y php-pdo php-mysql
# RUN set -ex apk --no-cache add postgresql-dev libpq-dev
# RUN apt-get install -y vim htop libpq-dev libonig-dev
# RUN docker-php-ext-install mbstring pdo_mysql opcache

# COPY ./conf/httpd.conf /usr/local/apache2/conf/
# COPY ./conf/php.ini /usr/local/etc/php/