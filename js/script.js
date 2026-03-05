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
    resumeDetails.forEach(detail => detail.classList.remove('active'));
    resumeBtns.forEach(btn => btn.classList.remove('active'));

    const activeButton = resumeBtns[section - 1];
    const activeDetail = resumeDetails[section - 1];

    activeButton.classList.add('active');
    activeDetail.classList.add('active');
}

// Event listener untuk tombol resume
resumeBtns.forEach((btn, index) => {
    btn.addEventListener('click', () => {
        showResumeDetail(index + 1);
    });
});

// Inisialisasi pertama, menampilkan bagian pertama
showResumeDetail(1);

// Fungsi untuk mengaktifkan halaman dan menyembunyikan elemen yang tidak perlu
const activePage = () => {
    const header = document.querySelector('header');
    const barsBox = document.querySelector('.bars-box');

    header.classList.remove('active');
    setTimeout(() => {
        header.classList.add('active');
    }, 1100);

    navLinks.forEach(link => link.classList.remove('active'));

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
            link.classList.add('active');

            setTimeout(() => {
                sections[idx].classList.add('active');
            }, 1100);
        }
    });
});

// Logo link untuk navigasi ke halaman utama
logoLink.addEventListener('click', () => {
    if (!navLinks[0].classList.contains('active')) {
        activePage();
        navLinks[0].classList.add('active');

        setTimeout(() => {
            sections[0].classList.add('active');
        }, 1100);
    }
});

// ================= Carousel Portfolio ================= //
let currentIndex = 0;
const carousel = document.querySelector('.img-slide');
const images = document.querySelectorAll('.img-item');
const leftArrow = document.querySelector('.arrow-left');
const rightArrow = document.querySelector('.arrow-right');
const portfolioDetailsList = document.querySelectorAll('.potofolio-detail');

function updateCarousel() {
    const totalImages = images.length;

    // Geser carousel
    carousel.style.transform = `translateX(-${currentIndex * 100}%)`;

    // Toggle tombol disabled
    leftArrow.classList.toggle('disabled', currentIndex === 0);
    rightArrow.classList.toggle('disabled', currentIndex === totalImages - 1);

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
    currentIndex--;
    updateCarousel();
});

// Event listener tombol kanan
rightArrow.addEventListener('click', () => {
    if (rightArrow.classList.contains('disabled')) return;
    currentIndex++;
    updateCarousel();
});

// Inisialisasi carousel
updateCarousel();