================================================================================
  PANDUAN MENAMBAH PORTFOLIO BARU - portofolio Fauzan
================================================================================

RINGKASAN PENTING
-----------------
Untuk menambah 1 project portfolio (geser kiri/kanan + teks nomor project):

  WAJIB ubah  : index.html (2 tempat) + simpan gambar di folder images/
  OPSIONAL    : index.html (modal View & Download, link download .ino/schematic)
  FILE ARDUINO: arduino/ dan arduino/schematics/

  script.js   : UNTUK GESER PORTFOLIO BIASANYA TIDAK PERLU DIUBAH / DITAMBAH
                Script sudah menghitung jumlah item otomatis dari HTML.

Kenapa script.js tidak perlu diubah?
  Di bawah, maxIndex = Math.min(jumlah gambar carousel, jumlah portfolio-detail) - 1
  Jadi kalau kamu tambah portfolio ke-9 di HTML (detail + 1 gambar), geser otomatis
  sampai nomor 09 tanpa mengubah angka di JavaScript.

================================================================================
  CHECKLIST MENAMBAH PROJECT BARU (contoh: PORTFOLIO 09)
================================================================================

[1] index.html - BLOK TEKS (salin dari portfolio 08, ubah isinya)

    Cari: <div class="portfolio-detail"> ... numb">08 ... </div>
    Salin seluruh blok itu, tempel SETELAH portfolio 08, ubah jadi 09:

    <div class="portfolio-detail">
        <p class="numb">09</p>
        <h3>NAMA PROJECT KAMU</h3>
        <p>Deskripsi singkat project.</p>
        <div class="tech">
            <p>Bahan-bahan / tech stack:</p>
            <p>ESP32 X1</p>
        </div>
        <div class="live-github">
            <a href="arduino/nama-file.ino" download>
                <i class='bx bx-download'></i><span>Download Source</span>
            </a>
            <a href="#" onclick="openModal('nama-project-modal')">
                <i class='bx bx-images'></i><span>View & Download</span>
            </a>
            <a href="arduino/schematics/nama-skema.png" download>
                <i class='bx bx-image'></i><span>Download Schematic</span>
            </a>
        </div>
    </div>

    (Tombol di live-github boleh dipilih: cukup yang kamu butuh.)

[2] index.html - GAMBAR CAROUSEL (wajib, 1 gambar per portfolio)

    Cari bagian:
        <div class="portfolio-carousel">
            <div class="img-slide">

    Di DALAM img-slide, tambah SATU blok di paling bawah (urutan = nomor project):

        <div class="img-item">
            <img src="images/portofolio9.jpeg" alt="Portfolio 09">
        </div>

    Simpan file foto di:  c:\portofolio\images\portofolio9.jpeg

[3] File project (kalau ada download)

    Kode Arduino :  arduino\nama-file.ino
    Skematik     :  arduino\schematics\nama-skema.png

[4] Modal View & Download (OPSIONAL - hanya kalau pakai tombol itu)

    Salin blok modal yang sudah ada (misalnya luminoalert-modal), ubah:
    - id modal unik:  id="nama-project-modal"
    - onclick tombol: openModal('nama-project-modal')
    - src gambar di dalam modal

    script.js TIDAK perlu ditambah untuk modal (openModal / changeModalSlide sudah generik).

================================================================================
  KAPAN script.js HARUS DIUBAH?
================================================================================

  TIDAK perlu ubah script.js jika:
  - Hanya menambah / mengurangi jumlah portfolio di index.html
  - Hanya menambah modal dengan pola yang sama (View & Download + geser gambar)

  PERLU ubah script.js jika:
  - Mau fitur baru yang belum ada (filter, autoplay, swipe portfolio, dll.)
  - Carousel error karena selector HTML berubah (class/id diubah)

================================================================================
  KESALAHAN YANG SERING TERJADI
================================================================================

  1. Hanya tambah teks portfolio-detail, lupa tambah img-item di carousel
     -> Geser berhenti di nomor terakhir yang punya pasangan gambar.

  2. Hanya tambah gambar carousel, lupa portfolio-detail
     -> Sama, geser tidak sampai nomor baru.

  3. Urutan tidak sama
     -> Slide ke-3 harus portfolio 03, bukan acak.

  4. Hanya tambah modal di bawah file, tanpa portfolio-detail + img-item
     -> Modal bisa dibuka, tapi geser portfolio utama tidak nambah.

================================================================================
  KODE DI js/script.js UNTUK GESER PORTFOLIO (COPY DARI PROJECT ASLI)
  File: js/script.js
  Bagian ini yang mengatur geser portfolio - biasanya JANGAN diubah saat nambah project.
================================================================================

// ================= Carousel Portfolio ================= //
let currentIndex = 0;
const carousel = document.querySelector('.portfolio-carousel .img-slide');
const images = document.querySelectorAll('.portfolio-carousel .img-item');
const leftArrow = document.querySelector('.portfolio-box .arrow-left');
const rightArrow = document.querySelector('.portfolio-box .arrow-right');
const portfolioDetailsList = document.querySelectorAll('.portfolio-box:first-child .portfolio-detail');

// Batas geser = jumlah item terkecil antara detail teks dan gambar carousel
const maxIndex = Math.min(images.length, portfolioDetailsList.length) - 1;

function updateCarousel() {
    // Pastikan currentIndex berada di dalam batas yang benar
    currentIndex = Math.max(0, Math.min(currentIndex, maxIndex));

    // Geser carousel
    carousel.style.transform = `translateX(-${currentIndex * 100}%)`;

    // Toggle tombol disabled
    leftArrow.classList.toggle('disabled', currentIndex === 0);
    rightArrow.classList.toggle('disabled', currentIndex === maxIndex);

    // Update detail portfolio
    updatePortfolioDetail();
}

function updatePortfolioDetail() {
    portfolioDetailsList.forEach(detail => detail.classList.remove('active'));
    const activeDetail = portfolioDetailsList[currentIndex];
    if (activeDetail) activeDetail.classList.add('active');
}

// Event listener tombol kiri
leftArrow.addEventListener('click', () => {
    if (leftArrow.classList.contains('disabled')) return;
    currentIndex = Math.max(0, currentIndex - 1);
    updateCarousel();
});

// Event listener tombol kanan
rightArrow.addEventListener('click', () => {
    if (rightArrow.classList.contains('disabled')) return;
    currentIndex = Math.min(maxIndex, currentIndex + 1);
    updateCarousel();
});

// Inisialisasi carousel
updateCarousel();

================================================================================
  CONTOH REAL DI PROJECT INI (Portfolio 07 - Lampu Telegram)
================================================================================

  File kode   : arduino/hidupkanlamputelegram.ino  (atau sesuai nama file kamu)
  Skematik    : arduino/schematics/LampuTele.jpeg
  Modal id    : lampu-telegram-modal
  Tombol      : onclick="openModal('lampu-telegram-modal')"

  Saat portfolio masih 7 item, maxIndex otomatis = 6 (tampil nomor 01-07).
  Setelah tambah portfolio-detail ke-08 + img-item ke-8 di index.html,
  maxIndex otomatis = 7 (tampil nomor 01-08) tanpa ubah script.js.

================================================================================
  QUICK REFERENCE
================================================================================

  Tambah 1 portfolio:
    index.html  ->  +1 portfolio-detail
    index.html  ->  +1 img-item di .portfolio-carousel .img-slide
    images/     ->  +1 file gambar
    script.js   ->  tidak perlu (kecuali fitur baru)

  Terakhir diupdate: sesuai struktur project portofolio (8 portfolio + carousel auto)

================================================================================