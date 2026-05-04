# language: tr
# ══════════════════════════════════════════════════════════════
# Türkçe Gherkin — Kapsamlı Anahtar Kelime Doğrulama
#
# AMAÇ: Türkçe anahtar kelime çeşitliliğini doğrulama (parser testi).
# Her bölüm kendi alanının doğal dilini kullanır.
#
# Best Practice Prensipleri:
#   - Bildirimsel (NE, NASIL değil)
#   - Senaryo başına tek davranış
#   - Adım başına tek eylem, max 5 adım
#   - Tutarlı zaman kipi
#   - Davranış odaklı, implementasyon bağımsız
# ══════════════════════════════════════════════════════════════

İş Gereksinimi: Türkçe anahtar kelime doğrulama
  Bu dosya Türkçe Gherkin anahtar kelimelerinin
  farklı sektör ve bağlamlarda doğal kullanımını
  doğrular.

  Arka Plan:
    Diyelim ki kullanıcı sisteme giriş yapmıştır
    Ve kullanıcının rolü tanımlıdır

  # ── 1. E-TİCARET ──────────────────────────────

  Kural: Sepet ve sipariş kuralları

    Senaryo: Sepete ürün ekleme
      Mevcut kullanıcının sepeti boştur
      Eğer kullanıcı bir ürünü sepetine eklerse
      O zaman sepet tutarı ürün fiyatı kadar artar
      Ve sepetteki ürün sayısı 1 olur

    Senaryo şablonu: Kargo ücreti hesaplama
      Mevcut sepet toplamı <tutar> TL tutarındadır
      Eğer kullanıcı teslimat adresini seçerse
      O zaman kargo ücreti <kargo> TL olarak hesaplanır

      Örnekler:
        | tutar | kargo |
        | 100   | 35    |
        | 249   | 35    |
        | 300   | 0     |

  # ── 2. ŞİRKET: Çalışan İşlemleri ─────────────

  İş Kuralı: Çalışan izin ve performans yönetimi

    Mevcut Durum:
      Halihazırda çalışan deneme süresini tamamlamıştır
      Ve çalışanın 15 gün yıllık izin hakkı bulunmaktadır

    Örnek: İzin talebi onay akışı
      Zaten çalışan sistem üzerinden izin talebi oluşturmuştur
      Eğer ki yönetici bu talebi onaylarsa
      O zaman izin durumu "Onaylandı" statüsüne geçer
      Ve sistem çalışana bildirim gönderir

    Örnek: Onaylanan izin bordro entegrasyonu
      Zaten çalışanın izin talebi onaylanmıştır
      Ne zaman bordro sistemi günlük senkronizasyonu çalıştırırsa
      O zaman izin bilgisi bordro kaydına yansır
      Ayrıca İK raporlama paneli güncellenir

    Örnek: Kritik proje döneminde izin kısıtlaması
      Mevcut aktif bir kritik proje dönemi tanımlıdır
      Eğer çalışan bu dönemde izin talebi oluşturursa
      O zaman sistem uyarı mesajı gösterir
      Fakat çalışan yönetici onayı ile istisnai izin alabilir

    Örnek: Performans değerlendirme sonucu
      Biliniyor ki çalışan tüm hedeflerini tamamlamıştır
      Hem de müşteri memnuniyet puanı yüzde 92 üzerindedir
      Eğer dönem sonu değerlendirmesi yapılırsa
      Böylece çalışan terfi havuzuna dahil edilir

    Örnek: Disiplin kaydının terfi üzerindeki etkisi
      Mevcut çalışanın aktif bir disiplin kaydı bulunmaktadır
      Eğer dönem sonu değerlendirmesi yapılırsa
      O zaman çalışan terfi havuzuna dahil edilmez
      Ancak çalışan disiplin kararına itiraz edebilir

  # ── 3. FABRİKA: Üretim Hattı ─────────────────

  Kural: Üretim hattı kalite ve güvenlik prosedürü

    Giriş:
      Halihazırda üretim hattı çalışır durumdadır
      Ve sensörler kalibre edilmiştir
      Bir de hata toleransı binde 2 olarak belirlenmiştir

    Durum: Hatalı ürün oranı eşik değeri aşımı
      Mevcut üretim hattı saatte 500 birim üretir
      Ne zaman ki sensör ardışık 5 hatalı ürün tespit ederse
      O zaman üretim hattı otomatik olarak durur
      Bunun üzerine sistem vardiya amirine ve kalite mühendisine bildirim gönderir

    Durum: Planlı bakım sürecinde hat duruşu
      Önceden planlı bakım penceresi tanımlanmıştır
      Eğer üretim hattı bakım süresi içinde durursa
      O zaman otomatik alarm tetiklenmez
      Yalnız bakım süresi aşılırsa sistem uyarı üretir

    Durum: Ham madde stok seviyesi kritik eşik altında
      Önceden belirlenen stok eşiği 2 günlük üretim kapasitesidir
      Ve mevcut alüminyum stoku bu eşiğin altına düşmüştür
      Eğer üretim planında 3 günlük sipariş bekliyorsa
      O takdirde satın alma birimine acil tedarik talebi iletilir
      İlaveten planlama birimi üretim planını yeniden önceliklendirir

  # ── 4. DEVLET: Kamu İhale ─────────────────────

  Madde: Kamu ihale değerlendirme usulü

    Ön Koşul:
      Daha önce ihale ilanı EKAP üzerinden yayımlanmıştır
      Ve teklif verme süresi dolmuştur

    Durum: Tekliflerin değerlendirilmesi
      Sistemde komisyon üyeleri giriş yapmıştır
      Eğer bir istekli belirlenen baraj puanının altında kalırsa
      O zaman komisyon teklifi teknik olarak yetersiz sayar
      Ve komisyon gerekçeli kararı tutanağa işler

    Durum: Yetersiz bulunan isteklinin itiraz süreci
      Zaten isteklinin teklifi yetersiz bulunmuştur
      Eğer istekli 10 iş günü içinde itiraz ederse
      O zaman komisyon itirazı değerlendirmeye alır
      Ancak süresini geçmiş itirazlar işleme alınmaz

    Senaryo taslağı: İhale teminat hesaplama
      Diyelim ki ihale bedeli <bedel> TL olarak belirlenmiştir
      Ve teminat oranı yüzde <oran> olarak uygulanır
      Eğer firma geçici teminat yatırırsa
      O zaman teminat tutarı <teminat> TL olmalıdır

      Değerler:
        | bedel      | oran | teminat  |
        | 1000000    | 3    | 30000    |
        | 5000000    | 3    | 150000   |
        | 10000000   | 3    | 300000   |

  # ── 5. GÜMRÜK: İthalat İşlemleri ─────────────

  Kaide: Gümrük beyanname işlem esasları

    Önkoşul:
      Başlangıçta gümrük bilgi sistemi çevrimiçidir
      Ve güncel döviz kurları sisteme yüklenmiştir

    Senaryo: Yüksek değerli ithalat kontrolü
      Önceden ithalatçı firma beyanname düzenlemiştir
      Ve beyan edilen ürün bedeli 50.000 doların üzerindedir
      Ne zaman ki gümrük müfettişi inceleme başlatırsa
      Buna binaen müfettiş fatura asılları ve menşe belgesi talep eder

    Senaryo: Müfettişin ek süre tanıması
      Kabul edelim ki müfettiş inceleme sırasında eksik belge tespit etmiştir
      Eğer ithalatçı ek süre talep ederse
      O zaman müfettiş 5 iş günü ek süre tanıyabilir
      Lakin bu süre bir defaya mahsus uygulanır

    Senaryo: Kısıtlı ürün ithalatı
      Kabul edelim ki beyan edilen ürün kısıtlı mal listesindedir
      Ve ithalatçının özel izin belgesi bulunmamaktadır
      Eğer ki gümrük kontrolünde bu durum tespit edilirse
      Sonuç olarak ürün gümrükten geçiş izni alamaz
      Ama ithalatçı 10 iş günü içinde gerekli izni sunabilir

  # ── 6. HUKUK: Hizmet Sözleşmesi ──────────────

  Hüküm: Hizmet alım sözleşmesi cezai şartları

    Mukaddime:
      Farz edelim ki taraflar arasında hizmet sözleşmesi akdedilmiştir
      Ve hizmet seviyesi taahhüdü yüzde 99.9 olarak belirlenmiştir

    Vaka: Gecikme cezası uygulaması
      Varsayalım ki hizmet sağlayıcı işi teslim edememiştir
      Ve teslim süresi 15 takvim günü aşılmıştır
      Şayet gecikme mücbir bir sebebe dayanmıyorsa
      Netice itibariyle günlük yüzde 1 oranında gecikme cezası uygulanır

    Vaka: Mücbir sebep istisnası
      Varsayalım ki teslim gecikmesi mücbir sebepten kaynaklanmıştır
      Eğer hizmet sağlayıcı belgelendirme sunarsa
      O zaman gecikme cezası uygulanmaz
      Meğer ki taraflar aksini kararlaştırmışsa

    Vaka: Gecikme nedeniyle fesih hakkı
      Zaten hizmet sağlayıcıya gecikme cezası uygulanmıştır
      Buna ek olarak gecikme 30 takvim gününü aşmıştır
      Şayet işveren sözleşmeyi feshetmek isterse
      Şu halde tek taraflı fesih hakkını kullanabilir

    Vaka: Sözleşme yenileme müzakeresi
      Geçmişte taraflar sözleşmeyi karşılıklı memnuniyetle yürütmüştür
      Ve sözleşmenin bitimine 60 gün kalmıştır
      Şayet yeni dönem koşulları üzerinde uzlaşma sağlanırsa
      Bu durumda sözleşme aynı koşullarla 1 yıl uzatılır

    Vaka: Uzlaşma sağlanamaması durumu
      Geçmişte sözleşme yenileme müzakeresi başlatılmıştır
      Ve taraflar yeni koşullarda uzlaşma sağlayamamıştır
      Eğer sözleşme süresi sona ererse
      Buna mukabil tasfiye süreci başlar

  # ── 7. SAĞLIK: Acil Servis ────────────────────

  Kural: Acil servis triaj ve sevk prosedürü

    Geçmiş:
      Diyelim ki hastane acil servisi 7/24 hizmet vermektedir
      Ve triaj sistemi aktiftir

    Senaryo: Kritik hasta müdahalesi
      Diyelim ki hasta acil servise başvurmuştur
      Ve triaj hemşiresi kırmızı kod belirlemiştir
      Eğer müdahale odası müsaitse
      O zaman hasta derhal müdahale odasına alınır

    Senaryo: Yoğun bakım kapasitesi dolu iken sevk
      Varsayılan olarak hastanenin yoğun bakım kapasitesi 20 yataktır
      Ve mevcut doluluk oranı yüzde 100'dür
      Şayet en yakın uygun hastane belirlenirse
      Bunun üzerine hastane nakil işlemini başlatır
      Ve sistem hasta dosyasını karşı hastaneye aktarır

  # ── 8. PERAKENDE: Sadakat Sistemi ─────────────

  İş Kuralı: Sadakat kartı ve puan kullanımı

    Önceki Durum:
      Zaten müşteri sadakat programına kayıtlıdır
      Ve kartında 500 puan birikmiştir

    Senaryo: Puan ile kısmi ödeme
      Mevcut müşteri kasada ödeme aşamasındadır
      Eğer müşteri ödemenin bir kısmını puanla yapmak isterse
      O zaman puanlar toplam tutardan düşülür
      Ve kalan tutar diğer ödeme yöntemiyle tahsil edilir
      Beklenen işlem fişinde puan indiriminin görülmesidir

    Senaryo: Yetersiz puan ile ödeme denemesi
      Mevcut müşterinin puan bakiyesi sıfırdır
      Eğer müşteri puanla ödeme yapmaya çalışırsa
      O zaman sistem yetersiz puan uyarısı gösterir

    Senaryo: Yetersiz puan sonrası alternatif ödeme yönlendirmesi
      Zaten müşterinin puan ile ödeme denemesi başarısız olmuştur
      Eğer müşteri ödeme ekranında kalırsa
      O zaman sistem müşteriyi farklı ödeme yöntemine yönlendirir
      Aksi halde müşteri sepet sayfasına geri döner
