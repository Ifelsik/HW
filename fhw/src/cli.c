#include "../include/cli.h"

void cli(User_t *user, Student_t **students_list_ptr, Book_t **books_list_ptr) {
    /* inits required */
    char msg[64];
    sprintf(msg, "'cli': Logged as '%s'", user->login);
    log_msg(msg);
    // if (NULL == user) {
    //     err_msg("Wrong login or password. Please, try again!");
    //     return;
    // }
    if (user->books_access && !user->students_access) {
        cli_booksMenu(books_list_ptr, students_list_ptr);
        printf("Exit...\n");
        return;
    }
    if (!user->books_access && user->students_access) {
        cli_studentsMenu(students_list_ptr);
        printf("Exit...\n");
        return;
    }
    int opt;
    getc(stdin);  // retarded thing
    do {
        printf("Menu. Select option\n");
        printf("1. Books\n");
        printf("2. Students\n");
        printf("0. Shut down\n");
        
        fflush(stdin);
        opt = getc(stdin);
        fflush(stdin);
        switch (opt) {
            case '0': 
                printf("Exit...\n");
                return;
            case '1':
                cli_booksMenu(books_list_ptr, students_list_ptr);
                break;
            case '2':
                cli_studentsMenu(students_list_ptr);
                break;
            default:
                printf("Unsupported operation! Try again\n");
        }
    } while (opt != '0');
}

void cli_studentsMenu(Student_t **students_list_ptr) {
    printf("Students. Select the option:\n");
    printf("1. add student\n");
    printf("2. delete student\n");
    printf("3. edit student\n");
    printf("4. show student's info\n");
    printf("5. search by surname\n");
    printf("0. to return\n");
    int opt;
    char *buffer = (char*) calloc(BASE_STRING_LEN, sizeof(char));
    if (NULL == buffer) {
        err_msg("'cli_studentsMenu': 'buffer' calloc err");
        log_msg("'cli_studentsMenu': 'buffer' calloc err");
    }
    do {
        opt = getc(stdin);
        fflush(stdin);
        switch (opt) {
            case '0': return;
            case '1':
                student_add(students_list_ptr);
                break;
            case '2':
                printf("Enter record book:\n");
                scanf("%s", buffer);
                student_del(students_list_ptr, buffer);
                break;
            case '3':
                printf("Enter record book:\n");
                scanf("%s", buffer);
                student_edit(*students_list_ptr, buffer);
                break;
            case '4':
                printf("Enter record book:\n");
                scanf("%s", buffer);
                student_info(*students_list_ptr, buffer);
                break;
            case '5':
                printf("Enter surname:\n");
                scanf("%s", buffer);
                student_findBySurname(*students_list_ptr, buffer);
                break;
            default:
                printf("Unsupported operation! Try again\n");
        }
    } while(opt != '0'); 
    free(buffer);
}

void cli_booksMenu(Book_t **books_list_ptr, Student_t **students_list_ptr) {
    printf("Books. Select the option:\n");
    printf("1. add book\n");
    printf("2. delete book\n");
    printf("3. show info about book\n");
    printf("4. show info about all books\n");
    printf("5. edit book\n");
    printf("6. give a book to a student\n");
    printf("7. take a book from a student\n");
    printf("0. to return\n");

    int opt;
    unsigned long long isbn;
    char *buffer = (char*) calloc(BASE_STRING_LEN, sizeof(char));
    if (NULL == buffer) {
        err_msg("'cli_studentsMenu': 'buffer' calloc err");
        log_msg("'cli_studentsMenu': 'buffer' calloc err");
    }
    do {
        opt = getc(stdin);
        fflush(stdin);
        switch (opt) {
            case '0': return;
            case '1':
                book_add(books_list_ptr);
                break;
            case '2':
                printf("Enter isbn:\n");
                scanf("%llu", &isbn);
                book_del(books_list_ptr, isbn);
                break;
            case '3':
                printf("Enter isbn:\n");
                scanf("%llu", &isbn);
                book_info(*books_list_ptr, isbn);
                break;
            case '4':
                book_infoAll(*books_list_ptr);
                break;
            case '5':
                printf("Enter isbn:\n");
                scanf("%llu", &isbn);
                book_edit(*books_list_ptr, isbn);
                break;
            case '6':
                printf("Enter record book:\n");
                scanf("%s", buffer);
                printf("Enter isbn:\n");
                scanf("%llu", &isbn);
                studentbook_takeBook(*students_list_ptr, *books_list_ptr,
                            buffer, isbn);
                break;
            case '7':
                printf("Enter record book:\n");
                scanf("%s", buffer);
                printf("Enter isbn:\n");
                scanf("%llu", &isbn);
                studentbook_returnBook(*students_list_ptr, *books_list_ptr,
                            buffer, isbn);
                break;
            default:
                printf("Unsupported operation! Try again\n");
        }
    } while (opt != '0');

    free(buffer);
}
