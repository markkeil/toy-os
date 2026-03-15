#ifndef TERMINAL_H
#define TERMINAL_H

void tinit();
void tputchar(char c);
void tprint(const char *str);
void tprinthex(unsigned int n);
void tprintint(int n);

#endif