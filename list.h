#ifndef LIST_H
#define LIST_H

struct node {
   char *key;
   struct node *next;
};

struct node *create_node(char *, struct node *);
void destroy_list(struct node *);
struct node *cons(char *, struct node *);
struct node *append(struct node *, char *);
struct node *insert(struct node *, char *);
struct node *locate(struct node *, char *);
struct node *delete(struct node *, char *);
struct node *reverse(struct node *, struct node *);
int size(struct node *);
void print_list(struct node *);
struct node *read_text(struct node *, FILE *);
void write_text(struct node *, FILE *);
struct node *read_binary(struct node *, FILE *);
void write_binary(struct node *, FILE *);

#endif
