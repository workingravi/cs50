
    document.onkeydown = detectKey;
    function detectKey(e) {
        var posLeft = document.getElementById('myId').offsetLeft;
        var posTop = document.getElementById('myId').offsetTop;
        e = e || window.event;
        if (e.keyCode == '38') {
            // up arrow
            document.getElementById('myId').style.marginTop  = (posTop-58)+"px";
        }
        else if (e.keyCode == '40') {
            // down arrow
            document.getElementById('myId').style.marginTop  = (posTop+58)+"px";
        }
        else if (e.keyCode == '37') {
           // left arrow
            document.getElementById('myId').style.marginLeft  = (posLeft-58)+"px";
        }
        else if (e.keyCode == '39') {
           // right arrow
            document.getElementById('myId').style.marginLeft  = (posLeft+58)+"px";
        }
    }