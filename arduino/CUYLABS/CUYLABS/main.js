const endpoint = "http://192.xxx.x.xx"; // Ganti dengan IP ESP32 kamu

// ======== GET LED ========
function getDapurLed() {
    fetch(endpoint + "/dapur", { method: "GET" })
        .then(response => response.text())
        .then(result => {
            if(result == "ON") {
                ledDapur.style.backgroundColor = "rgba(20, 20, 20, 0.6)";
                dapurLedImage.src ="./assets/led-on-red.png";
                ledDapur.textContent = "TURN OFF";
            } else {
                ledDapur.style.backgroundColor = "rgba(30, 30, 30, 0.4)";
                dapurLedImage.src ="./assets/led-off.png";
                ledDapur.textContent = "TURN ON";
            }
        });
}

function getTamuLed() {
    fetch(endpoint + "/tamu", { method: "GET" })
        .then(response => response.text())
        .then(result => {
            if(result == "ON") {
                ledTamu.style.backgroundColor = "rgba(20, 20, 20, 0.6)";
                tamuLedImage.src ="./assets/led-on-blue.png";
                ledTamu.textContent = "TURN OFF";
            } else {
                ledTamu.style.backgroundColor = "rgba(30, 30, 30, 0.4)";
                tamuLedImage.src ="./assets/led-off.png";
                ledTamu.textContent = "TURN ON";
            }
        });
}

function getMakanLed() {
    fetch(endpoint + "/makan", { method: "GET" })
        .then(response => response.text())
        .then(result => {
            if(result == "ON") {
                ledMakan.style.backgroundColor = "rgba(20, 20, 20, 0.6)";
                makanLedImage.src ="./assets/led-on-green.png";
                ledMakan.textContent = "TURN OFF";
            } else {
                ledMakan.style.backgroundColor = "rgba(30, 30, 30, 0.4)";
                makanLedImage.src ="./assets/led-off.png";
                ledMakan.textContent = "TURN ON";
            }
        });
}

function getToiletLed() {
    fetch(endpoint + "/toilet", { method: "GET" })
        .then(response => response.text())
        .then(result => {
            if(result == "ON") {
                ledToilet.style.backgroundColor = "rgba(20, 20, 20, 0.6)";
                toiletLedImage.src ="./assets/led-on-yellow.png";
                ledToilet.textContent = "TURN OFF";
            } else {
                ledToilet.style.backgroundColor = "rgba(30, 30, 30, 0.4)";
                toiletLedImage.src ="./assets/led-off.png";
                ledToilet.textContent = "TURN ON";
            }
        });
}



// ======== SET LED ========
function setDapurLed() {
    fetch(endpoint + "/dapur", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}

function setTamuLed() {
    fetch(endpoint + "/tamu", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}

function setMakanLed() {
    fetch(endpoint + "/makan", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}

function setToiletLed() {
    fetch(endpoint + "/toilet", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}


// ======== SET ALL LED ========
function turnAllOn() {
    fetch(endpoint + "/allon", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}

function turnAllOff() {
    fetch(endpoint + "/alloff", { method: "POST" })
        .then(response => response.text())
        .then(() => location.reload());
}

// ======== INITIALIZE ========
getDapurLed();
getMakanLed();
getTamuLed();
getToiletLed();


