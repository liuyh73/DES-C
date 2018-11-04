# des

**数据加密标准**（英语：Data Encryption Standard，缩写为 DES）是一种[对称密钥加密](https://zh.wikipedia.org/wiki/%E5%B0%8D%E7%A8%B1%E5%AF%86%E9%91%B0%E5%8A%A0%E5%AF%86)[块密码](https://zh.wikipedia.org/wiki/%E5%A1%8A%E5%AF%86%E7%A2%BC)算法，1976年被[美国](https://zh.wikipedia.org/wiki/%E7%BE%8E%E5%9B%BD)联邦政府的[国家标准局](https://zh.wikipedia.org/wiki/%E5%9B%BD%E5%AE%B6%E6%A0%87%E5%87%86%E5%B1%80)确定为[联邦资料处理标准](https://zh.wikipedia.org/wiki/%E8%81%94%E9%82%A6%E8%B5%84%E6%96%99%E5%A4%84%E7%90%86%E6%A0%87%E5%87%86)（FIPS），随后在国际上广泛流传开来。它基于使用56位密钥的[对称算法](https://zh.wikipedia.org/w/index.php?title=%E5%AF%86%E9%92%A5%E5%AF%86%E7%A0%81%E5%AD%A6&action=edit&redlink=1)。（来自[wiki](https://zh.wikipedia.org/wiki/%E8%B3%87%E6%96%99%E5%8A%A0%E5%AF%86%E6%A8%99%E6%BA%96#%E5%AF%86%E9%92%A5%E8%B0%83%E5%BA%A6)）

## 项目结构

```bash
DES-C
  |─cipher_code
  |  |─ cipher_code.cpp
  |  └─ cipher_code.hpp
  |
  |─des
  |  |─ des.cpp
  |  └─ des.hpp
  |
  |─initial_replace
  |  |─ initial_replace.cpp
  |  └─ initial_replace.hpp
  |
  |─iteration
  |  |─ iteration.cpp
  |  └─ iteration.hpp
  |
  |─reverse_replace
  |  |─ reverse_replace.cpp
  |  └─ reverse_replace.hpp
  |
  |─utils
  |  |─ utils.cpp
  |  └─ utils.hpp
  |
  |─main.cpp
  |─makefile
  └─README.md
```

## cipher_code/

此文件主要提供加解密过程中的16组子密钥。

子秘钥的生成：(秘钥调度)

首先，使用**选择置换1**（PC-1）从64位输入密钥中选出56位的密钥—剩下的8位要么直接丢弃，要么作为奇偶校验位。然后，56位分成两个28位的半密钥；每个半密钥接下来都被分别处理。在接下来的回次中，两个半密钥都被左移1或2位（由回次数决定），然后通过**选择置换2**（PC-2）产生48位的子密钥—每个半密钥24位。移位表明每个子密钥中使用了不同的位，每个位大致在16个子密钥中的14个出现。

## des/

此文件包含加密解密函数，提供对外的两个接口Encrypt、Decrypt，用于对明文加密解密

## initial_replace/

加解密第一步：**初始置换（IP）**-- 将明文/密文经过一个8*8的矩阵变换来更改明文/密文的顺序

## iteration/

加解密第二步：**费斯妥函数（F函数）**

- **E扩张置换** -- 将32位（原始数据的一半）的明文/密文扩展到48位，其输出包括8个6位的数据

- **与子密钥进行混合** -- 用异或操作将扩张的结果和一个子密钥进行混合。16个48位的子密钥——每个用于一个回次的F变换

- **S盒置换** -- 在与子密钥混合之后，块被分成8个6位的块，然后使用“S盒”，或称“置换盒”进行处理。8个S盒的每一个都使用以查找表方式提供的非线性的变换将它的6个输入位变成4个输出位。S盒提供了DES的核心安全性（如果没有S盒，密码会是线性的，很容易破解）。

- **P置换** -- 最后，S盒的32个输出位利用固定的置换，“P置换”进行重组。这个设计是为了将每个S盒的4位输出在下一回次的扩张后，使用4个不同的S盒进行处理。

## reverse_replace/

加解密最后一步：**逆序置换（FP）** -- 逆置换是初始置换的逆运算。从初始置换规则中可以看到，原始数据的第1位置换到了第40位，第2位置换到了第8位。则逆置换就是将第40位置换到第1位，第8位置换到第2位。

## utils.go

该文件提供一些功能函数，主要是编解码过程中二进制串与16进制串、普通字符串之间的相互转换函数。

### main.go

提供使用该包的方法

### makefile

需要在linux下使用make命令编译该文件，得到可执行文件。

**【注】** 解密过程中，除了子密钥顺序相反外，密钥调度的过程与加密完全相同。（即我们可以首先获得16个子秘钥，加密过程使用顺序的子秘钥，解密过程使用逆序的子秘钥）。详细内容参考下方博客。

**【博客链接】** https://blog.csdn.net/liuyh73/article/details/83472521