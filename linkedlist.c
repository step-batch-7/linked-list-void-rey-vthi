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

Status add_unique(List_ptr list,Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    if ((*matcher)(p_walk->element,element))
    {
      return Failure;
    }
    p_walk = p_walk->next;
  }
    return add_to_list(list, element);
}

Element remove_from_start(List_ptr list) {
  if(list->first == NULL)
  {
    return NULL;
  }
  Node_ptr new_first_node = list->first->next;
  Element removed_element = list->first->element;
  free(list->first);
  list->first = new_first_node;
  list->length--;
  return removed_element;
}

Element remove_from_end(List_ptr list)
{ 
  if(list->first == NULL)
  {
    return NULL;
  }
  Node_ptr last_node = NULL;
  Node_ptr p_walk = list->first;
  while (p_walk->next != NULL)
  {
    last_node = p_walk;
    p_walk = p_walk->next;
  }
  Element removed_element = p_walk->element;
  free(p_walk);
  list->last= last_node;
  if(last_node != NULL)
    last_node->next = NULL;
  else
    list->first = last_node;
  list->length--;
  return removed_element;
}

Element remove_at(List_ptr list, int position) {
  if(list->first == NULL || position < 0 || position >= list->length){
    return NULL;
  }
  if(position == 0){
    return remove_from_start(list);
  }
  if (position == list->length - 1)
  {
    return remove_from_end(list);
  }
  int counter = 0;
  Node_ptr p_walk = list->first;
  Node_ptr last_node = list->first;
  while (counter < position)
  {
    last_node = p_walk;
    p_walk = p_walk->next;
    counter++;
  }
  last_node->next = p_walk->next;
  list->last = p_walk->next;
  list->length--;
  Element removing_element = p_walk->element;
  free(p_walk);
  return removing_element;
}

Status does_exist(List_ptr list, Element element,Matcher matcher)
{
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    if((*matcher)(element,p_walk->element)){
      return Success;
    }
    p_walk = p_walk->next;
  }
  return Failure;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  if(!does_exist(list,element,matcher))
    return NULL;
  Node_ptr p_walk = list->first;
  for(int position = 0; p_walk!=NULL; position++)
  {
    if((*matcher)(element,p_walk->element))
    {
      return remove_at(list,position);
    }
    p_walk = p_walk->next;
  }
  return NULL;
}
