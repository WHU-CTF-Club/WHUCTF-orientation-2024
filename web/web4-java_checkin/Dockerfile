FROM openjdk:8-slim-bullseye

# 安装必要的软件包
RUN sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list && \
    # apk add --update --no-cache tar apache mysql mysql-client bash
    apt update && \
    apt install -y curl iptables

# 拷贝程序和启动脚本至根目录
COPY ./src /app
COPY ./service/docker-entrypoint.sh /docker-entrypoint.sh

# 开放的端口取决于服务，默认 Demo 为8080
EXPOSE 8080

# 指定容器入口点
ENTRYPOINT [ "/bin/bash","/docker-entrypoint.sh" ]
