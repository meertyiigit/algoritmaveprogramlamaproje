#include <stdio.h>

struct Personel {// personel bilgilerini tutmak için bir yapı(struct) tanımlıyoruz.
    int sicil_no; //personel sicil numarası
    char ad[50]; //personel adı(50karakter)
    char soyad[50];//personel soyadı(50karakter)
    int satis_miktari;//satış miktarı
};

int main() {
    struct Personel calisanlar[50];//50 elemanlık bir personel yapı dizisi oluşturur.
    int sayac = 0;//dosyada okunan personel sayısını tutar.
    int en_yuksek = 0;//en yüksek satış miktarını bulmak için başlangıç değerini 0 a eşitler.
    int i;//döngü kontrol değişkeni.

    FILE *dosya_oku = fopen("yillik.dat", "r");//dosyayı okuma modunda açar.
    if (dosya_oku == NULL) return 1;//eğer dosya bulunamazsa programı 1 hatasıyla sonlandırır.
   //verileri dosya bitene kadar döndürür dosya bittiğinde döngüden çıkar.
    while (fscanf(dosya_oku, "%d %s %s %d",
                  &calisanlar[sayac].sicil_no,
                  calisanlar[sayac].ad,
                  calisanlar[sayac].soyad,
                  &calisanlar[sayac].satis_miktari) != EOF) {

        if (calisanlar[sayac].satis_miktari > en_yuksek) {//okunan personelin satış miktarı şu ana kadarki en yüksekten büyükse onu en yüksek değerini günceller.
            en_yuksek = calisanlar[sayac].satis_miktari;
        }
        sayac++;//bir sonraki personel dizisini okumak için dizinin numarasını arttırır.
                  }
    fclose(dosya_oku);//dosyayı kapatır.

    FILE *dosya_yaz = fopen("satislar.dat", "w");//satışlar dosyasını yazma modunda açar.(varsa içeriği temizler,yoksa oluşturur)
    if (dosya_yaz == NULL) return 1;//dosya oluşturulamazsa 1 hatasıyla geri döner.

    for (i = 0; i < sayac; i++) {
        int fark = en_yuksek - calisanlar[i].satis_miktari;//verileri tekrar üzerinden geçer ve en yüksek değerden mevcut satış miktarı arasındaki farkı hesaplar.

        fprintf(dosya_yaz, "%d %s %s ",//verileri (ad,soyad,sicil no)hedef dosyaya yazar.
                calisanlar[i].sicil_no,
                calisanlar[i].ad,
                calisanlar[i].soyad);

        if (fark == 0) {
            fprintf(dosya_yaz, "-en yuksek satis-\n");//fark 0 ise en yüksek satış miktarını yapan kişidir.
        } else {  
            fprintf(dosya_yaz, "%d\n", fark);//eğer fark 0 değilse farkı yazdırır.
        }
    }
    fclose(dosya_yaz);//  yazma işlemi bittiği için dosyayı kapatır.

    return 0;//program sorunsuz bir şekilde tamamlanırsa 0 değeriyle programı sonlandırır.
}
