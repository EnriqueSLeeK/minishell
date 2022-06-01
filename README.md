# minishell &middot; [![Norminette](https://github.com/EnriqueSLeeK/minishell/actions/workflows/norminette.yml/badge.svg)](https://github.com/EnriqueSLeeK/minishell/actions/workflows/norminette.yml) [![make-test](https://github.com/EnriqueSLeeK/minishell/actions/workflows/build.yml/badge.svg)](https://github.com/EnriqueSLeeK/minishell/actions/workflows/build.yml)

## Description
This project is from the 42 cursus and aims to implement a simple shell

## Compilation
### For the mandatory version
```
make
```
### For the bonus version
```
make bonus
```

## Functionalities
### Implemented
- Input/Output redirections ( <, <<, >, >> )
- Some builtins
- Environment variables ( creation, deletion, substitution )
- Wildcard (only the * expansion) [bonus only]
- Logical operator ( &&, || ) [bonus only]
- Priority parentheses [bonus only]

### Not implemented
- ; and \ metacharacter are not implemented

## Builtins
### cd
Change the current directory
```
cd <dir>
```
### pwd 
Print the current directory
```
pwd
```
### echo
Print out the arguments given to him
Supported flag: -n (have the same behavior as the original echo)
```
echo <arg1> ... <argn>
echo -n <arg1> ... <argn>
```

### Export
Set or substitue a environment variables
```
export <var1>=<value1> ... <varn>=<valuen>
```

### Unset
Unset environment variables
```
unset <var1> ... <varn>
```

### Exit
Just exit the program
```
exit
```
