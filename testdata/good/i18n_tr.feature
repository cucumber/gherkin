# language: tr
# ══════════════════════════════════════════════════════
# Türkçe Gherkin — Tam Anahtar Kelime Rehberi
# Cucumber BDD ile Davranış Odaklı Geliştirme
# ══════════════════════════════════════════════════════

İş Gereksinimi: Türkçe anahtar kelime doğrulama
  Bu özellik dosyası tüm Türkçe Gherkin anahtar
  kelimelerini test eder.

  # ── 1. E-TİCARET: Sipariş Yaşam Döngüsü ──────────

  Arka Plan:
    Diyelim ki mağaza açık ve stokta ürünler var
    Ve ödeme sistemi aktif

  Kural: Sipariş tamamlama kuralları

    Senaryo: Başarılı sipariş tamamlama
      Zaten müşteri giriş yapmış
      Ve sepetinde 2 ürün var
      Eğer müşteri ödeme sayfasına geçerse
      Ve kredi kartı bilgilerini girerse
      O zaman sipariş onaylanmalı
      Ve müşteriye e-posta ile bildirim gitmeli

    Senaryo: Stokta olmayan ürün uyarısı
      Diyelim ki müşteri bir ürünü sepete eklemiş
      Ama ürün stoktan düşmüş
      Şayet müşteri ödeme yapmaya çalışırsa
      O zaman "Ürün stokta kalmadı" uyarısı gösterilmeli
      Ve sepet otomatik güncellenmeli

    Senaryo şablonu: Kargo ücreti hesaplama
      Diyelim ki sepet tutarı <tutar> TL
      Eğer müşteri <şehir> adresine teslimat seçerse
      O zaman kargo ücreti <kargo> TL olmalı

      Örnekler:
        | tutar | şehir    | kargo |
        | 50    | İstanbul | 29    |
        | 200   | Ankara   | 0     |
        | 75    | Trabzon  | 19    |

  # ── 2. FİNANS: Banka Hesap İşlemleri ─────────────

  Kural: Transfer güvenlik kontrolleri

    Önkoşul:
      Halihazırda müşteri internet bankacılığına giriş yapmış

    Senaryo: Günlük transfer limiti aşımı
      Mevcut durumda hesapta 10.000 TL bakiye var
      Ve günlük transfer limiti 5.000 TL
      Eğer hesap sahibi 6.000 TL transfer yapmaya çalışırsa
      O zaman işlem reddedilmeli
      Ve "Günlük limitiniz aşıldı" mesajı gösterilmeli

    Senaryo: Şüpheli işlem tespiti
      Varsayalım ki hesap sahibi her gün ortalama 500 TL harcıyor
      Eğer ki aynı gün içinde 5 farklı ülkeden işlem gelirse
      O zaman hesap geçici olarak dondurulmalı
      Ve güvenlik ekibine otomatik bildirim gitmeli

  # ── 3. SAĞLIK: Hasta Randevu Sistemi ─────────────

  Kural: Randevu yönetim kuralları

    Önceki Durum:
      Önceden hastane randevu sistemi açılmış
      Ve doktor müsaitlik bilgileri güncellenmiş

    Örnek: Acil durum randevusu
      Diyelim ki hasta acil servise başvurdu
      Ve triaj puanı kırmızı
      Şayet hastaya doktor atanırsa
      O zaman muayene süresi 5 dakika içinde başlamalı
      Fakat normal sıra bekleyen hastalar etkilenmemeli

    Örnek: Randevu çakışması kontrolü
      Mevcut durumda doktorun 14:00 randevusu dolu
      Eğer başka bir hasta 14:00 için randevu almaya çalışırsa
      Sonuç olarak en yakın boş saat önerilmeli
      Ancak acil durumlar bu kuraldan muaf olmalı

  # ── 4. GÜVENLİK: Erişim Kontrolü ──────────────

  Kural: Gizli belgelere yalnızca yetki seviyesi yeterli personel erişebilir

    Ön Koşul:
      Halihazırda güvenlik sistemi aktif
      Ve erişim logları kayıt altında

    Senaryo: Yetkisiz erişim denemesi
      Diyelim ki personelin güvenlik seviyesi "gizli"
      Ve belgenin gizlilik seviyesi "çok gizli"
      Eğer personel belgeyi açmaya çalışırsa
      O zaman erişim engellenmelidir
      Ve güvenlik loguna kayıt düşmelidir

    Senaryo: Yetkili erişim ile denetim izi
      Mevcut durumda personelin güvenlik seviyesi "çok gizli"
      Ve belgenin gizlilik seviyesi "çok gizli"
      Eğer personel belgeyi açarsa
      O zaman belge görüntülenmelidir
      Ve erişim kaydı tarih ve saat ile loglanmalıdır

  # ── 5. ENERJİ: SCADA İzleme ─────────────────────

  Kural: Enerji santrali kritik eşik izleme

    Senaryo: Sıcaklık eşiği aşımı
      Diyelim ki reaktör sıcaklığı normal aralıkta
      Ne zaman ki sıcaklık 85 derece değerine ulaşır
      O zaman sarı alarm tetiklenmeli
      Ve operatöre anlık bildirim gitmeli

    Senaryo: Kritik seviye operatör müdahalesiz kalırsa
      Diyelim ki reaktör sıcaklığı 95 derece eşiğini aştı
      Ve sarı alarm 30 saniyedir yanıyor
      Eğer operatör bu süre içinde onay vermezse
      O zaman otomatik soğutma sistemi devreye girmeli
      Ve olay raporu tarih ve operatör kimliğiyle oluşturulmalı

  # ── 6. GÜNLÜK HAYAT: Market Alışverişi ─────────

  İş Kuralı: Market kasa işlemleri

    Senaryo: Sadakat kartı ile indirim
      Zaten müşteri sadakat kartına sahip
      Ve sepette 3 kalem ürün var
      Eğer müşteri kasada sadakat kartını okuttursa
      Böylece toplam tutardan yüzde 5 indirim uygulanmalı
      Ayrıca kalan puan bakiyesi fiş üzerinde gösterilmeli

    Senaryo: Bozuk para üstü hesaplama
      Halihazırda kasada yeterli bozuk para var
      Eğer müşteri 47 TL tutarında alışveriş yapıp 50 TL verirse
      O zaman 3 TL para üstü verilmeli

  # ── 7. EĞİTİM: Öğrenci Kayıt Sistemi ──────────

  Kural: Ders kayıt kuralları

    Senaryo: Kontenjan dolu ders kaydı
      Önceden öğrenci ders seçim dönemine giriş yapmış
      Ve seçmek istediği dersin kontenjanı dolmuş
      Şayet öğrenci bu derse kayıt olmaya çalışırsa
      O zaman "Kontenjan dolmuştur" uyarısı gösterilmeli
      Ama öğrenci bekleme listesine eklenebilmeli

    Senaryo şablonu: Not ortalaması hesaplama
      Varsayalım ki öğrencinin <ders> dersinden notu <not>
      Eğer dönem sonu ortalaması hesaplanırsa
      Böylece genel ortalama <ortalama> olmalı

      Değerler:
        | ders       | not | ortalama |
        | Matematik  | 85  | 82       |
        | Fizik      | 90  | 87       |
        | Kimya      | 75  | 83       |

  # ── 8. ULAŞIM: Toplu Taşıma Kartı ─────────────

  Kural: Toplu taşıma kart işlemleri

    Senaryo: Aktarmalı biniş hakkı
      Diyelim ki yolcu otobüsten inmiş
      Ve kartında aktarma hakkı var
      Hem de son binişten 45 dakika geçmemiş
      Bir de aktarma yapılacak hat tanımlı
      Eğer yolcu metroya binmek için kartını okuttursa
      O zaman biniş ücretsiz olmalı
      Ayrıca kalan aktarma süresi ekranda gösterilmeli

  # ── 9. HUKUK: Sözleşme Yönetimi ───────────────

  Kaide: Sözleşme imza süreçleri

    Durum: Süresi dolmuş sözleşme yenileme
      Biliniyor ki sözleşmenin bitiş tarihi geçmiş
      Ve taraflar yenileme konusunda anlaşmış
      Şayet yeni sözleşme sisteme yüklenirse
      Dolayısıyla eski sözleşme arşive taşınmalı
      Yalnız arşivlenen sözleşme salt okunur olmalı

    Durum: Yetkisiz sözleşme değişikliği
      Biliyoruz ki sözleşme onay sürecinde
      Ve sadece hukuk birimi değişiklik yapabilir
      Eğer yetkisiz bir kullanıcı düzenleme yapmaya çalışırsa
      O zaman değişiklik engellenmelidir
      Lakin kullanıcıya yetki talebi formu gösterilmeli
      Ne var ki mevcut sözleşme içeriği değişmemeli
