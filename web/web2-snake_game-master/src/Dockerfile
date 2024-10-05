# 使用 nginx 作为基础镜像
FROM nginx:alpine

# 复制项目文件到 nginx 的默认目录
COPY . /usr/share/nginx/html

# 暴露端口 80
EXPOSE 80

# 启动 nginx
CMD ["nginx", "-g", "daemon off;"]
