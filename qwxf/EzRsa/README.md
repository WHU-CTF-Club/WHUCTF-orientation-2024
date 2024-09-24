# EzHv
## Description
某公司使用RSA2048加密算法来进行一些校验，但是经过我们的安全员审计发现，他们的这份代码中忘记剔除了一些敏感信息！

## Hint
有一些程序中没有用到的函数的数据可能可以被我们利用。

## Platform
`Linux`

## File
`ezrsa`

## Flag
`WHUCTF{545B76DB-DD8E-8740-74C9-F06DA947188D}`

## Info
2048位RSA，结构体中同时保留了私钥的内容和解密函数，可以直接patch调用解密得到答案。