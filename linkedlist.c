#include "linkedlist.h"

List_ptr create_list(void) {
  List_ptr new_list = malloc(sizeof(LinkedList));
  new_list->length = 0;
  new_list->first = NULL;
  new_list->last = NULL;
  return new_list;
}

Node_ptr create_node(void *data)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = data;
  new_node->next = NULL;
  return new_node;
}

Status add_to_list(List_ptr list, Element data)
{
  Node_ptr new_node = create_node(data);
  if(list->first == NULL)
  {
    list->first = new_node;
    list->last = new_node;
    list->length++;
    return Success;
  }
  Node_ptr p_walk = list->first;
  while (p_walk->next != NULL)
  {
    p_walk = p_walk->next;
  }
  p_walk->next = new_node;
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list,Element data)
{
  Node_ptr new_node = create_node(data);
  if (list->first == NULL)
  {
    list->first = new_node;
    list->last = new_node;
    list->length++;
    return Success;
  }
  new_node->next = list->first;
  list->first = new_node;
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{
  if (position > list->length || position < 0)
  {
    return Failure;
  }
  Node_ptr new_node = create_node(element);
  if (position == 0)
  {
    return add_to_start(list, element);
  }
  Node_ptr p_walk = list->first;
  Node_ptr previous_node = list->first;
  int counter = 0;
  while (counter != position)
  {
    previous_node = p_walk;
    p_walk = p_walk->next;
    counter++;
  }
  previous_node->next = new_node;
  new_node->next = p_walk;
  list->length++;
  return Success;
}

List_ptr map(List_ptr list, Mapper mapper)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    Element map_result = (*mapper)(p_walk->element);
    add_to_list(new_list, map_result);
    p_walk = p_walk->next;
  }
  return new_list;
}

List_ptr filter(List_ptr list, Predicate predicate) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while(p_walk != NULL) 
  {
    int filter_result = (*predicate)(p_walk->element);
    if(filter_result)
      add_to_list(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}

Element reduce(List_ptr list, Element data, Reducer reducer) {
  Node_ptr p_walk = list->first;
  while (p_walk!=NULL)
  {
    data = (*reducer)(data,p_walk->element);
    p_walk = p_walk->next;
  }
  return data;
}
