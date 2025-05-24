#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node node;
node *head = NULL;

void yazdir();

void basaekle(int veri);

void araekle(int veri, int sira);

void sonaekle(int veri);

void dugumsil();

int main() {
    int secim, veri, sira;
    while (1) {
        printf("\n---Menu---\n");
        printf("1-Listeyi Goruntule\n");
        printf("2-Basa eleman ekle\n");
        printf("3-Araya eleman ekle\n");
        printf("4-Sona eleman ekle\n");
        printf("5-Dugum Sil\n");
        printf("6-Cikis yap\n");
        printf("Secim yapiniz ? \n");
        scanf("%d", &secim);

        switch (secim) {
            case 1: yazdir();
                break;
            case 2:
                printf("Eleman Girin: \n");
                scanf("%d", &veri);
                basaekle(veri);
                break;
            case 3:
                printf("Eleman  giriniz : \n");
                scanf("%d", &veri);
                printf("Kacinci indekse ekleme yapilsin: \n");
                scanf("%d", &sira);
                araekle(veri, sira);
                break;
            case 4:
                printf("Eleman  giriniz : \n");
                scanf("%d", &veri);
                sonaekle(veri);
                break;
            case 5:
                dugumsil();
                break;
            case 6: exit(0);
            default: printf("Secim Error\n");
        }
    }
}

void yazdir() {
    node *temp = head;
    printf("Liste: \n");
    while (temp != NULL) {
        printf("%d ->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void basaekle(int veri) {
    node *yeni = malloc(sizeof(node));
    yeni->data = veri;
    yeni->next = head;
    head = yeni;
}

void araekle(int veri, int sira) {
    node *yeni = malloc(sizeof(node));

    yeni->data = veri;
    yeni->next = NULL;

    if (sira == 0) {
        basaekle(veri);
        return;
    }
    node *temp = head;
    for (int i = 0; i < sira - 1; i++) {
        if (temp == NULL) {
            printf("Girilen degere, liste botuyunda buyuktur\nEkleme yapilmadi\n");
            free(yeni);
        }

        temp = temp->next;
    }
    yeni->next = temp->next;
    temp->next = yeni;

    printf("%d. indekse %d degeri eklendi.\n", sira, veri);
}

void sonaekle(int veri) {
    node *yeni = malloc(sizeof(node));
    yeni->data = veri;
    yeni->next = NULL;

    if (head == NULL) {
        head = yeni;
        return;
    }
    node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = yeni;
}

void dugumsil() {
    int sira;
    printf("Silinecek dugumun indeksi: ");
    scanf("%d", &sira);

    if (head == NULL) {
        printf("Liste bos, silme yapilamaz.\n");
        return;
    }

    if (sira == 0) {
        node *sil = head;
        head = head->next;
        printf("0. indisteki %d silindi.\n", sil->data);
        free(sil);
        return;
    }

    node *temp = head;
    for (int i = 0; i < sira - 1; i++) {
        if (temp == NULL || temp->next == NULL) {
            printf("Gecersiz indeks, silme yapilamadi.\n");
            return;
        }
        temp = temp->next;
    }

    node *sil = temp->next;
    if (sil == NULL) {
        printf("Gecersiz indeks, silme yapilamadi.\n");
        return;
    }

    temp->next = sil->next;
    printf("%d. indisteki %d silindi.\n", sira, sil->data);
    free(sil);
}
