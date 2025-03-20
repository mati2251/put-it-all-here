#include "books.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define PROCESS_NUMBER 10
#define LIBRARY_COUNT 10

static struct sembuf sem_buf;

struct program_properties {
    int readers_count;
    int current_readers[PROCESS_NUMBER];
    int process_count;
    int books_count_library;
    int sended_books;
    struct {
        struct book book;
        int how_many_message;
    } books_state[LIBRARY_COUNT];
};

enum process_type {
    READER, WRITER
};

struct process_properties {
    int sem_id;
    int msg_id;
    enum process_type type;
    int process_number;
};

struct message {
    long mtype;
    struct book mvalue;
};

void sem_op(int sem_id, int sem_num, short value) {
    sem_buf.sem_num = sem_num;
    sem_buf.sem_op = value;
    sem_buf.sem_flg = 0;
    if (semop(sem_id, &sem_buf, 1) == -1) {
        perror("Raising the semaphore");
        exit(1);
    }
}

void sem_set_value(int sem_id, int sem_num, int value) {
    if (semctl(sem_id, sem_num, SETVAL, value) == -1) {
        perror("Setting the semaphore value");
        exit(1);
    }
}

void add_send_book_to_state(struct book book, struct program_properties *program_properties) {
    for (int i = 0; i < program_properties->books_count_library; i++) {
        if (program_properties->books_state[i].book.id == book.id) {
            program_properties->books_state[i].how_many_message++;
            return;
        }
    }
    program_properties->books_state[program_properties->books_count_library].book = book;
    program_properties->books_state[program_properties->books_count_library].how_many_message = 1;
    program_properties->books_count_library++;
}

void remove_book_from_libary(struct book book, struct program_properties *program_properties) {
    for (int i = 0; i < LIBRARY_COUNT; i++) {
        if (program_properties->books_state[i].book.id == book.id) {
            for (int j = i; j < LIBRARY_COUNT - 1; j++) {
                program_properties->books_state[j] = program_properties->books_state[j + 1];
            }
            program_properties->books_count_library--;
            break;
        }
    }
}

void sub_send_book_from_state(struct book book, struct program_properties *program_properties) {
    for (int i = 0; i < LIBRARY_COUNT; i++) {
        if (book.id == program_properties->books_state[i].book.id) {
            program_properties->books_state[i].how_many_message--;
            if (program_properties->books_state[i].how_many_message == 0) {
                remove_book_from_libary(book, program_properties);
            }
            return;
        }
    }
}


void snd_msg(struct process_properties *process_p, struct message msg, struct program_properties *program_p) {
    if (msgsnd(process_p->msg_id, &msg, sizeof(msg.mvalue), 0) == -1) {
        printf("%s %s %d %ld \n", msg.mvalue.title, msg.mvalue.author, msg.mvalue.year, msg.mtype);
        exit(1);
    }
    add_send_book_to_state(msg.mvalue, program_p);
    printf("Process %d send book %s %s to %ld\n", process_p->process_number, msg.mvalue.title, msg.mvalue.author, msg.mtype);
}

void rcv_msg(struct process_properties *process_p, struct program_properties *program_p) {
    struct message msg;
    if (msgrcv(process_p->msg_id, &msg, sizeof(msg.mvalue), process_p->process_number + 1, IPC_NOWAIT) == -1) {
        printf("Process %d didn't read the book\n", process_p->process_number);
        return;
    }
    sub_send_book_from_state(msg.mvalue, program_p);
    printf("Process %d received book %s %s\n", process_p->process_number, msg.mvalue.title, msg.mvalue.author);
}

void add_reader(struct program_properties *program_p, struct process_properties process_p) {
    sem_op(process_p.sem_id, 0, -1);
    program_p->current_readers[program_p->readers_count] = process_p.process_number;
    program_p->readers_count++;
    sem_op(process_p.sem_id, 0, 1);
}

void remove_reader(struct program_properties *program_p, struct process_properties process_p) {
    sem_op(process_p.sem_id, 0, -1);
    for (int i = 0; i < program_p->readers_count; i++) {
        if (program_p->current_readers[i] == process_p.process_number) {
            for (int j = i; j < program_p->readers_count - 1; j++) {
                program_p->current_readers[j] = program_p->current_readers[j + 1];
            }
            program_p->readers_count--;
            break;
        }
    }
    sem_op(process_p.sem_id, 0, 1);
}

void reader_operation(struct program_properties *program_p, struct process_properties process_p) {
    sem_op(process_p.sem_id, 1, -1);
    sem_op(process_p.sem_id, 0, -1);
    printf("Process %d is reader now\n", process_p.process_number);
    rcv_msg(&process_p, program_p);
    sem_op(process_p.sem_id, 0, 1);
    usleep(50000);
    sem_op(process_p.sem_id, 1, 1);
}

