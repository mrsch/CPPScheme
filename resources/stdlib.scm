;; Additional stdlib functions
(define (curry func arg1) (lambda (arg) (apply func (cons arg1 (list arg)))))
(define (id obj) obj)
(define (flip func) (lambda (arg1 arg2) (func arg2 arg1)))
(define (compose f g) (lambda (args) (f (apply g args))))
(define (foldr func end lst)
  (if (null? lst)
      end
      (func (car lst) (foldr func end (cdr lst)))))
(define (foldl func accum lst)
  (if (null? lst)
      accum
      (foldl func (func accum (car lst)) (cdr lst))))
(define fold foldl)
(define reduce foldr)
(define (sum lst) (fold + 0 lst))
(define (product lst) (fold * 1 lst))

;; Numerical
(define zero?              (curry = 0))
(define positive?          (curry < 0))
(define negative?          (curry > 0))
(define (odd? num)         (= (modulo num 2) 1))
(define (even? num)        (= (modulo num 2) 0))
(define (unfold func init pred)
  (if (pred init)
      (cons init '())
      (cons init (unfold func (func init) pred))))

;; Booleans
(define (not x) (if x #f #t))

;; Lists
(define (null? obj) (if (eqv? obj '()) #t #f))
(define (length lst) (fold (lambda (x y) (+ x 1)) 0 lst))
(define (reverse lst) (fold (flip cons) '() lst))
(define (map func lst)      (foldr (lambda (x y) (cons (func x) y)) '() lst)) ;; TODO: multiple lists 1 list for each argument
(define (filter pred lst)   (foldr (lambda (x y) (if (pred x) (cons x y) y)) '() lst))

;; Random functions
(define (factorial n)
 (cond ((< n 0) #f)
         ((<= n 1) 1)
         (else (* n (factorial (- n 1))))))

(define (make-adder num) (lambda (arg) (+ arg num)))
