#include <stdio.h>
#include <stdlib.h>

#define COUNT 5

struct Data {
    char name[80];
    char address[80];
};

struct Data arr[COUNT];
int length;

void add_entry(){
    if (length == COUNT) {
        printf("\x1b[91mMaximum entries count is %d.\x1b[0m\n\n", COUNT);
        return;
    }
    length++;
    printf("Name: ");
    scanf("%s", arr[length - 1].name);
    printf("Address: ");
    scanf("%s", arr[length - 1].address);
    printf("\n");
}

void view_data(){
    for (int i = 0; i < COUNT; i++) {
        if (arr[i].name[0] == '\0') {
            printf("\x1b[36m%d empty entries.\x1b[0m\n\n", COUNT - i);
            return;
        }
        printf("\x1b[92mName:\x1b[0m %s\n", arr[i].name);
        printf("\x1b[93mAddress:\x1b[0m %s\n", arr[i].address);
    }
    printf("\n");
}

void save_data(){
    FILE *entries = fopen("output.bin", "wb");
    if (entries != NULL) {
        fwrite(arr, sizeof(struct Data), COUNT, entries);
        fclose(entries);
    }
}

void load_data(){
    FILE *entries = fopen("output.bin", "rb");
    if (entries != NULL) {
        fread(arr, sizeof(struct Data), COUNT, entries);
        fclose(entries);
    }
}

int main(){
    length = 0;
    int op;
    do {
        printf("Address Book\n");
        printf("1. Add\n");
        printf("2. View\n");
        printf("3. Save to file\n");
        printf("4. Load from file\n");
        printf("5. Exit\n");
        printf("Select an operation (1 - 5): ");
        scanf("%d", &op);
        printf("\n");
        if (op == 1) add_entry();
        else if (op == 2) view_data();
        else if (op == 3) save_data();
        else if (op == 4) load_data();
    } while (op != 5);
    return 0;
}
