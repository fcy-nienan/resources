set timestamp=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%
set commitMessage=%timestamp%

set dir="D:\Code\WorkSpace\java\NewWorkSpace\Image"
call pullAndpush.bat %dir% %commitMessage%
cd /d %batPath%

set dir="D:\Code\WorkSpace\pratice"
call pullAndpush.bat %dir% %commitMessage%
cd /d %batPath%

set dir="D:\Code\WorkSpace\resources"
call pullAndpush.bat %dir% %commitMessage%
cd /d %batPath%


