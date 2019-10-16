/*
    Program to create a slideshow of images allowing
    insertion, deletion, and display
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

typedef struct listnode{
    char name[128];
    struct listnode *link;
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
    printf("\n  1 to INSERT image into Slideshow");
    printf("\n  2 to DELETE image into Slideshow");
    printf("\n  3 to START Slideshow");
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
        if(*count == 0) {   *h = temp; temp -> link = *h;   }
        else            {   temp -> link = *h; *h = temp;   }
        return;
    }
    while(--pos)        current = current -> link;
    temp -> link = current -> link;
    current -> link = temp;
}

void del(node **h, char *fname, int *count){
    node *current = *h, *prev;
    int temp = *count, f = 0;
    while(temp){
        if(strcmp(fname, current -> name) == 0) { f = 1; break; }
        prev = current; current = current -> link; temp--;
    }
    if(f == 0)  {   printf("\"%s\" NOT Found!\n", fname); return;   }
    printf("\"%s\" DELETED\n\n", fname);
    if(*count == 1) *h = NULL;
    else if(temp == 1 && (*count) != 1)  prev -> link = *h;
    else            prev -> link = current -> link;
    (*count)--; free(current);
}

void display(node *h, int count){
    if(count != 0)  printf("Number of images : %d\n--\n", count);
    if(count == 0)  {   printf("-- Empty List\n"); return; }
    node *current = h;
    while(count--){
        printf("  %s\n", current -> name);
        current = current -> link;
    }
}

void show(node *h, int count){
	node *current = h;
    while(count--){
        slide(current -> name);
		current = current -> link;
    }
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
