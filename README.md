Scheme����������
�ƿ��� 5140309571
��Ŀ����
�ô���ҵΪһ����C++ 11�±�д��ʵ��R5RS��׼�µ�Scheme��������
������
���룺(display (+ 1 2))
	�����3

	���룺
(define y1 (list 1 2 3 4))
(display (map (lambda (x) (* x x)) y1))
�����(1 4 9 16)

���룺
(define (fib n)
 (cond ((= n 0) 0)
       ((= n 1) 1)
       (else (+ (fib (- n 1))
               (fib (- n 2))))))
(display (fib 20))
�����6765

���뻷��
��Dev-C++ 5.3.04�±�д�����롣
����ʱ�����������-std=c++11 -Wl,--stack,100000000
�������������м����������-static-libgcc

��ʵ�ֹ���
����ʷno side effect�У�����ȷʵ�֣�
utilities
basic operations
try some big numbers
fast-exp
Fibonacci��ע����ʹ�õݹ�쳲�������32��Ҫһ��������ʱ�䣩
(define unused_var (fib 50000)) ��implemented tail call optimization
the compute
predicates
pairs and lists��С�������⺯��δʵ�֣�hanoi��ʵ�֣�
let-bindings
�Լ����ܱ���Ϊ���ӳ���ʱ���ö���ġ�����������map��apply��length�Ȳ���

δʵ�ֹ���
pairs and lists�е�cadr, list-ref, memq, table, assq
infinite stream
N-queens
closure
Test with side effect
