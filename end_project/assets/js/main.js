document.addEventListener('DOMContentLoaded', () => {
    const elButton = document.getElementById('startButton')
    elButton.addEventListener('click', () => {
        let xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = () => {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("startButton").innerHTML = this.responseText
            }
        }
        xhttp.open("GET", "stateButton", true)
        xhttp.send()
    })
    setInterval(() => {
        let xhttp = new XMLHttpRequest()
        xhttp.onreadystatechange = () => {
            if (this.readyState == 4 && this.status == 200) {
                document.getElementById("timer").innerHTML = this.responseText
            }
        }
        xhttp.open("GET", "timer", true)
        xhttp.send()
    }, 100)
})