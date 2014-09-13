REM Global Const REGKEYSTR = "ps70p7c0"     ' Evaluation until 9/01/97 (HW key ignored)
REM Global Const REGKEYSTR = "9u239u23"     ' Master Key (HW key ignored)
bfr "ps70p7c0" "9u239u23" *.exe -b
fd  *.* /t12:00 /d09-01-97
