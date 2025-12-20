#include <stdio.h>

struct Personel {
    int sicil_no;
    char ad[50];
    char soyad[50];
    int satis_miktari;
};

int main() {
    struct Personel calisanlar[50];
    int sayac = 0;
    int en_yuksek = 0;
    int i;

    FILE *dosya_oku = fopen("yillik.dat", "r");
    if (dosya_oku == NULL) return 1;

    while (fscanf(dosya_oku, "%d %s %s %d",
                  &calisanlar[sayac].sicil_no,
                  calisanlar[sayac].ad,
                  calisanlar[sayac].soyad,
                  &calisanlar[sayac].satis_miktari) != EOF) {

        if (calisanlar[sayac].satis_miktari > en_yuksek) {
            en_yuksek = calisanlar[sayac].satis_miktari;
        }
        sayac++;
                  }
    fclose(dosya_oku);

    FILE *dosya_yaz = fopen("satislar.dat", "w");
    if (dosya_yaz == NULL) return 1;

    for (i = 0; i < sayac; i++) {
        int fark = en_yuksek - calisanlar[i].satis_miktari;

        fprintf(dosya_yaz, "%d %s %s ",
                calisanlar[i].sicil_no,
                calisanlar[i].ad,
                calisanlar[i].soyad);

        if (fark == 0) {
            fprintf(dosya_yaz, "-en yuksek satis-\n");
        } else {
            fprintf(dosya_yaz, "%d\n", fark);
        }
    }
    fclose(dosya_yaz);

    return 0;
}