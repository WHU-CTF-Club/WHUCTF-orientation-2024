# Winding_AES
`WHUCTF{The_Tail_Destroyed_MyAES}`
## 题目描述
CTF新生赛偶遇AES加密，反复异或加密强如怪物，拼尽全力无法战胜...

### 解题过程
- 乍一看密钥和密钥都每给全可能比较唬人，但其实给出了尾部信息是可以往前爆破的
- 用一个滑动窗口去理解，关键就在于每次就移了一位，那么hint的低15位此轮密文异或当前窗口的低15位
- 从而验证每一位爆破的正确性，利用窗口的不断左移向前恢复密文和密钥
- 到了最高位，需要单独爆破，同时利用前面不断恢复的第一个密钥还原初始的密钥
- 用初始的密钥解遍历高位的密文，根据有无flag头来判断爆破的正确与否

## 出题说明
必要的分组加密考点，和异或结合了一下反而降低了难度

感觉构造得比较~~粪~~，也算能写吧
### 提示
xor(key, c1)似乎和hint很像