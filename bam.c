# include <signal.h>
# include <stdio.h>


# include "ipc/ipc.h"

# define FALSE 0
# define TRUE 1
main() {
 long *bp;
 extern ipc_msg;
 char buff[20];

 ipc_init(TRUE);


 ipc_snd( IPC_T_END, buff );
 printf("-S->%d<\n",ipc_msg );
 
 ipc_terminate(TRUE);
 printf("-S- bye\n");
 return(0);
}
