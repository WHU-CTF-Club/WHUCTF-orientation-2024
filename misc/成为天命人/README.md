# 成为天命人
`WHUCTF{Are_u_the_Destined_One_in_BlackMyth:WuKong?}`
## 题目描述
从各种steam中找到付款码图片，再扫码购买，成为天命人！

flag格式：WHUCTF{天命人参透的佛语}

### 解题过程
- 密码样式在压缩包末尾，掩码攻击解开压缩包
- 遍历目录找到图片
- 先是[汉信码解密](https://tuzim.net/hxdecode/)得到佛曰和熊曰
- 然后[新佛曰熊曰](http://hi.pcmoe.net/index.html)解密得到flag

## 出题说明
扫码题，结合一下黑悟空的热度，刚好带一手佛曰熊曰加密

### 提示
还有什么其他二维码呢？