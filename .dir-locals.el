;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

((nil
  (projectile-project-type . cmake)
  (projectile-project-test-cmd . "cd bin && ./unit_test")
  (projectile-project-compilation-cmd . "cmake --build build --target all")
  (projectile-project-run-cmd . "cd bin/ && ./main")
  (cmake-ide-project-dir . "/home/mario/Projects/awescheme/")
  (cmake-ide-build-dir . "/home/mario/Projects/awescheme/build/")
  )
 (c++-mode
  (eval add-hook 'before-save-hook #'clang-format-buffer nil t)))
