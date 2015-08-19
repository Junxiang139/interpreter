Scheme解释器报告
黄俊翔 5140309571
项目内容
该大作业为一个在C++ 11下编写，实现R5RS标准下的Scheme解释器。
举例：
输入：(display (+ 1 2))
	输出：3

	输入：
(define y1 (list 1 2 3 4))
(display (map (lambda (x) (* x x)) y1))
输出：(1 4 9 16)

输入：
(define (fib n)
 (cond ((= n 0) 0)
       ((= n 1) 1)
       (else (+ (fib (- n 1))
               (fib (- n 2))))))
(display (fib 20))
输出：6765

编译环境
在Dev-C++ 5.3.04下编写及编译。
编译时加入以下命令：-std=c++11 -Wl,--stack,100000000
在连接器命令行加入以下命令：-static-libgcc

已实现功能
在历史no side effect中，能正确实现：
utilities
basic operations
try some big numbers
fast-exp
Fibonacci（注：若使用递归斐波那契则32需要一分钟运行时间）
(define unused_var (fib 50000)) ：implemented tail call optimization
the compute
predicates
pairs and lists（小部分特殊函数未实现，hanoi已实现）
let-bindings
以及不能被作为复杂抽象时调用对象的、仅仅基础的map、apply、length等操作

未实现功能
pairs and lists中的cadr, list-ref, memq, table, assq
infinite stream
N-queens
closure
Test with side effect
