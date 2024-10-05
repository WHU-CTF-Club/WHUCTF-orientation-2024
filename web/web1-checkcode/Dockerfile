FROM node:lts-alpine3.15

WORKDIR /usr/src/app

COPY ./app ./

RUN npm  install

EXPOSE 80

CMD ["./start.sh"]
