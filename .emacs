
;;(autoload 'run-prolog "sicstus" "Start a Prolog sub-process." t)
;;(autoload 'prolog-mode "sicstus" "Major mode for editing Prolog programs" t)

;;(setq load-path (cons (expand-file-name "~herme/GNU") load-path))

(setq spell-command "detex | spell") 

(put 'eval-expression 'disabled nil)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(autoload 'latex-mode "tex-mode")
(load "tex-mode") ;; so that TeX-mode-map additions don't fail
(load "misc.el")  ;; This a MCL patch... perhaps not very pretty

(define-key TeX-mode-map "\C-c\C-v" 'TeX-view) ;; TeX-view in misc.el
(define-key TeX-mode-map "\C-c\C-s" 'TeX-run-view-slide) ;; view slide misc.el
(define-key TeX-mode-map "\C-c\C-f" 'Latex-find-error) ;; my macro
(define-key TeX-mode-map "\C-c\C-t" 'TeX-bibtex)

(setq TeX-directory "/tmp/")
(setq TeX-dvi-print-command "dvispool")
(setq TeX-bibtex-command "bibtex")
(setq TeX-show-queue-command "lpq")

(if (eq window-system 'x)
    (setq TeX-dvi-view-command  "texx -l 1 -tm 0.3 -sm 0.3 =-0-0 ")
  (setq TeX-dvi-view-command "texsun -Wp 474 0 -Ws 678 909 -WP 1012 96 -Wf 0 100 155 -Wi ~/icons/garfield -l 1") )
    (setq TeX-dvi-view-command  "texsun -l 1 -tm 0.5 -sm 0.5 ") )
(setq TeX-default-mode 'LaTeX-mode)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; Spanish in LaTeX:
;; Use: F1 (L1 in Sun) + character

(defun spchars (char)
  (interactive "*c")
  ( cond
    ((equal char ?n) (insert-string "\\~{n}"))
    ((equal char ?a) (insert-string "\\'{a}"))
    ((equal char ?e) (insert-string "\\'{e}"))
    ((equal char ?i) (insert-string "\\'{\\i}"))
    ((equal char ?o) (insert-string "\\'{o}"))
    ((equal char ?u) (insert-string "\\'{u}"))
    ((equal char ??) (insert-string "?'"))
    ((equal char ?!) (insert-string "!'"))
    ( t (insert-char char 1))
  )) 
(global-set-key "\C-x*bl" 'spchars)	; Sun L2
;; (global-set-key "\C-'" 'spchars)	; Sun L2
;; (define-key TeX-mode-map "\C-'" 'spchars)
;; WARNING: ONLY FOR X-WINDOWS
(global-unset-key "\e[")
(global-set-key "[193z" 'spchars)   ;L2 in Xwindows for Sun
(global-set-key "[224z" 'spchars)   ;F1 in Xwindows for Xterminal





