void writer_operation(struct program_properties *program_p, struct process_properties process_p) {
    sem_op(process_p.sem_id, 1, -PROCESS_NUMBER);
    sem_op(process_p.sem_id, 0, -1);
    printf("Books in Library: %d\n", program_p->books_count_library);
    if (program_p->readers_count != 0 && program_p->books_count_library < LIBRARY_COUNT) {
        printf("Process %d is writer now \n", process_p.process_number);
        struct book book = books[program_p->sended_books];
        program_p->sended_books++;
        for (int i = 0; i < program_p->readers_count; i++) {
            struct message msg = {program_p->current_readers[i] + 1, book};
            snd_msg(&process_p, msg, program_p);
            usleep(100000);
        }
    }
    sem_op(process_p.sem_id, 0, 1);
    sem_op(process_p.sem_id, 1, PROCESS_NUMBER);
}

void process(struct program_properties *program_p, struct process_properties process_p) {
    srand(time(NULL) + process_p.process_number + getpid());
    enum process_type old_type = WRITER;
    sem_op(process_p.sem_id, 0, -1);
    process_p.process_number = program_p->process_count;
    program_p->process_count++;
    sem_op(process_p.sem_id, 0, 1);
    printf("Process number %d started work \n", process_p.process_number);
    while (program_p->sended_books < NUMBER_OF_BOOKS) {
        if (process_p.type == READER) {
            if (old_type == WRITER) {
                add_reader(program_p, process_p);
            }
            reader_operation(program_p, process_p);
        } else {
            if (old_type == READER) {
                remove_reader(program_p, process_p);
            }
            writer_operation(program_p, process_p);
        }
        old_type = process_p.type;
        process_p.type = rand() % 2;
    }
    while(program_p->books_count_library != 0){
        reader_operation(program_p, process_p);
    }
    printf("exit %d\n", process_p.process_number);
    exit(0);
}

int create_semaphores() {
    int number_of_semaphores = 2;
    int sem_id = semget(47867, number_of_semaphores, IPC_CREAT | 0600);
    if (sem_id == -1) {
        perror("Create semaphore arrays");
        exit(1);
    }

    return sem_id;
}

void initial_value_semaphores(int sem_id) {
    sem_set_value(sem_id, 0, 1);
    sem_set_value(sem_id, 1, PROCESS_NUMBER);
}

void removed_message(int msg_id) {
    msgctl(msg_id, IPC_RMID, 0);
}

int create_shared_memory() {
    int shm_id = shmget(47867, sizeof(struct program_properties), IPC_CREAT | 0600);
    if (shm_id == -1) {
        perror("Create shared memory");
        exit(1);
    }
    removed_message(shm_id);
    return shm_id;
}

struct program_properties *get_shared_memory(int shm_id) {
    struct program_properties *properties;
    properties = (struct program_properties *) shmat(shm_id, NULL, 0);
    properties->readers_count = 0;
    properties->process_count = 0;
    properties->sended_books = 0;
    properties->books_count_library = 0;
    return properties;
}

int create_communication_queue() {
    int msg_id = msgget(47867, IPC_CREAT | IPC_EXCL | 0600);
    removed_message(msg_id);
    msg_id = msgget(47867, IPC_CREAT | IPC_EXCL | 0600);
    if (msg_id == -1) {
        msg_id = msgget(47867, IPC_CREAT | 0600);
        if (msg_id == -1) {
            perror("Create a message queue");
            exit(1);
        }
    }
    return msg_id;
}

void create_processes(struct program_properties *program_p, struct process_properties *process_p) {
    for (int i = 0; i < PROCESS_NUMBER; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Create a process");
            exit(1);
        } else if (pid == 0) {
            process_p->type = i % 2;
            process(program_p, *process_p);
        }
    }
}

void wait_for_processes() {
    for (int i = 0; i < PROCESS_NUMBER; i++) {
        wait(NULL);
    }
}

int main() {
    printf("Program started\n");
    int shm_id = create_shared_memory();
    int msg_id = create_communication_queue();
    int sem_id = create_semaphores();
    initial_value_semaphores(sem_id);
    struct program_properties *program_p = get_shared_memory(shm_id);
    struct process_properties *process_p;
    process_p->sem_id = sem_id;
    process_p->msg_id = msg_id;
    process_p->type = WRITER;
    create_processes(program_p, process_p);
    wait_for_processes();
    removed_message(process_p->msg_id);
    return 0;
}
