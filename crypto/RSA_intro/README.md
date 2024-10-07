# RSA_intro
`WHUCTF{Welc0me_2_th3_RSA_introduct1on!}`
## 题目描述
这是你的第一个RSA吗，给你p,q，尝试解决它吧，为了让这份介绍更加大众化，我使用了世界人民都能看懂的编码！

### 解题过程
- 解unicode编码得到p，q的十六进制值，还原其整数值
- 正常进行RSA解密

## 出题说明
本题旨在向新生介绍RSA加密算法的原理，但是直接给出pq显得太无脑

所以多给p,q套了一层unicode编码，希望新生能解


### 提示
unicode编码