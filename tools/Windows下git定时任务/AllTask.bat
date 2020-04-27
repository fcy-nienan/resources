set batPath=D:\ScheduledTask\
cd /d %batPath%
#:loop
call getNewestGitReposity.bat >> D:\ScheduledTask\execute.log
echo "executed finished"
set ttt=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%
echo %ttt%
echo %ttt% > D:\%ttt%


#timeout 1800
#goto loop