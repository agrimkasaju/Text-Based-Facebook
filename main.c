/********* main.c ********
    Student Name 	= Agrim Kasaju
    Student Number	= 101280101
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/

    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    int num = 0;
    int exit = 0;
    while (!exit)
    {
        print_menu();
        scanf("%d", &num);

        if (num < 1 || num > 6)
        {
            printf("Invalid choice. Please try again.\n\n");
        }
        else
        {
            char name[30];
            char password[15];

            switch (num)
            {
            case 1:
                printf("Enter a username: ");
                scanf("%29s", name);
                printf("Enter an upto 15 characters password: ");
                scanf("%14s", password);
                users = add_user(users, name, password);
                printf("User Added!\n\n");
                break;
            case 2:
                printf("Enter username to update their password: ");
                scanf("%29s", name);
                user_t *found1 = find_user(users, name);
                if (found1 == NULL)
                {
                    printf("User not found.\n\n");
                    break;
                }
                else
                {
                    printf("Enter a new password that is upto 15 characters: ");
                    scanf("%14s", password);
                    strncpy(found1->password, password, sizeof(found1->password) - 1);
                    found1->password[sizeof(found1->password) - 1] = '\0';
                    printf("Password changed!\n\n");
                    break;
                }
                break;
            case 3:
                printf("Enter username to mange their posts: ");
                scanf("%29s", name);
                user_t *found2 = find_user(users, name);
                if (found2 == NULL)
                {
                    printf("User not found.\n\n");
                }
                else
                {
                    printf("%s's posts\n", found2->username);
                    if (found2->posts == NULL)
                    {
                        printf("No posts available for %s.\n\n", found2->username);
                    }
                    int choice;
                    do
                    {
                        printf("1. Add a post\n");
                        printf("2. Remove a post\n");
                        printf("3. Return to the main menu\n");
                        printf("Your choice: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:
                        {
                            char content[250];
                            printf("Enter your post content: ");
                            scanf(" %[^\n]", content);
                            add_post(found2, content);
                            printf("Post added to your profile.\n\n");
                            display_user_posts(found2);
                            break;
                        }
                        case 2:
                            int post = 0;
                            printf("Which post you want to delete?: ");
                            scanf("%d", &post);
                            if (delete_post(found2, post))
                            {
                                printf("Post %d was deleted successfully!\n\n", post);
                                display_user_posts(found2);
                            }
                            else
                            {
                                printf("\n");
                            }
                            break;
                        case 3:
                            printf("\n");
                            break;
                        default:
                            printf("Invalid choice. \n\n");
                            break;
                        }
                    } while (choice != 3);
                }
                break;
            case 4:
                printf("Enter username to mange their friends: ");
                scanf("%29s", name);
                user_t *found3 = find_user(users, name);
                if (found3 == NULL)
                {
                    printf("User not found.\n\n");
                }
                else
                {
                    printf("%s's friends\n\n", found3->username);
                    int choice;
                    do
                    {
                        printf("1. Display all user's friends\n");
                        printf("2. Add a new friend\n");
                        printf("3. Delete a friend\n");
                        printf("4. Return to the main menu\n");
                        printf("Your choice: ");
                        scanf("%d", &choice);

                        char friends[30];
                        switch (choice)
                        {
                        case 1:
                            if (found3->friends == NULL)
                            {
                                printf("No friends available for %s.\n\n", found3->username);
                            }
                            else
                            {
                                display_user_friends(found3);
                            }
                            break;
                        case 2:
                            printf("Enter a new friend's name: ");
                            scanf("%29s", friends);
                            user_t *found_friend = find_user(users, friends);
                            if (found_friend == NULL)
                            {
                                printf("User not found.\n\n");
                            }
                            else
                            {
                                add_friend(found3, friends);
                                printf("Friend added to the list. \n\n");
                            }
                            break;
                        case 3:
                            display_user_friends(found3);
                            printf("Enter a friend's name to delete: ");
                            scanf("%29s", friends);
                            if (delete_friend(found3, friends))
                            {
                                printf("List of %s's friends:\n\n", friends);
                                display_user_friends(found3);
                            }
                            else
                            {
                                printf("\n");
                            }
                            break;
                        case 4:
                            printf("\n");
                            break;
                        }
                    } while (choice != 4);
                }
                break;
            case 5:
                display_all_posts(users);
                break;
            case 6:
                teardown(users);
                exit = 1;
                break;
            default:
            printf("Invalid choice. \n\n");
            break;
            }
        }
    }
}
