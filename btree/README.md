# 用C语言实现B树

> 此程序由C语言实现，实现了B树的基本操作。

### 基本操作

​        InitBTree(&t)

​        操作结果：初始化一棵空的B树。

​        CreateBTreeRandom(&t,keyNumber)

​        初始条件：keyNumber为正整数，且范围为1-1000。

​        操作结果：根据用户输入生成一棵随机数的B树。

​        SearchBTree(t, key, &r)

​        初始条件：B树t存在。

​        操作结果：在B-树t查找关键字key，用r返回（pt, i, tag）        InsertBTree(&t, key, q, i)

​        初始条件：B树t存在。

​        操作结果：在B-树t中q结点的key[i - 1]和key[i]之间插入关键字key。 

​        DeleteBTree(&t, &p, i)

​        初始条件：B树t存在。

​        操作结果：删除B树上p结点的第i个关键字。

​        OrderTraverseBTree(t)

​        初始条件：B树t存在。

​        操作结果：按关键字大小升序输出B树关键字。

​        PrintBTree(t,tab)

​        初始条件：B树t存在。

​        操作结果：以凹入表的形式打印B树。

​        BTreeKeyNumber(t)

​        初始条件：B树t存在。

​        操作结果：返回B树关键字数量。

​        DestoryBTree(&t)

​        初始条件：B树t存在。

​        操作结果：销毁B树。

相关博文：http://minsming.com/2018/01/25/B%E6%A0%91%E4%B9%8BC%E8%AF%AD%E8%A8%80%E5%AE%9E%E7%8E%B0/