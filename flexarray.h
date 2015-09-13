/*flexarray.h*/
#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_
typedef struct flexarrayrec *flexarray;
extern void flexarray_append(flexarray f, char *word);
extern void flexarray_free(flexarray f);
extern flexarray flexarray_new();
extern void flexarray_print(flexarray f);
extern int is_present(flexarray f, char *word);
extern void visit(flexarray f, void p(char *str));
#endif
