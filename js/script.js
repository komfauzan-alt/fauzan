const navLinks = document.querySelectorAll('header nav a'); 
const logoLink = document.querySelector('.logo');
const sections = document.querySelectorAll('section');
const menuIcon = document.querySelector('#menu-icon');
const navbar = document.querySelector('header nav');

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
    }, 150);

    navLinks.forEach(link => link.classList.remove('active'));

    barsBox.classList.remove('active');
    setTimeout(() => {
        barsBox.classList.add('active');
    }, 150);

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
            }, 150);
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
        }, 150);
    }
});

// Modal functions
const modalGalleryIndex = {};

function openModal(modalId) {
    const modal = document.getElementById(modalId);
    if (!modal) return;
    modal.style.display = 'flex';
    if (modal.querySelector('.modal-gallery')) {
        initModalGallery(modalId);
    }
}

function closeModal(modalId) {
    const modal = document.getElementById(modalId);
    if (modal) modal.style.display = 'none';
}

// Close modal when clicking outside
window.onclick = function(event) {
    if (event.target.classList.contains('modal')) {
        event.target.style.display = 'none';
    }
}

function initModalGallery(modalId) {
    modalGalleryIndex[modalId] = 0;
    updateModalSlide(modalId);
}

function updateModalSlide(modalId) {
    const modal = document.getElementById(modalId);
    if (!modal) return;

    const slides = modal.querySelectorAll('.modal-slide');
    const downloadBtn = modal.querySelector('.modal-download-btn');
    if (!slides.length) return;

    let idx = modalGalleryIndex[modalId] || 0;
    idx = Math.max(0, Math.min(idx, slides.length - 1));
    modalGalleryIndex[modalId] = idx;

    slides.forEach((slide, index) => {
        slide.classList.toggle('active', index === idx);
    });

    if (downloadBtn && slides[idx]) {
        downloadBtn.setAttribute('href', slides[idx].getAttribute('src'));
    }
}

function changeModalSlide(modalId, step) {
    const modal = document.getElementById(modalId);
    if (!modal) return;

    const slides = modal.querySelectorAll('.modal-slide');
    if (!slides.length) return;

    let idx = (modalGalleryIndex[modalId] || 0) + step;

    if (idx < 0) {
        idx = slides.length - 1;
    } else if (idx >= slides.length) {
        idx = 0;
    }

    modalGalleryIndex[modalId] = idx;
    updateModalSlide(modalId);
}

document.querySelectorAll('.modal-gallery').forEach((gallery) => {
    let touchStartX = 0;

    gallery.addEventListener('touchstart', (event) => {
        touchStartX = event.changedTouches[0].screenX;
    }, { passive: true });

    gallery.addEventListener('touchend', (event) => {
        const modalEl = gallery.closest('.modal');
        if (!modalEl || !modalEl.id) return;

        const touchEndX = event.changedTouches[0].screenX;
        const swipeDistance = touchEndX - touchStartX;

        if (Math.abs(swipeDistance) < 40) return;
        if (swipeDistance > 0) {
            changeModalSlide(modalEl.id, -1);
        } else {
            changeModalSlide(modalEl.id, 1);
        }
    }, { passive: true });
});

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