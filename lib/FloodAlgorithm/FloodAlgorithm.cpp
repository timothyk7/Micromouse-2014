/*
 @author Timothy Kua and Joe Kang
*/
#include "FloodAlgorithm.h"

/*Stack Methods*/
void FloodAlgorithm::push(bool next)
{
  if(!next)
  {
    //ASSERT(c_stack_size+1<STACK_CAP);
    c_stack[c_stack_size] = node;
    c_stack_size++;
  }
  else
  {
    //ASSERT(n_stack_size+1<STACK_CAP);
    n_stack[n_stack_size] = node;
    n_stack_size++;
  }
}


void FloodAlgorithm::pop(bool next)
{
  if(!next)
  {
    //ASSERT(c_stack_size-1>=0);
    node = c_stack[c_stack_size-1];
    c_stack_size--;
  }
  else
  {
    //ASSERT(n_stack_size-1>=0);
    node = n_stack[n_stack_size-1];
    n_stack_size--;
  }
}

int FloodAlgorithm::size(bool next)
{
  if(next)
    return n_stack_size;
  else
    return c_stack_size;
}
