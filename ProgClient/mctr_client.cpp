#include "../System/usercall.hpp"

// g++ invoke.cpp main.cpp -pthread -o midd `pkg-config --cflags --libs opencv`

int main(int argc, char const *argv[]) {
  sem_t s0;

  sem_init(&s0, 0, 0);
  init_client();
  sem_wait(&s0);
  return 0;
}
