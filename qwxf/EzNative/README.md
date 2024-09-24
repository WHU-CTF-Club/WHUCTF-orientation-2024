# EzNative
## Description
这里有一个exe程序，但是我无论如何都没办法通过双击鼠标运行它。并且它被VMP加固过了，这么短的时间内静态分析是很难解决的。
不过听说它会像调试器输出一些奇怪的什么以WHUCTF开头的奇怪字符串信息就是了，我有什么办法拿到这个字符串吗......

## Hint
1. VS工程的链接器的某个选项中有一个叫做系统的选项，通常来说这个值是SUBSYSTEM:CONSOLE或SUBSYSTEM:WINDOWS，分别对应了控制台应用和窗口应用。这个程序的这个属性好像跟他们有一些不同？同时这个程序的内存空间好像异常的干净，只有一个ntdll。
2. 我可以通过什么方式来启动它，并且在它结束之前把调试器附加上去得到它调用某个函数向调试器输出的信息。

## Platform
`Windows`

## File
`EzNative.vmp.exe`

## Flag
`WHUCTF{e25ff8d8-e7be-42b7-9aec-7fe7eb5c93fa}`

## Info
使用`RtlCreateProcessParameters`+`RtlCreateUserProcess`+`ResumeThread`即可，在`ResumeThread`之前把调试器挂上去就能看到输出了。