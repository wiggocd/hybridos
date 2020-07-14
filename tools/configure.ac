AC_INIT([hybridos], [0.1], [cd.wiggins@outlook.com])

AC_PROG_CC

REQUIRED=""

AC_DEFUN(AC_PROG_NASM, [AC_CHECK_PROG(NASM, nasm, yes)])
AC_PROG_NASM
if test x"${NASM}" != x"yes";
then
    REQUIRED+=" nasm"
fi

AC_DEFUN(AC_PROG_MAKE, [AC_CHECK_PROG(MAKE, make, yes)])
AC_PROG_MAKE
if test x"${MAKE}" != x"yes";
then
    REQUIRED+=" make"
fi

AC_DEFUN(AC_PROG_CURL, [AC_CHECK_PROG(CURL, curl, yes)])
AC_PROG_CURL
if test x"${CURL}" != x"yes";
then
    REQUIRED+=" curl"
fi



if test x"${#REQUIRED}" != x"0";
then
    AC_MSG_ERROR([Please install these packages before running configure:${REQUIRED}])
fi