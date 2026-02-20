# tinyml-tensor-c

C dilinde gömülü sistemler (TinyML) için dinamik tensör ve quantization kütüphanesi.

\# TinyML: C Tabanlı Dinamik Tensör ve Quantization Kütüphanesi 🚀



Bu proje, bellek (RAM) kapasitesi son derece kısıtlı olan gömülü sistemler (örn: ESP32, Arduino) üzerinde Yapay Zeka (TinyML) modellerini çalıştırabilmek amacıyla geliştirilmiş dinamik bir Tensör yönetim kütüphanesidir. 



Proje, standart yapay zeka tensörlerini düşük seviyeli (low-level) C programlama dili prensipleriyle yöneterek maksimum bellek optimizasyonu sağlamayı hedefler. Geliştirme sürecinde \*\*Agentic Kodlama\*\* yaklaşımı benimsenmiş ve \*\*Gemini 3.1 Pro\*\* dil modeli bir yazılım mimarisi asistanı olarak kullanılmıştır.



\## 📌 Proje Özellikleri ve Mimari Kararlar



\* \*\*Bellek Optimizasyonu (Union Kullanımı):\*\* 32-bit Float, 16-bit Float ve 8-bit Integer veri tiplerinin bellekte aynı adresi paylaşması için `union` yapısı kullanılmıştır. Bu sayede bellek israfının önüne geçilmiştir.

\* \*\*Dinamik Tip Dönüşümü (Type Casting):\*\* Tensör okuma işlemleri sırasında `enum` tabanlı kontrol mekanizması ile tek bir bellek adresinden dinamik tip dönüşümleri (Type Casting) yapılmıştır.

\* \*\*Min-Max Quantization (Nicemleme):\*\* 32-bit ondalıklı sayıların ağırlıkları (weights), model davranışını koruyarak 8-bit tam sayılara (Int8) sıkıştırılmış ve bellek kullanımında tam 4 kat (%75) tasarruf sağlanmıştır.

\* \*\*Güvenli Bellek Yönetimi:\*\* Dinamik bellek tahsisi (`malloc`) ile matrisler tek boyutlu ardışık bellek blokları olarak ayrılmış ve işlem bitiminde `free()` fonksiyonu ile \*Memory Leak (Bellek Sızıntısı)\* tamamen engellenmiştir.



\## 🛠️ Geliştirme Ortamı ve Araçlar



\* \*\*Programlama Dili:\*\* C

\* \*\*IDE:\*\* CLion (JetBrains)

\* \*\*Derleyici:\*\* GCC / CMake

\* \*\*Yapay Zeka Asistanı:\*\* Gemini 3.1 Pro (Agentic Kodlama yaklaşımı ile)



\## 🚀 Kurulum ve Çalıştırma



Projeyi bilgisayarınızda derlemek ve test etmek için aşağıdaki adımları izleyebilirsiniz.



1\. Repoyu bilgisayarınıza klonlayın:

&nbsp;  ```bash

&nbsp;  git clone \[https://github.com/KULLANICI\_ADINIZ/tinyml-tensor-c.git](https://github.com/KULLANICI\_ADINIZ/tinyml-tensor-c.git)

&nbsp;  cd tinyml-tensor-c



2\.C kodunu derleyin (GCC kullanarak):

gcc main.c -o tensor\_demo



3.Uygulamayı çalıştırın:

./tensor\_demo



📊 Örnek Çıktı ve Quantization Analizi

Uygulama çalıştığında konsolda 32-bit bir matrisin nasıl 8-bit'e sıkıştırıldığını ve belleğin nasıl optimize edildiğini görebilirsiniz:

--- TinyML Gömülü Sistem Tensör Demosu ---



1\. Orijinal 32-Bit Float Tensor (Bellek: 36 byte)

Tensor Boyutu: 3x3 | Tip: FLOAT32

&nbsp;  7.251    1.234    9.812 

&nbsp;  0.551    8.442    2.100 

&nbsp;  4.881    3.333    5.678 

-----------------------------------



2\. Quantize Edilmiş 8-Bit Int Tensor (Bellek: 9 byte)

Tensor Boyutu: 3x3 | Tip: INT8 (Quantized)

&nbsp;  93       15      127 

&nbsp;   7      109       27 

&nbsp;  63       43       73 

-----------------------------------



Islem tamamlandi. Bellek basariyla temizlendi.

