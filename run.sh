#!/bin/bash

dir=$(pwd)

valgrind -q --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --show-reachable=yes --suppressions=./readline.supp ./minishell
#valgrind -q --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --show-reachable=yes --suppressions=    ./libc_leak.supp ./minishell
