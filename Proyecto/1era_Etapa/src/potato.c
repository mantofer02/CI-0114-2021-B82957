/*Copyright 2021 Marco Ferraro*/

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define LEFT -1
#define RIGHT 1
#define ALLOCATION_ERROR -1
#define THREAD_CREATION_ERROR -2

/**
 * @brief Shared data structure
 */
typedef struct {
  size_t thread_count;
  int user_potato_value;
  int game_direction;
  int potato_value;
  int active_players;
  sem_t* sem_array;
} shared_data_t;

/**
 * @brief Private data structure for each thread 
 */
typedef struct {
  int thread_id;
  bool playing;
  shared_data_t* shared_data;
} private_data_t;

/**
 * @brief Method for thread creation
 * @param shared_data A pointer to a shared data structure
 * @return 0 if success, ohterwise THREAD_CREATION_ERROR
 */
int create_threads(shared_data_t* shared_data);

/**
 * @brief Method for potato game
 * @details It manages a sem array to allow a circular 
 * game between thread
 * @param data A pointer to a thread private data structure
 * @return NULL
 */
void* game(void* data);

/**
 * @brief Method for collatz conjeture
 * @param n number which collatz shall be applied to
 * @return n/2 if n is even, (3n + 1)/2 if n is odd 
 */
int collatz(int n);

int main(int argc, char ** argv) {
  int error = EXIT_SUCCESS;
  int thread_count, user_potato_value, game_direction;

  thread_count = sysconf(_SC_NPROCESSORS_ONLN);
  user_potato_value = 10;
  game_direction = RIGHT;

  if (argc > 3) {
    thread_count = atoi(argv[1]);
    user_potato_value = atoi(argv[2]);
    if (atoi(argv[3]) == RIGHT || atoi(argv[3]) == LEFT) {
      game_direction = atoi(argv[3]);
    }
  }


  shared_data_t* shared_data = (shared_data_t*)
    calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    shared_data->thread_count = thread_count;
    shared_data->user_potato_value = user_potato_value;
    shared_data->game_direction = game_direction;
    shared_data->potato_value = user_potato_value;
    shared_data->active_players = thread_count;
    shared_data->sem_array = (sem_t*)calloc(thread_count, sizeof(sem_t));

    create_threads(shared_data);

    free(shared_data->sem_array);
    free(shared_data);
  } else {
    fprintf(stderr, "could not allocate shared data memory \n");
    // change value for macro
    error = ALLOCATION_ERROR;
  }
  return error;
}

int create_threads(shared_data_t* shared_data) {
  int error = 0;
  int initial_value = 1;
  pthread_t* threads = (pthread_t*)
    malloc(shared_data->thread_count * sizeof(pthread_t));

  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->thread_count, sizeof(private_data_t));

  if (threads && private_data) {
    for (size_t index = 0; index < shared_data->thread_count; index++) {
      if (index != 0) {
        initial_value = 0;
      }
      sem_init(&shared_data->sem_array[index], 0, initial_value);

      private_data[index].thread_id = index;
      private_data[index].playing = true;
      private_data[index].shared_data = shared_data;

      error = pthread_create(&threads[index], NULL, game, &private_data[index]);

      if (error) {
        fprintf(stderr, "error creating threads \n");
        error = THREAD_CREATION_ERROR;
      }
    }
    for (size_t index = 0; index < shared_data->thread_count; index++) {
      pthread_join(threads[index], NULL);
      sem_destroy(&shared_data->sem_array[index]);
    }
    free(threads);
    free(private_data);
  }
  return error;
}

void* game(void* data) {
  private_data_t* private_data = (private_data_t*) data;
  shared_data_t* shared_data = private_data->shared_data;
  const size_t my_id = private_data->thread_id;
  const size_t thread_count = shared_data->thread_count;
  const int game_direction = shared_data->game_direction;
  int potato_value = 0;
  int next_thread = 0;

  while (shared_data->active_players) {
    sem_wait(&shared_data->sem_array[my_id]);

    if (shared_data->active_players && private_data->playing) {
      printf("Hello from thread %zu\n", my_id);
      potato_value = collatz(shared_data->potato_value);

      if (potato_value == 1) {
        printf("  Potato exploded!!!!!! \n");
        private_data->playing = false;
        shared_data->active_players -= 1;
        shared_data->potato_value = shared_data->user_potato_value
          + shared_data->active_players;
      } else {
        shared_data->potato_value = potato_value;
        printf("  Potato value:  %u\n", shared_data->potato_value);
      }
      printf("  Active players: %u\n", shared_data->active_players);
      printf("\n");
    }
    if (game_direction == RIGHT) {
      sem_post(&shared_data->sem_array[(my_id + 1) % thread_count]);
    } else {
      next_thread = my_id - 1;
      if (next_thread < 0) {next_thread = thread_count - 1;}
      sem_post(&shared_data->sem_array[next_thread]);
    }
  }
  return NULL;
}

int collatz(int n) {
  if (n % 2 == 0) {return n/2;}
  return (3 * n) + 1;
}
