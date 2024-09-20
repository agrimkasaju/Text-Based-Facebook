/********* definitions.c ********
    Student Name 	= Agrim Kasaju
    Student Number	= 101280101
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *temp = malloc(sizeof(user_t));
   if (temp == NULL)
   {
      return users;
   }

   strcpy(temp->username, username);
   strcpy(temp->password, password);
   temp->friends = NULL;
   temp->posts = NULL;
   temp->next = NULL;

   if (users == NULL || strcmp(username, users->username) < 0)
   {
      temp->next = users;
      return temp;
   }

   user_t *p = users;
   while (p->next != NULL && strcmp(username, p->next->username) >= 0)
   {
      p = p->next;
   }

   temp->next = p->next;
   p->next = temp;

   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   user_t *current = users;
   while (current != NULL)
   {
      if (strcmp(current->username, username) == 0)
      {
         return current;
      }
      current = current->next;
   }
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *friend = malloc(sizeof(friend_t));
   if (friend == NULL)
   {
      return NULL;
   }

   strncpy(friend->username, username, sizeof(friend->username) - 1);
   friend->username[sizeof(friend->username) - 1] = '\0';

   return friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *add = create_friend(friend);
   
   friend_t *current = user->friends;

   if(current == NULL || strcmp(friend, current->username) < 0){
      add->next = user->friends;
      user->friends = add;
      return;
   }

   while(current->next != NULL && strcmp(friend, current->next->username) > 0){
      current = current->next;
   }

   add->next = current->next;
   current->next = add;
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *current = user->friends;
   friend_t *prev = NULL;

   while (current != NULL)
   {
      if (strcmp(current->username, friend_name) == 0)
      {
         if (prev == NULL)
         {
            user->friends = current->next;
         }
         else
         {
            prev->next = current->next;
         }

         return 1;
      }
      prev = current;
      current = current->next;
   }
   return 0;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *post = malloc(sizeof(post_t));
   if (post == NULL)
   {
      return NULL;
   }

   strncpy(post->content, text, sizeof(post->content) - 1);
   post->content[sizeof(post->content) - 1] = '\0';

   return post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *add = create_post(text);
   add->next = user->posts;
   user->posts = add;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t *current = user->posts;
   post_t *prev = NULL;
   int count = 1;

   while (current != NULL && count != number)
   {
      prev = current;
      current = current->next;
      count++;
   }

   if (current == NULL)
   {
      return 0;
   }
   else if (prev == NULL)
   {
      user->posts = current->next;
   }
   else
   {
      prev->next = current->next;
   }

   return 1;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   post_t *current = user->posts;
   int count = 1;
   while (current != NULL)
   {
      printf("%d- %s: %s\n", count, user->username, current->content);
      current = current->next;
      count++;
   }
   printf("\n");
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   friend_t *current = user->friends;
   int count = 1;
   while (current != NULL)
   {
      printf("%d- %s\n", count, current->username);
      current = current->next;
      count++;
   }
   printf("\n");
}

/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   user_t *current = users;
   if (current != NULL)
   {
      display_user_posts(current);
      current = current->next;
   }
   if (current != NULL)
   {
      display_user_posts(current);

      char choice[2];
      printf("Do you want to display next 2 users posts? (Y/N): ");
      scanf("%s", choice);

      if (choice[0] == 'N')
      {
         return;
      }
      else
      {
         display_all_posts(current->next);
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *current_user = users;
   while(current_user != NULL){
      user_t *next_user = current_user->next;

      post_t *current_post = current_user->posts;
      while(current_post != NULL){
         post_t *next_post = current_post->next;
         free(current_post);
         current_post = next_post;
      }

      free(current_user);

      current_user = next_user;
   }
   printf("\nThank you for using Text-Based Facebook\nGoodBye!");
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("Main Menu: \n");
   printf("1. Register a new User \n");
   printf("2. Manage a user's profile (change password) \n");
   printf("3. Manage a user's posts (display/add/remove) \n");
   printf("4. Manage a user's friends (display/add/remove) \n");
   printf("5. Display All Posts \n");
   printf("6. Exit \n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
