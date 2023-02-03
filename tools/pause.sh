# On MacOS, the pause button doesn't work for the debugger.
# However, a running program can be paused with SIGINT
ps aux | grep berzerk | awk '{print $2}' | xargs kill -2 
