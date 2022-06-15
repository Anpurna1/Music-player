#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct st
{
    struct st *next;
    struct st *prev;
    char *data;
}node;

node *create_node(char *val)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = strdup(val);
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

node *search_by_pos(node *head, int pos)
{
    int i = 1, count = 1;
    node *tmp = head;

    if (head == NULL)
        return NULL;

    while (head->next != NULL)
    {
        head = head->next;
        count++;
    }

    if (pos > count || pos <= 0 )
    {
        printf("Invalid Position\n");
        return NULL;
    }

    for (i = 1; i < pos; i++)
        tmp = tmp->next;

    return tmp;
}

void play(node *pos)
{
    printf("%s", pos->data);
}

void add_after(node *head, int pos, char *value, FILE *fp)
{
    node *temp, *pos_node = NULL;

    temp = create_node(value);
    pos_node = search_by_pos(head, pos);

    temp->prev = pos_node;
    temp->next = pos_node->next;
    pos_node->next->prev = temp;
    pos_node->next = temp;

    fp= fopen("music.txt", "w"); 
    while (head != NULL)
    {
        fprintf(fp, "%s", head->data);
        head= head->next;
    }
}

void add_before(node *head, int pos, char *value, FILE* fp)
{
    node *temp, *pos_node = NULL;

    temp = create_node(value);
    pos_node = search_by_pos(head, pos);

    temp->prev = pos_node->prev;
    temp->next = pos_node;
    pos_node->prev->next = temp;
    pos_node->prev = temp;

    fp= fopen("music.txt", "w");
    while (head != NULL)
    {
        fprintf(fp, "%s", head->data);
        head= head->next;
    }
}

void add_end(node **head, node **tail, char *value)
{
    node *new_node = create_node(value);

    if (*head == NULL)
    {
        *head = new_node;
        *tail = new_node;
        return;
    }

    new_node->prev = *tail;
    (*tail)->next = new_node;
    *tail = new_node;
}

void delete (node *head, int p)
{
    node *pos_node = NULL;
    pos_node = search_by_pos(head, p);
    node *tmp = pos_node->prev;

    tmp->next = pos_node->next;
    pos_node->next->prev = tmp;
}

void traverse(node *head)
{
    while (head != NULL)
    {
        printf("%s ", head->data);
        head = head->next;
    }
}
int main()
{
    FILE *fp;int p;
    char c,t[40], dump;
    char str[40];
    node *head = NULL, *tail = NULL, *pos = NULL, *curr;
    fp = fopen("music.txt", "r");
    while ((fgets(str, 40, fp)))
        add_end(&head, &tail, str);
    traverse(head);
    do
    {
        printf("\nS start the player.");
        printf("\nJ jump to a specific track.");
        printf("\nN next track.");
        printf("\nP previous track.");
        printf("\nF first track.");
        printf("\nL last track.");
        printf("\nA add a track after an existing track.");
        printf("\nB add a track before an existing track.");
        printf("\n R remove a specific track from the list.");
        printf("\n T to print the playlist.");

        printf("\nEnter your choice: ");
        scanf("%c%c", &c, &dump);

        switch (c)
        {
        case 'S':
            curr = head;
            play(curr);
            break;
        case 'J':
            printf("\nEnter a position: ");
            scanf("%d", &p);
            pos = search_by_pos(head, p);
            play(pos);
            break;
        case 'N':
            if (curr->next == NULL)
            {
                curr = head;
                play(curr);
            }
            else
            {
                play(curr->next);
                curr = curr->next;
            }
            break;

        case 'P':
            if (curr->prev == NULL)
                break;
            else
            {
                play(curr->prev);
                curr = curr->prev;
            }
            break;

        case 'F':
            play(head);
            break;

        case 'L':
            play(tail);
            break;

        case 'A':
            printf("\nEnter a pos: ");
            scanf("%d%c", &p, &dump);
            printf("\nEnter a track: ");
            fgets(t, sizeof(t), stdin);
            add_after(head, p, t, fp);
            break;
        case 'B':
            printf("\nEnter a pos: ");
            scanf("%d%c", &p, &dump);
            printf("\nEnter a track: ");
            fgets(t, sizeof(t), stdin);
            add_before(head, p, t, fp);
            break;

        case 'R':
            printf("\nEnter a pos: ");
            scanf("%d", &p);
            delete (head, p);
            break;

        case 'T':
            traverse(head);
            break;

        case 'Y':
            continue;

        case 'n':
            return 0;

        default:
            break;
        }
        printf("\nDo you want to continue? ");
        scanf("%c", &c);
    } while (c != 'n');

    fclose(fp);

    return 0;
}