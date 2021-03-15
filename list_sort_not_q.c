#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "list_sort_no_q.h"

static struct list_head *list_new() {
  struct list_head *head = malloc(sizeof(struct list_head));
  if (!head)
    return NULL;
  INIT_LIST_HEAD(head);
  return head;
}
bool list_insert_head(struct list_head *head, char *s) {
  if (!head)
    return false;
  list_ele_t *newh = malloc(sizeof(list_ele_t));
  if (!newh)
    return false;
  char *new_value = strdup(s);
  if (!new_value) {
    free(newh);
    return false;
  }
  newh->value = new_value;
  // newh->list.next = head->next;
  // head->next = newh;
  list_add_tail(&(newh->list), head);
}

static void list_free(struct list_head *head) {
  if (!head)
    return;
  struct list_head *current = head->next;
  while (current) {
    if (current == head) {
      break;
    }
    list_ele_t *tmp = list_entry(current, list_ele_t, list);
    current = current->next;
    free(tmp->value);
    free(tmp);
  }
}

int main(void)
{
    FILE *fp = fopen("cities.txt", "r");
    if (!fp) {
      perror("failed to open cities.txt");
      exit(EXIT_FAILURE);
    }

    struct list_head *head = list_new();
    char buf[256];
    while (fgets(buf, 256, fp))
      list_insert_head(head, buf);
    fclose(fp);
    list_merge_sort(head);
    // assert(validate(q));

    list_free(head);

    return 0;
}
