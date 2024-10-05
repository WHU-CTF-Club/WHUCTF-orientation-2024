# 使用 Node.js 官方镜像作为基础镜像
FROM node:18

# 创建工作目录
WORKDIR /usr/src/app

# 复制 package.json 和 package-lock.json 文件到工作目录
COPY ./package*.json ./

# 安装项目依赖
RUN npm i

# 复制服务器代码到工作目录
COPY . .

# 暴露端口 3000
EXPOSE 3000

# 启动服务器
CMD ["node", "server.js"]
