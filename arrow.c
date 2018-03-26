#include "all_include.h"

int pressed_arrow(){
	int c = 0;
	static struct termios oldTermios, newTermios;

	tcgetattr(STDIN_FILENO, &oldTermios);
	newTermios = oldTermios;

	cfmakeraw(&newTermios);

	tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
	if(c==27){
			tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
			c = getchar();
			tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
			if(c==91){
				tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
				c = getchar();
				tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
				if(c==65){
					printf("up");
					return 1;
				}
				else if(c==66){
					printf("down");
					return 2;
				}
				else{
					ungetc(c, stdin);

					return 0;
				}
			}
			
			else{
				ungetc(c, stdin);
				return 0;
			}
		}
	else if(c==3 || c==26){
		ungetc(c, stdin);
		return -1;
	}
	else{
			ungetc(c, stdin);
			return 0;
	}
	
	return 0;	
}	


// int main(){
// 	int a;
// 	a=pressed_arrow();
// 	while(a!=-1){
// 		a=pressed_arrow();	
// 	}
// }