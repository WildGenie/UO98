bcc32 -I%inc% -I%apidir% -L%lib% -tWD -c jit.cpp
bcc32 -I%inc% -I%apidir% -L%lib% -tWD %1 jit.obj
