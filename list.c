#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct node *create_node(char *k, struct node* next)
{
   struct node *node=(struct node *)malloc(sizeof(struct node));
   node->key = (char *) malloc((strlen(k) + 1) * sizeof(char));
   strcpy(node->key, k);
   node->next = next;
   return(node);
}

void destroy_list(struct node *head)
{
   static struct node *next;

   if (head == (struct node *) NULL)
      return;
   next = head->next;
   free(head->key);
   free(head);
   destroy_list(next);
}

struct node *cons(char *k, struct node *node)
{
   return(create_node(k, node));
}

struct node *append(struct node *head, char *k)
{
   if (head == (struct node *) NULL) {
      head = create_node(k, head);
      return(head);
   }
   head->next = append(head->next, k);
   return(head);
}

struct node *insert(struct node *head, char *k)
{
   if (head == (struct node *) NULL || strcmp(k, head->key) < 0) {
      head = create_node(k, head);
      return(head);
   }
   if (strcmp(k, head->key) != 0)
      head->next = insert(head->next, k);
   return(head);
}

struct node *locate(struct node *head, char *k)
{
   if (head == (struct node *) NULL || strcmp(head->key, k) == 0)
      return(head);

   if (head->next != (struct node *) NULL
         && strcmp(head->next->key, k) == 0)
      return(head);
   return(locate(head->next, k));
}

struct node *delete(struct node *head, char *k)
{
   struct node *target, *tag;

   if (head == (struct node *) NULL)
      return(head);

   if (strcmp(k, head->key) == 0) {
      target = head->next;
      free(head->key);
      free(head);
      return(target);
   }
   target = locate(head, k);
   if (target) {
      tag = target->next;
      target->next = target->next->next;
      free(tag->key);
      free(tag);
   }
   return(head);
}

struct node *reverse(struct node *curr, struct node *prev)
{
   struct node *rest;

   if (curr == (struct node *) NULL)
      return(prev);
   rest = curr->next;
   curr->next = prev;
   return reverse(rest, curr);
}

int size(struct node *head)
{
   if (head == (struct node *) NULL)
      return(0);
   return(1 + size(head->next));
}

void print_list(struct node *node)
{
   if (node == (struct node *) NULL)
      return;
   puts(node->key);
   print_list(node->next);
}

struct node *read_text(struct node *node, FILE *fp)
{
   static char buf[32];

   if (fscanf(fp, " %[^\n]", buf) == EOF)
      return(reverse(node, (struct node *) NULL));
   /*
   if (fgets(buf, 32, fp) == NULL)
      return(node);
   buf[strlen(buf)-1] = '\0';
   */
   /* puts(buf); */
   return(read_text(cons(buf, node), fp));
}

void write_text(struct node *node, FILE *fp)
{
   if (node == (struct node *) NULL)
      return;
   fprintf(fp, "%s\n", node->key);
   write_text(node->next, fp);
}

struct node *read_binary(struct node *node, FILE *fp)
{
   static char buf[32];

   memset(buf, '\0', sizeof(buf));
   if (fread(buf, sizeof(buf), 1, fp) == 0)
      return(reverse(node, (struct node *) NULL));
   return(read_binary(cons(buf, node), fp));
}

void write_binary(struct node *node, FILE *fp)
{
   static char buf[32];

   if (node == (struct node *) NULL)
      return;
   memset(buf, '\0', sizeof(buf));
   strcpy(buf, node->key);
   fwrite(buf, sizeof(buf), 1, fp);
   write_binary(node->next, fp);
}
