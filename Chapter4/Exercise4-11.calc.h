/** Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
  * static variable. */

#define NUMBER '0'

void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);