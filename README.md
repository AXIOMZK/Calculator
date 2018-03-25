# Calculator 数值表达式计算器

> 数值表达式 计算器
* 支持 + - * / (  ) 按符号优先级 计算
* 一个数值间不能有空格,比如数字10不能为&emsp;1&emsp;&emsp;0&emsp;,只能为10
* 数值与操作符直接可以有任意空格,比如 10&emsp;&emsp;+&emsp;2 &emsp; *&emsp;  5
* 回车键确认输入，进行计算
* 支持自定义符号计算，如pi=3.1415926, 需要声明map<string,double>table和NAME
> 计算示例
```
输入

12 + 3 * 6

输出

30

输入

(2 + 3) * 6

输出

30
```