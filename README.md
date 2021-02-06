# printf
printf imitation

# Requirements
In source file, replace printf -> ori_printf and add this line
>#include "printf/ori_printf.h"

# Run
Clone this repository to the root of your repo and run this command
>- cd printf && make && cp libprintf.a .. && cd ..
>- gcc (source file) libprintf.a
>- ./(exe file)
