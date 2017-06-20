;;; 6. DOT-PRODUCT FUNCTION (works)
(defun dot-product (x y)
  (cond 
    ((equal x nil) 0)
    (t (+ (* (car x) (car y))
  (dot-product (cdr x) (cdr y))))))

;;; 7. COUNT-NUMBER FUNCTION (works)
(defun count-number (x)
  (cond
    ((null x) 0)
    ((numberp (car x)) (+ 1 (count-number (cdr x))))
    (t (count-number (cdr x)))))

;;; 8. NEW-LIST FUNC (works)
(defun new-list (x)
  (if (< x 1) '()
    (cons T (new-list(- x 1)))))

;;; 9. ALL-LENGTH FUNCTION (works)
(defun all-length (x)
  (if (equal x nil) 0
    (if (atom (car x)) (+ 1 (all-length (cdr x)))
      (+ (all-length (car x)) (all-length (cdr x))))))
