#include <stdio.h>
#include <stdlib.h>

char fileName[100] = "products.dat";

struct ogr {
    int id;
    char name[50];
    float price;
    int stock;
};
void showMenu();

void addProduct();

void updateProduct();

void getProducts();

void deleteProduct();

int main() {
    showMenu();
    return 0;
}
void showMenu() {
    int choice;
    printf("-----------Welcome---------\n");
    while (1) {
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Show Products\n");
        printf("5. Exit\n");

    printf("enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            deleteProduct();
            break;
        case 4:
            getProducts();
            break;
        case 5:
            exit(0);
            break;
            default:
            printf("wrong choice try again");
    }
  }
 }

void addProduct() {
    FILE *fp = fopen(fileName, "ab");
    if (fp == NULL) {
        printf("File not found! \n");
        return;
    }

    struct ogr ogr;
    printf("Enter id: \n");
    scanf("%d", &ogr.id);
    printf("Enter name: \n");
    scanf("%s", ogr.name);
    printf("Enter price: \n");
    scanf("%f", &ogr.price);
    printf("Enter stock: \n");
    scanf("%d", &ogr.stock);

    if (fwrite(&ogr, sizeof(struct ogr), 1, fp) == 1) {
        printf("Added successful!..\n");
    } else {
        printf("Error! \n");
    }
    fclose(fp);
}


void updateProduct() {
    FILE *fp = fopen(fileName, "rb+");
    if (fp == NULL) {
        printf("File not found! \n");
        return;
    }
    struct ogr ogr;
    int id, found=0;

    printf("Enter id Update: \n");
    scanf("%d", &id);

    while (fread(&ogr, sizeof(struct ogr), 1, fp)) {
        if (ogr.id == id) {
            printf("Currently Stock: %d\n", ogr.stock);
            printf("Enter new stock: \n");
            scanf("%d", &ogr.stock);

            fseek(fp, -sizeof(struct ogr), SEEK_CUR);
            fwrite(&ogr, sizeof(struct ogr), 1, fp);
            printf("Updated successful!..\n");
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printf("Error! \n");
    }
    fclose(fp);
}

void getProducts() {
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        printf("File not found! \n");
        return;
    }
    struct ogr ogr;
    int id, found = 0;

    printf("Enter id: \n");
    scanf("%d", &id);
    while (fread(&ogr, sizeof(struct ogr), 1, fp)) {
        if (ogr.id == id) {
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", ogr.id, ogr.name, ogr.price, ogr.stock);
            found = 1;
            break;
        }
    }
    if (found == NULL) {
        printf("Error! \n");
    }
    fclose(fp);
}

void deleteProduct() {
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL) {
        printf("File not found! \n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("File not found! \n");
        fclose(fp);
        return;
    }

    struct ogr ogr;
    int id, found = 0;

    printf("Enter id: \n");
    scanf("%d", &id);

    while (fread(&ogr, sizeof(struct ogr), 1, fp)) {
        if (ogr.id == id) {
            found = 1;
            continue;
        }
        fwrite(&ogr, sizeof(struct ogr), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    if (found) {
        remove(fileName);
        rename("temp.dat", fileName);
        printf("Deleted Successful! \n");
    }else {
        remove("temp.dat");
        printf("Error!..\n");
    }
}
