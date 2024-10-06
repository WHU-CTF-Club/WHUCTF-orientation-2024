# 雪花牛肉
`WHUCTF{Sn0wfl@ke_Bee4_1s_D3lic1ous}`
## 题目描述
这CTF啊我有四不做：WEB不做、密码不做、逆向不做、PWN不做...

### 解题过程
1. 从图片中分离出压缩包
2. 发现snow隐写，使用beef作为密码
3. 执行`.\snow.exe -C -p beef .\flag.txt` 得到flag

## 出题说明
题目中多次提到雪花牛肉，其实是以beef为密码的snow隐写

工具在 https://darkside.com.au/snow/

### 提示
空白字符隐写