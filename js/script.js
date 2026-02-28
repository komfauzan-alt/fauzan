const navLinks = document.querySelectorAll('header nav a'); 
const logoLink = document.querySelector('.logo');
const sections = document.querySelectorAll('section');
const menuIcon = document.querySelector('#menu-icon');
const navbar = document.querySelector('header nav');
const portfolioDetails = document.querySelectorAll('.potofolio-detail');

// Tombol dan bagian resume
const resumeBtns = document.querySelectorAll('.resume-btn');
const resumeDetails = document.querySelectorAll('.resume-detail');

// Menu toggle
menuIcon.addEventListener('click', () => {
    menuIcon.classList.toggle('bx-x');
    navbar.classList.toggle('active');
});

// Fungsi untuk mengatur tombol aktif dan menampilkan bagian yang relevan pada resume
function showResumeDetail(section) {
    // Nonaktifkan semua resume-detail dan tombol
    resumeDetails.forEach(detail => detail.classList.remove('active'));
    resumeBtns.forEach(btn => btn.classList.remove('active'));

    // Aktifkan tombol yang diklik dan tampilkan bagian yang relevan
    const activeButton = resumeBtns[section - 1];
    const activeDetail = resumeDetails[section - 1];

    activeButton.classList.add('active');
    activeDetail.classList.add('active');
}

// Event listener untuk tombol resume
resumeBtns.forEach((btn, index) => {
    btn.addEventListener('click', () => {
        showResumeDetail(index + 1);  // Menambahkan 1 karena index dimulai dari 0
    });
});

// Inisialisasi pertama, menampilkan bagian pertama (Experience)
showResumeDetail(1);

// Fungsi untuk mengaktifkan halaman dan menyembunyikan elemen yang tidak perlu
const activePage = () => {
    const header = document.querySelector('header');
    const barsBox = document.querySelector('.bars-box');

    header.classList.remove('active');
    setTimeout(() => {
        header.classList.add('active');
    }, 1100);

    navLinks.forEach(link => link.classList.remove('active')); // Hapus kelas 'active' dari semua link

    barsBox.classList.remove('active');
    setTimeout(() => {
        barsBox.classList.add('active');
    }, 1100);

    sections.forEach(section => section.classList.remove('active'));

    menuIcon.classList.remove('bx-x');
    navbar.classList.remove('active');
};

// Event listener untuk navigasi
navLinks.forEach((link, idx) => {
    link.addEventListener('click', () => {
        if (!link.classList.contains('active')) {
            activePage();

            link.classList.add('active');  // Menandai link yang aktif

            // Menambahkan class aktif pada section sesuai index link yang diklik
            setTimeout(() => {
                sections[idx].classList.add('active');
            }, 1100); // Sesuaikan durasi sesuai dengan animasi yang diinginkan
        }
    });
});

// Logo link untuk navigasi ke halaman utama
logoLink.addEventListener('click', () => {
    if (!navLinks[0].classList.contains('active')) {
        activePage();

        navLinks[0].classList.add('active'); // Menandai link pertama sebagai aktif

        setTimeout(() => {
            sections[0].classList.add('active'); // Menampilkan section pertama
        }, 1100);
    }
});

// Menambahkan logika untuk navigasi carousel
let currentIndex = 0; // Menyimpan index gambar yang aktif
const carousel = document.querySelector('.img-slide'); // Menyimpan referensi ke slide gambar
const images = document.querySelectorAll('.img-item'); // Menyimpan semua gambar
const leftArrow = document.querySelector('.arrow-left'); // Tombol kiri
const rightArrow = document.querySelector('.arrow-right'); // Tombol kanan
const portfolioDetailsList = document.querySelectorAll('.potofolio-detail'); // Menyimpan detail portfolio

// Fungsi untuk memperbarui carousel berdasarkan index
function updateCarousel() {
    const totalImages = images.length;

    // Memindahkan gambar berdasarkan index
    carousel.style.transform = `translateX(-${currentIndex * 100}%)`;

    // Mengaktifkan atau menonaktifkan tombol kiri/kanan
    leftArrow.classList.toggle('disabled', currentIndex === 0); // Nonaktifkan tombol kiri di gambar pertama
    rightArrow.classList.toggle('disabled', currentIndex === totalImages - 1); // Nonaktifkan tombol kanan di gambar terakhir

    // Update detail portfolio yang relevan berdasarkan gambar yang aktif
    updatePortfolioDetail();
}

// Fungsi untuk memperbarui detail portfolio berdasarkan index carousel
function updatePortfolioDetail() {
    portfolioDetailsList.forEach(detail => detail.classList.remove('active')); // Nonaktifkan semua detail

    const activeDetail = portfolioDetailsList[currentIndex]; // Menentukan detail yang relevan dengan gambar aktif
    if (activeDetail) {
        activeDetail.classList.add('active'); // Tampilkan detail portfolio yang relevan
    }
}

// Event listener untuk tombol kiri
leftArrow.addEventListener('click', () => {
    if (currentIndex > 0) {
        currentIndex--; // Mengurangi index untuk pindah ke gambar sebelumnya
        updateCarousel(); // Memperbarui carousel dan detail portfolio
    }
});

// Event listener untuk tombol kanan
rightArrow.addEventListener('click', () => {
    if (currentIndex < images.length - 1) {
        currentIndex++; // Menambah index untuk pindah ke gambar berikutnya
        updateCarousel(); // Memperbarui carousel dan detail portfolio
    }
});

// Inisialisasi awal untuk memperbarui carousel dan detail portfolio
updateCarousel();

