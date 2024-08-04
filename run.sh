#!/bin/bash

# clear
clear

# Delete specified files if they exist
files_to_delete=("env" "input" "visualizer" "checkout")
for file in "${files_to_delete[@]}"; do
  if [ -e "$file" ]; then
    echo "Deleting $file"
    rm -f "$file"
  fi
done

# make re
echo make re
make re &> /dev/null

# color
GREEN='\033[0;32m' # GOOD
BLUE='\033[0;34m' # YOU NEED TEST
RED='\033[0;31m' # NEED TO FIX?
NC='\033[0m' # No Color
B_Yellow='\033[0;43m' # Back glound color
B_GREEN='\033[0;42m' # Back glound color
B_WHITE='\033[0;47m' # Back glound color

# check success of make re
if [ $? -eq 0 ]; then
  if [ "$1" == "valgrind" ]; then
    # run executable with valgrind
    echo "valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp ./minishell"
    valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --suppressions=readline.supp ./minishell
  
		elif  [ "$1" == "echo" ]; then
    echo Running evaluation...
    echo -e ${B_Yellow}_______ORIGINAL SHELL [echo]________${NC}
    echo -e ${GREEN}1: echo hello our evaluator!${NC}
    echo "hello our evaluator!"
    echo -e ${GREEN}2: echo -n hello our evaluator!${NC}
    echo -n hello our evaluator!
    echo -e "${GREEN}3: echo ichi ni  san shi go${NC}"
    echo "cat lol.c | cat > lol.c"
    echo -e ${BLUE}'5: If something crashes, select the "crash" flag.'${NC}
    echo -e ${BLUE}'6: If something doesn'"'"'t work, select the "incomplete work" flag.'${NC}
    echo
				echo -e ${B_GREEN}________OUR MINISHELL [echo]________${NC}
				./minishell << EOF && echo -e ${B_WHITE}________________FIN________________${NC}
echo hello our evaluator!
echo -n hello our evaluator!
echo ichi ni  san shi go

exit
EOF
		elif [ "$1" == "DoubleQuotes" ]; then
    echo Running evaluation...
    echo -e ${B_Yellow}_______ORIGINAL SHELL [Double Quotes]________${NC}
    echo -e ${GREEN}1: echo \"hello our evaluator!\"${NC}
    echo "hello our evaluator!"
    echo -e "${GREEN}2: echo \"cat lol.c | cat > lol.c\"${NC}"
    echo "cat lol.c | cat > lol.c"
    echo -e ${GREEN}3: Try anything except $ : echo we are \"TOO\" nice${NC}
    echo "we are \"TOO\" nice"
    echo -e ${BLUE}'4: If something crashes, select the "crash" flag.'${NC}
    echo -e ${BLUE}'5: If something doesn'"'"'t work, select the "incomplete work" flag.'${NC}
    echo
				echo -e ${B_GREEN}________OUR MINISHELL [Double Quotes]________${NC}
				./minishell << EOF && echo -e ${B_WHITE}________________FIN________________${NC}
echo "hello our evaluator!"
echo "cat lol.c | cat > lol.c"
echo we are "TOO" nice

exit
EOF
		elif [ "$1" == "SingleQuotes" ]; then
    echo Running evaluation...
    echo -e ${B_Yellow}_______ORIGINAL SHELL [Single Quotes]________${NC}
    echo -e "${GREEN}1: echo 'hello our evaluator!${NC}'"
    echo 'hello our evaluator!'
    echo -e "${GREEN}2: echo ''${NC}"
				echo ''
    echo -e "${GREEN}3: echo 'Which  \$PATH tell me \$USERs name > file | cat|ls'${NC}"
    echo 'Which  $PATH tell me $USERs name > file | cat|ls'
    echo -e "${GREEN}4: echo '\$USER'${NC}"
    echo '$USER'
				echo -e "${BLUE}5: Nothing should be interpreted.${NC}"
    echo -e ${B_GREEN}________OUR MINISHELL [Single Quotes]________${NC}
				./minishell << EOF && echo -e ${B_WHITE}________________FIN________________${NC}
echo 'hello our evaluator!'
echo '\$USER'
echo 'Which  \$PATH tell me \$USERs name > file | cat|ls'

exit
EOF
  else
    # run executable
    echo "./minishell"
    ./minishell
  fi
else
  echo "Error: make failed"
fi

# make fclean
echo "make fclean"
make fclean &> /dev/null

# Delete specified files if they exist
files_to_delete=("env" "input" "visualizer" "checkout")
for file in "${files_to_delete[@]}"; do
  if [ -e "$file" ]; then
    echo "Deleting $file"
    rm -f "$file"
  fi
done

# norminette
if command -v "norminette" &> /dev/null; then
  echo "norminette error: " \
  && norminette | grep Error! | wc -l
fi
