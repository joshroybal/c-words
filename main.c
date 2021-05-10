#include <stdio.h>
#include "list.h"

int main()
{
   struct node *words = (struct node *) NULL;
   FILE *fp;

   fp = fopen("/usr/dict/words", "r");
   words = read_text(words, fp);
   fclose(fp);
   puts(" << /usr/dict/words");
   fp = fopen("words.bin", "wb");
   write_binary(words, fp);
   fclose(fp);
   puts(" >> words.bin");
   destroy_list(words);
   words = (struct node *) NULL;
   fp = fopen("words.bin", "rb");
   words = read_binary(words, fp);
   fclose(fp);
   puts(" << words.bin");
   fp = fopen("words.txt", "wb");
   write_text(words, fp);
   fclose(fp);
   puts(" >> words.txt");
   destroy_list(words);
   return(0);
}
