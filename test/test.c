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

Element int_increment(Element number)
{
  int* result = malloc(sizeof(int));
  *result = *(int *)number + 1;
  Element void_result = result;
  return void_result;
}

Status is_even(Element data)
{
  int number = *(int *)data;
  return number % 2 == 0;
}

Element get_sum(Element data1,Element data2) {
  int* result = malloc(sizeof(int));
  int num1 = *(int *)data1;
  int num2 = *(int *)data2;
  *result = num1 + num2;
  Element void_result = result;
  return void_result;
}

Status match_int(Element data1,Element data2) {
  int num1 = *(int *)data1;
  int num2 = *(int *)data2;
  return num1 == num2 ? Success : Failure;
}

void test_map() {
  char operation[] = "should map for each element";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  int expected[] = {2, 3};
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  List_ptr result = map(list, &int_increment);
  print_test_status(operation, assert_number_list(result, expected, 2));
}

void test_filter() {
  char operation[] = "should filter the elements based on conditions";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  int expected[] = {2};
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  List_ptr result = filter(list, &is_even);
  print_test_status(operation, assert_number_list(result, expected, 1));
}

void test_reduce() {
  char operation[] = "should reduce the given list using the accumulator";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  int data = 0;
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  Element result = reduce(list,&data,&get_sum);
  print_test_status(operation,(*(int *)result)==3?Success:Failure);
}

void test_add_unique() {
  char operation1[] = "should add if the given element is not found in the list";
  List_ptr list = create_list();
  int elements[] = {1, 2};
  int unique_element = 3;
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  print_test_status(operation1, add_unique(list, &unique_element, &match_int));
  char operation2[] = "should not add if the given element exist";
  int existing_element = 2;
  print_test_status(operation2, !add_unique(list, &existing_element, &match_int));
}

void test_remove_from_start() {
  char operation1[] = "should not remove any element when the list is empty";
  List_ptr list = create_list();
  Element result1 = remove_from_start(list);
  print_test_status(operation1, result1 == NULL ?Success: Failure);

  char operation2[] = "should remove the first element in the list";
  int elements[] = {1, 2};
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  Element result2 = remove_from_start(list);
  print_test_status(operation2, *(int *)result2 == 1 ?Success: Failure);
}

void test_remove_from_end() {
  char operation1[] = "should not remove any element when list is empty";
  List_ptr list = create_list();
  Element result1 = remove_from_start(list);
  print_test_status(operation1, result1 == NULL ?Success: Failure);

  char operation2[] = "should remove the last element in the list";
  int elements[] = {1, 2};
  add_to_list(list, &elements[0]);
  add_to_list(list, &elements[1]);
  Element result2 = remove_from_end(list);
  print_test_status(operation2, *(int *)result2 == 2 ? Success : Failure);
}

int main()
{
  test_create_list();
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_map();
  test_filter();
  test_reduce();
  test_add_unique();
  test_remove_from_start();
  test_remove_from_end();
  return 0;
}