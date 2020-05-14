#include "../linkedlist.h"

Status assert_number_list(List_ptr list,int *expected,int length) {
  if (list->length != length)
  {
    return Failure;
  }
  Node_ptr p_walk = list->first;
  for (int index = 0; index < length; index++)
  {
    int current_value = *(int *)p_walk->element;
    if (current_value != expected[index])
      return Failure;
    p_walk = p_walk->next;
  }
  return Success;
}

void  print_test_status(char operation[],int status) {
  if(status) {
    printf("Success: %s\n", operation);
  } else {
    printf("Failed: %s\n", operation);
  }
}

void test_create_list() {
  char operation[] = "Should create an empty list";
  List_ptr list = create_list();
  if(list->first == NULL && list->last == NULL && list->length == 0) {
    return print_test_status(operation,Success);
  }
  return print_test_status(operation,Failure);
}

void test_add_to_list() {
  char operation[] = "Add to list";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  print_test_status(operation,assert_number_list(list, elements, 2));
}

void test_add_to_start() {
  char operation[] = "Add to list at start";
  List_ptr list = create_list();
  int elements[] = {0};
  add_to_start(list, &elements[0]);
  print_test_status(operation,assert_number_list(list, elements, 1));
}

void test_insert_at() {
  char operation[] = "Should insert at given valid position";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  add_to_start(list, &elements[0]);
  insert_at(list, &elements[1], 1);
  print_test_status(operation, assert_number_list(list, elements, 2));
}

int main()
{
  test_create_list();
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  return 0;
}