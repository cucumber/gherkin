# language: tr
Özellik: E-ticaret platformu uçtan uca sipariş akışı
  Bir e-ticaret mobil uygulamasının altyapı kurulumundan
  ödeme tamamlanmasına kadar tüm akışını doğrular.

  # -- 1. ALTYAPI -- Sistem Ayağa Kalkma -----------

  Kural: Konteyner ortamı hazırlığı

    Ön Koşul:
      Mevcut Docker Engine çalışıyor
      Sistemde docker-compose.yml dosyası tanımlı

    Senaryo: Uygulama konteynerlerinin başlatılması
      Mevcut tüm konteynerler durdurulmuştur
      Ne zaman docker-compose up komutu çalıştırılırsa
      Beklenen veritabanı konteyneri 10 saniye içinde hazır olur
      Ve API konteyneri 15 saniye içinde hazır olur
      Ayrıca Redis önbellek konteyneri başlatılır

    Senaryo: Veritabanı bağlantı havuzu oluşturma
      Mevcut PostgreSQL konteyneri çalışıyor
      Ne zaman API servisi ilk bağlantı talebini gönderirse
      Beklenen 20 bağlantılık havuz oluşturulur
      Gerekli servis veritabanı sorgularını kabul etmeye başlar

    Senaryo: Servis sağlık kontrolü
      Mevcut tüm konteynerler ayakta çalışıyorlar
      Ne zaman yük dengeleyici sağlık kontrolü yaparsa
      Gereken tüm servisler 200 OK yanıtı döner
      Ancak yanıt süresi 500 milisaniyeyi aşarsa uyarı üretilir

  # -- 2. KİMLİK DOĞRULAMA -- Kayıt ve Giriş ------

  İş Kuralı: Kullanıcı kimlik doğrulama akışı

    Senaryo: Yeni kullanıcı kaydı
      Mevcut mobil uygulama açıktır
      Sistemde bu e-posta adresi ile kayıtlı kullanıcı yoktur
      Ne zaman kullanıcı geçerli bilgilerle kayıt formunu gönderirse
      Beklenen hesap oluşturulur
      Ve doğrulama e-postası gönderilir
      Aynı zamanda hoş geldin bildirimi mobil cihaza iletilir

    Senaryo: E-posta doğrulama
      Önceden kullanıcı kayıt olmuştur
      Zaten doğrulama e-postası gönderilmiştir
      Ne zaman kullanıcı e-postadaki bağlantıya tıklarsa
      Beklenen hesap durumu doğrulanmış olarak güncellenir
      Böylece kullanıcı alışverişe başlayabilir

    Senaryo: Mobil uygulama ile oturum açma
      Mevcut kullanıcı hesabı doğrulanmıştır
      Ne zaman kullanıcı doğru e-posta ve şifre ile giriş yaptıysa
      Gereken JWT oturum belirteci oluşturulur
      Ve oturum belirteci güvenli depolamaya kaydedilir
      Bunun üzerine kullanıcı ana sayfaya yönlendirilir

    Senaryo: Üç başarısız giriş denemesi sonrası kilitleme
      Mevcut kullanıcı 2 kez yanlış şifre girmiştir
      Ne zaman üçüncü kez yanlış şifre girilirse
      Gerekli hesap 15 dakika süreyle kilitlenir
      Aynı zamanda kullanıcıya e-posta ile bilgilendirme gönderilir

    Senaryo: Biyometrik giriş
      Halihazırda kullanıcı biyometrik girişi etkinleştirmiştir
      Mevcut cihazda kayıtlı parmak izi vardır
      Eğer kullanıcı parmak izini okutursa
      Gerekli oturum açılır
      Ancak biyometrik doğrulama başarısız olursa şifre ekranı gösterilir

  # -- 3. ÜRÜN -- Listeleme ve Arama ---------------

  Kural: Ürün kataloğu ve arama işlevleri

    Senaryo: Ana sayfa ürün listeleme
      Mevcut kullanıcı oturum açmıştır
      Sistemde 150 aktif ürün kayıtlıdır
      Ne zaman kullanıcı ana sayfayı açarsa
      Beklenen ilk 20 ürün listelenir
      Ve her üründe ad, fiyat ve görsel gösterilir

    Senaryo: Kategoriye göre filtreleme
      Mevcut kullanıcı ürün listesinde
      Sistemde elektronik kategorisinde 45 ürün var
      Eğer kullanıcı elektronik kategorisini seçerse
      Beklenen yalnızca elektronik kategorisi ürünlerin listelenmesidir
      Bu durumda sayfa başlığı elektronik olarak güncellenir

    Senaryo: Stokta olmayan ürünün görüntülenmesi
      Mevcut ürün stok adedi sıfır
      Eğer kullanıcı bu ürünün detay sayfasını açarsa
      Beklenen ürün bilgileri görüntülenir
      Ancak sepete ekle düğmesi pasif olur
      Buna rağmen stok bildirimi almak için e-posta kaydı yapılabilir

    Senaryo taslağı: Fiyat aralığına göre filtreleme
      Mevcut kullanıcı ürün listesinde
      Ne zaman <min> TL ile <maks> TL arasındaki fiyat filtrelerini seçerse
      Beklenen yalnızca bu aralıktaki ürünlerin gösterilmesidir

      Örnekler:
        | min  | maks  |
        | 0    | 100   |
        | 100  | 500   |
        | 500  | 2000  |

  # -- 4. SEPET -- Ürün Ekleme ve Yönetim ----------

  Kural: Alışveriş sepeti yönetimi

    Senaryo: Sepete ilk ürün ekleme
      Mevcut sepet boş
      Sistemde ürün stokta var
      Ne zaman kullanıcı ürünü sepete eklerse
      O zaman sepette 1 ürün görünür
      Ve sepet simgesinde adet göstergesi güncellenir
      Aynı zamanda sepet toplam tutarı hesaplanır

    Senaryo: Aynı üründen birden fazla ekleme
      Mevcut sepette 1 adet kalem var
      Sistemde bu üründen 50 adet stokta var
      Şayet kullanıcı aynı ürünü tekrar sepete eklerse
      Beklenen kalem adedi 2 olarak güncellenir
      Dolayısıyla toplam tutar birim fiyatın 2 katı olur
      Ancak sepete ayrı satır olarak eklenmez

    Senaryo: Stok sınırını aşan adet girişi
      Mevcut sepette 1 adet ürün var
      Sistemde bu üründen 3 adet stokta kaldı
      Şayet kullanıcı adedi 5 olarak güncellemeye çalışırsa
      Gerekli sistem maksimum stok uyarısı gösterir
      Bu durumda adet otomatik olarak 3 ile sınırlandırılır

    Senaryo: Sepetten ürün çıkarma
      Mevcut sepette 3 farklı ürün var
      Eğer kullanıcı bir ürünü sepetten çıkardıysa
      O zaman sepette 2 ürün kalır
      Bunun üzerine toplam tutar yeniden hesaplanır

    Senaryo: Sepet zaman aşımı ve kurtarma
      Daha önce kullanıcı sepete ürün eklemiştir
      Halihazırda son işlemden bu yana 30 dakika geçmiştir
      Ne zaman kullanıcı sepet sayfasını açarsa
      Beklenen sepet içeriği korunur
      Ancak fiyatlar güncel duruma göre yeniden hesaplanır

  # -- 5. ÖDEME -- Mobil Ödeme Akışı ---------------

  İş Kuralı: Mobil ödeme işleme kuralları

    Ön Koşul:
      Sistemde ödeme altyapısı aktiftir
      Mevcut kullanıcı oturum açmıştır
      Zaten sepette en az 1 ürün vardır

    Senaryo: Teslimat adresi seçimi
      Mevcut kullanıcının 2 kayıtlı adresi var
      Ne zaman kullanıcı ödeme sayfasına geçerse
      Beklenen kayıtlı adresler listelenir
      Ve varsayılan adres seçili olarak gösterilir

    Senaryo: Kredi kartı ile başarılı ödeme
      Mevcut sepet tutarı 750 TL
      Önceden kullanıcı teslimat adresini seçmiştir
      Ne zaman kullanıcı geçerli kredi kartı bilgilerini girip ödemeyi onaylarsa
      Beklenen ödeme başarılı olarak işlenir
      Gereken sipariş numarası oluşturulur
      Ve sipariş onay e-postası gönderilir
      Aynı zamanda mobil bildirim iletilir
      Bunun ardından sepet temizlenir

    Senaryo: Yetersiz bakiye ile ödeme reddi
      Mevcut sepet tutarı 2500 TL
      Eğer kullanıcı yetersiz bakiyeli kart ile ödeme yapmaya çalışırsa
      Beklenen sonuç ödemenin reddedilmesidir
      Fakat kullanıcının sepet içeriği korunur
      Ve farklı ödeme yöntemi seçeneği sunulur

    Senaryo: 3D Secure doğrulama
      Mevcut sepet tutarı 1500 TL
      Ne zaman kullanıcı ödemeyi onaylarsa
      Gerekli 3D Secure doğrulama sayfası açılır
      Ne zaman kullanıcı SMS kodunu doğru girerse
      Beklenen ödeme onaylanır
      Böylece sipariş oluşturulur

    Senaryo: 3D Secure zaman aşımı
      Mevcut 3D Secure doğrulama sayfası açılmıştır
      Halihazırda 5 dakika geçmiştir ve kod girilmemiştir
      Eğer doğrulama süresi dolarsa
      Beklenen işlem iptal edilir
      Ancak kullanıcı ödemeyi tekrar deneyebilir
      Aynı zamanda sepet içeriği ve adres bilgisi korunur

    Senaryo şablonu: Taksitli ödeme hesaplama
      Mevcut sepet tutarı <tutar> TL
      Eğer kullanıcı <taksit> taksit seçeneğini tercih ederse
      Beklenen aylık taksit tutarı <aylik> TL olarak gösterilir
      Böylece toplam ödenecek tutar <toplam> TL olarak gösterilir

      Değerler:
        | tutar | taksit | aylik  | toplam |
        | 3000  | 3      | 1000   | 3000   |
        | 3000  | 6      | 530    | 3180   |
        | 3000  | 9      | 367    | 3303   |
        | 3000  | 12     | 290    | 3480   |

    Senaryo: Mobil cüzdan ile hızlı ödeme
      Mevcut kullanıcının mobil cüzdanı tanımlıdır
      Zaten cüzdanda kayıtlı kart vardır
      Ne zaman kullanıcı tek dokunuşla öde seçeneğini kullanırsa
      Gerekli biyometrik doğrulama istenir
      Şayet kullanıcı parmak izini onayladıysa
      Gereken ödeme işlenir
      Böylece sipariş anında oluşturulur

  # -- 6. SİPARİŞ SONRASI -- Kargo ve Bildirim ----

  Kural: Sipariş sonrası süreç yönetimi

    Senaryo: Sipariş durum bildirimi
      Önceden sipariş başarıyla oluşturulmuştur
      Ne zaman sipariş durumu hazırlanıyor olarak güncellenirse
      O zaman kullanıcıya mobil bildirim gönderilir
      Ayrıca sipariş takip sayfasında durum güncellenir

    Senaryo: Kargoya teslim bildirimi
      Önceden sipariş hazırlanmıştır
      Ne zaman kargo firması siparişi teslim alırsa
      Beklenen kargo takip numarası oluşturulur
      Ve kullanıcıya takip bağlantısı bildirimi gönderilir
      Bunun üzerine tahmini teslimat tarihi hesaplanır

    Senaryo: Başarılı teslimat onayı
      Mevcut sipariş kargoda
      Ne zaman kargo firması teslim edildi bilgisini gönderdiyse
      Beklenen sipariş durumu teslim edildi olarak güncellenir
      Aynı zamanda iade süresi başlangıç tarihi kaydedilir
      Bunun üzerine kullanıcıya değerlendirme daveti gönderilir
