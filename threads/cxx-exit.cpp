#include <pthread.h>

class ThreadExitException
{
  public:
    ThreadExitException (void* return_value) : thread_return_value_ (return_value)
    {
    }

    void* DoThreadExit ()
    {
      pthread_exit (thread_return_value_);
    }
  private:
    // the return value that will be used when exiting the thread
    void* thread_return_value_;
};

void do_some_work ()
{
  while (1) {
    // Do something useful things here ...

    if (should_exit_thread_immediately ())
      throw ThreadExitException (NULL);
  }
}

void* thread_function (void*)
{
  try {
    do_some_work ();
  }
  catch (ThreadExitException ex) {
    // Some function indicated that we should exit the thread
    ex.DoThreadExit();
  }
  return NULL;
}
