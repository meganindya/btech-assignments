/*
    Program to create an image viewer allowing
    insertion, deletion, display previous, display
    next image
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

typedef struct listnode{
    char name[128];
    struct listnode *prev;
    struct listnode *next;
}   node;

int exists(char *);
void ins(node **, char *, int, int *);
void del(node **, char*, int *);
void display(node *, int);
void show(node *, int);
void slide(char *);

int main(int argc, char *argv[]){
	gtk_init (& argc, & argv);
    int choice, pos, count = 0; char filename[128];
    node *head = NULL;

    clear(); loop:
    display(head, count);
    printf("\n=====\nPick");
    printf("\n  1 to INSERT image into Viewer");
    printf("\n  2 to DELETE image into Viewer");
    printf("\n  3 to Show Current");
    printf("\n  4 to Show Previous");
    printf("\n  5 to Show Next");
    printf("\n 0 to EXIT");
    printf("\n Enter : ");
    scanf("%d", &choice);

    if(choice == 0)     return 0;
    switch(choice){
        case 1:
            printf("\n Enter file name of image : ");
            scanf("%s", filename);
            if(exists(filename) == 0){
                clear();
                printf("\"%s\" NOT FOUND!\n", filename);
                break;
            }
            printf(" Enter insert position : ");
            scanf("%d", &pos); clear();
            ins(&head, filename, pos - 1, &count);
            break;
        case 2:
            if(count == 0){  clear(); printf("Nothing to delete\n"); break;}
            printf("\n Enter file name of image : ");
            scanf("%s", filename); clear();
            del(&head, filename, &count);
            break;
        case 3:
			clear();
			if(count != 0)	show(head, count);
            break;
        case 4:
            clear();
            if(count != 0){
                head = head -> prev;
                show(head, count);
            }
            break;
        case 5:
            clear();
            if(count != 0){
                head = head -> next;
                show(head, count);
            }
        default:
            clear(); printf("\nINVALID entry! Retry\n");
    }
    goto loop;
}

int exists(char *fname){
    if(access(fname, F_OK) != -1)   return 1;
    else                            return 0;
}

void ins(node **h, char *fname, int pos, int *count){
    if(pos < 0)         { printf("INVALID position! Retry\n"); return;   }
    if(pos > (*count))  { printf("INSERTING at end\n"); pos = *count;}
    printf("\"%s\" INSERTED at Position %d\n\n", fname, pos + 1);
    node *current = *h, *temp = (node *) malloc(sizeof(node));
    strcpy(temp -> name, fname);    (*count)++;

    if(pos == 0){
        if(*h == NULL){
            *h = temp; temp -> next = *h; temp -> prev = *h;
        }
        else{
            temp -> next = *h; *h = temp; temp -> next -> prev = temp;
            int z = (*count) - 1;
            while(--z)  current = current -> next;
            temp -> prev = current; current -> next = temp;
        }
        return;
    }
    while(--pos)    current = current -> next;
    temp -> next = current -> next;
    current -> next -> prev = temp;
    temp -> prev = current;
    current -> next = temp;
}

void del(node **h, char *fname, int *count){
    node *current = *h;
    int temp = *count, f = 0;
    while(temp){
        if(strcmp(fname, current -> name) == 0) { f = 1; break; }
        current = current -> next; temp--;
    }
    if(f == 0)  {   printf("\"%s\" NOT Found!\n", fname); return;   }
    if(*count == 1) *h = NULL;
    else if(temp == 1 && (*count) != 1){
        current -> prev -> next = *h; node *ext = *h;
        ext -> prev = current -> prev;
    }
    else{
        current -> prev -> next = current -> next;
        current -> next -> prev = current -> prev;
        if(temp == *count)  *h = current -> next;
    }
    (*count)--; free(current);
    printf("\"%s\" DELETED\n\n", fname);
}

void display(node *h, int count){
    if(count != 0)  printf("Number of images : %d\n--\n", count);
    if(count == 0)  {   printf("-- Empty List\n"); return; }
    node *current = h;
    while(count--){
        printf(" %s\n", current -> name);
        current = current -> next;
    }
}

void show(node *h, int count){
	node *current = h;
    slide(current -> name);
}

void slide(char *fname){
	GtkWidget * window;
	GtkWidget * image;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);
	gtk_window_set_title (GTK_WINDOW (window), "SLIDESHOW");
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 2);

	image = gtk_image_new_from_file (fname);
	gtk_container_add (GTK_CONTAINER (window), image);

	g_signal_connect_swapped (G_OBJECT (window), "destroy",
	G_CALLBACK (gtk_main_quit), G_OBJECT (window));

	gtk_widget_show_all (window);
	gtk_main ();
}
