document.addEventListener('DOMContentLoaded', function() {
    setInterval(() => {
        var xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("button1_state").innerHTML = this.responseText
            }
        }
        xhttp.open("GET", "firstbutton", true)
        xhttp.send()
    }, 100)
    setInterval(() => {
        var xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            document.getElementById("button2_state").innerHTML = this.responseText
            }
        }
        xhttp.open("GET", "secondbutton", true)
        xhttp.send()
    }, 100)
})