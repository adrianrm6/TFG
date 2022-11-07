// Función para validar formulario Elo
function validaFormElo(){

    if ($("#elo").val() === ""){
        $("elo").focus();
        return false;
    }
    else if($("#opciones").val() == ""){
        return false;
    }
    else{
        return true;
    }
}

let giro = false;
let colors = ["#F0D9B5", "#B58863"]; // in the order [white, black]

// Función para saber a qué color le toca mover
function showNextMoveColor(){
    let boxWidth = $("#a1").innerWidth()/4;
    let boxHeight = $("#a1").innerHeight()/4;
    let offset = $("#chessboard").innerWidth()/2 - boxWidth/2;
    let sideColor = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'.split(' ')[1] == 'w' ? colors[0] : colors[1];
    let moveColor = "white";
    
    if (typeof codigo !== 'undefined'){
        sideColor = codigo.split(' ')[1] == 'w' ? colors[0] : colors[1];
    }

    if(sideColor === colors[1]){
        giro = true;
        moveColor = "black";
    }
    
    $("#image-display").prepend('<div id="next-move-box"></div>');
    $("#next-move-box").css({
        "width": boxWidth,
        "height": boxHeight,
        "border": "solid 2px ".moveColor,
        "transform": "translateX(" + offset.toString() + "px)",
        "border-radius" : "3px",
        "background-color": moveColor,
    });
}

// Función para validar el código FEN
function validateFEN(fen){
        const validateRank = (notation) => {
    const hasContinuousNumbers = /\d{2}/.test(notation);
    
    const letters = notation.split('');
    
    const hasOnlyValidLetters = () => {
        return !letters.some((letter) => {
        return !/[1-8]|[pkqbnrPKQBNR]/.test(letter);
        });
    };
    
    const totalSquares = letters.reduce((total, letter) => {
        const parsedLetter = parseInt(letter, 10);
        const isInteger = Number.isInteger(parsedLetter);
        return isInteger? (total + parsedLetter) : (total + 1);
    }, 0);
    
    return ( hasOnlyValidLetters() &&
            !hasContinuousNumbers &&
            totalSquares === 8 );
    }
    
    const validatePiecePlacement = (notation) => {
    var ranks = notation.split('/');
    if (ranks.length !== 8) return false;
    
    return ranks.reduce(
        (lastVal, rank) => lastVal && validateRank(rank),
    true);
    }
    
    const curry = f => a => b => f(a, b);
    
    const check = curry((regex, str) => regex.test(str));
    
    const validateSideToMove = check(/^(w|b)$/);
    
    const validateCastlingAbility = check(/^-$|^(KQ?k?q?|Qk?q?|kq?|q)$/);
    
    const validateEnPassantTarget = check(/^(-|[a-h][36])$/);
    
    const validateHalfMoveClock = check(/^([0-9]|[1-9][0-9])$/);
    
    const validateFullMoveCounter = check(/^([1-9][0-9]{0,1})$/);
    
    /* parse FEN */
    const fenArr = fen.split(' ');
    const [piecePlacement, sideToMove,
            castlingAbility, enPassantTarget,
            halfMoveClock, fullMoveCounter] = fenArr;

    return (fenArr.length === 6) &&
            validatePiecePlacement(piecePlacement) &&
            validateSideToMove(sideToMove) &&
            validateCastlingAbility(castlingAbility) &&
            validateEnPassantTarget(enPassantTarget) &&
            validateHalfMoveClock(halfMoveClock) &&
            validateFullMoveCounter(fullMoveCounter);

}

// Función para conocer y mostrar las coordenadas en el tablero
function showBoardCoordsFunc(){
    const files = "abcdefgh";
    const offset  = $("#a1").innerHeight()/2.75;
    const fontSize = Math.min($("#chessboard").innerWidth(), $("#chessboard").innerHeight()) /500 * 12; 
    /* coord-col */
    for (let i = 0; i < files.length; i++){
        $("#" + files.charAt(i) + "1").append('<div class="coord-col"></div>');
        $("#" + files.charAt(i) + "1")
            .children(".coord-col")
            .text(files.charAt(i))
        $(".coord-col").css({
                "position": "absolute",
                "color": "black",
                "transform": "translateY("+ offset.toString() + "px)",
                "font-size": fontSize,
            });
    }
    /* coord-row */
    for (let i = 0; i < 8; i++){
        $("#h" + (i+1).toString()).append('<div class="coord-row"></div>');
        $("#h" + (i+1).toString())
            .children(".coord-row")
            .text((i+1).toString())
        $(".coord-row").css({
                "position": "absolute",
                "color": "black",
                "transform": "translateX("+ offset.toString() + "px)",
                "font-size": fontSize,
            });
    }
}

// Función para crear el tablero y mostrarlo
function createChessBoard(width, height, showBoardCoords, showBorder, showWhoseMove, borderType){
    $('<div id="chessboard" class="card"></div>').appendTo("#image-display");
    $('#chessboard').css({
        "margin": "auto",
        "width": width,
        "height": height,
    });
    if(showBorder){
            $('#chessboard').css({
                "border": borderType + " 2px black",
            });
    }

    $('<div id="square-prototype"></div>').appendTo("#chessboard");
    const files = "abcdefgh";
    const numFiles = 8;
    const numRanks = 8;
    for(let i = 0; i < numRanks; i++){
        for(let j = 0; j < numFiles; j++){
            let idStr = files.charAt(j)+(numFiles - i).toString();
            let colorPref = (i+j)%2 == 0 ? colors[0] : colors[1];
            let colorNotPref = (i+j)%2 == 0 ? colors[1] : colors[0];

            if (typeof mov1 !== 'undefined'){
                if ((j == 0 && mov1[0] == 'a' && numRanks-i == mov1[1]) || 
                    (j == 1 && mov1[0] == 'b' && numRanks-i == mov1[1]) ||
                    (j == 2 && mov1[0] == 'c' && numRanks-i == mov1[1]) || 
                    (j == 3 && mov1[0] == 'd' && numRanks-i == mov1[1]) ||
                    (j == 4 && mov1[0] == 'e' && numRanks-i == mov1[1]) || 
                    (j == 5 && mov1[0] == 'f' && numRanks-i == mov1[1]) ||
                    (j == 6 && mov1[0] == 'g' && numRanks-i == mov1[1]) || 
                    (j == 7 && mov1[0] == 'h' && numRanks-i == mov1[1])){

                        colorPref = "#ffed78";
                    }
            }
            if (typeof mov2 !== 'undefined'){
                if ((j == 0 && mov2[0] == 'a' && numRanks-i == mov2[1]) || 
                    (j == 1 && mov2[0] == 'b' && numRanks-i == mov2[1]) ||
                    (j == 2 && mov2[0] == 'c' && numRanks-i == mov2[1]) || 
                    (j == 3 && mov2[0] == 'd' && numRanks-i == mov2[1]) ||
                    (j == 4 && mov2[0] == 'e' && numRanks-i == mov2[1]) || 
                    (j == 5 && mov2[0] == 'f' && numRanks-i == mov2[1]) ||
                    (j == 6 && mov2[0] == 'g' && numRanks-i == mov2[1]) || 
                    (j == 7 && mov2[0] == 'h' && numRanks-i == mov2[1])){

                        colorPref = "#ffff33";
                }
            }

            $("#square-prototype")
                .clone()
                .attr("id", idStr)
                .attr("class", "square")
                .css({
                    "display":"flex",
                    "flex-direction":"row",
                    "align-items":"center",
                    "justify-content":"center",
                    "background-color": colorPref,
                    "min-width": $("#chessboard").innerWidth()/8,
                    "min-height": $("#chessboard").innerHeight()/8,
                    "color": colorNotPref,
                    "font-size": "12px",
                })
                .appendTo("#chessboard");	
        }
    }
    $("#square-prototype").remove();

    if(showBoardCoords){
        showBoardCoordsFunc(width, height);
    }

    if(showWhoseMove){
        showNextMoveColor();
    }
}

// Función para colocar las piezas en el tablero
function getPieceLocFromFEN(fen){
    let locObj = {
        white: [],
        black: []
    };
    const mainField = fen.split(' ')[0];
    const ranks = mainField.split('/');
    const lowP = "rnbqkp";
    const highP = lowP.toUpperCase();

    for(let rankIdx = 8; rankIdx >= 1; rankIdx--){
        let ranksArr = ranks[8-rankIdx].split('');
        let fileIdx = 1;
        for(let ranksArrIdx = 0; ranksArrIdx < ranksArr.length; ranksArrIdx++){
            if(lowP.indexOf(ranksArr[ranksArrIdx]) >= 0){
                locObj.black.push([fileIdx, rankIdx, ranksArr[ranksArrIdx]]);
                fileIdx++;
            }
            else if(highP.indexOf(ranksArr[ranksArrIdx]) >= 0){
                locObj.white.push([fileIdx, rankIdx, ranksArr[ranksArrIdx]]);
                fileIdx++;
            }
            else
                fileIdx += parseInt(ranksArr[ranksArrIdx]);
        }
    }
    
    return locObj;
}

// Función para conocer los cambios de posición del tablero
function updatePiecesArrToBoardCoords(obj){
    const coordMap = "abcdefgh";
    let newArr = [ [], [] ];
    const wLen = obj.white.length;
    const bLen = obj.black.length;
    for(let i = 0; i < wLen; i++){
        let removedIdx = obj.white.shift();
        newArr[0].push("" + removedIdx[2] + coordMap.charAt(removedIdx[0]-1) + removedIdx[1]);
    }
    for(let i = 0; i < bLen; i++){
        let removedIdx = obj.black.shift();
        newArr[1].push("" + removedIdx[2] + coordMap.charAt(removedIdx[0]-1) + removedIdx[1]);
    }
    
    return newArr;
}

// Función para crear las piezas en el tablero
function createPieces(){
    // FEN por defecto, la posición inicial
    let fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1';
    if (typeof codigo !== 'undefined'){
        fen = codigo;
    }
    
    if(!validateFEN(fen)){
        $("#fracasoFen").fadeIn();
        $("#fracasoFen").fadeOut(5000);
    }
    else{
        let piecesObj = getPieceLocFromFEN(fen);
        let arr = updatePiecesArrToBoardCoords(piecesObj);
        for(let i = 0; i < arr.length; i++){
            for(let j = 0; j < arr[i].length; j++){
                let filePathStr = "assets/pieces/";
                if((/^[A-Z]/).test(arr[i][j].charAt(0)))
                    filePathStr += 'w';	
                else
                    filePathStr += 'b';
                filePathStr += arr[i][j].charAt(0).toLowerCase() + ".svg";
                let imgStr = '<img src=' + filePathStr + ' alt=""' + ' id=' + arr[i][j].slice(1) + '-piece></img>';
                
                let pieceWidth = $("#chessboard").innerWidth()/10;
                let pieceHeight = $("#chessboard").innerHeight()/10;
                $('#'+arr[i][j].slice(1,3)).append(imgStr);
                $('#'+arr[i][j].slice(1,3)+'-piece').css({
                    "display":"relative",
                    "width": pieceWidth,
                    "height": pieceHeight,
                    "z-index":2,
                });
                $('#'+arr[i][j].slice(1,3)+'-piece').addClass("piece");
            }
        }
    }
}

// Función para limpiar el tablero
function removeChessBoard(){
    $("#image-display").children().remove();
}


$(document).ready(function() {

    // Botón para el formulario, inicio
    $("#botonElo").click( function() {
        // Si no se consigue validar el primer formulario se
        // le muestra al usuario lo que tiene que rellenar
        if (!validaFormElo()){
            $("#instrucciones").show();
            $("#respuestas").hide();
            $("#cardCambioEtiquetas").hide();

            $("#fracaso").fadeIn();
            $("#fracaso").fadeOut(5000);
        }
        else{
            $("#instrucciones").hide();
            $("#respuestas").show();
            $("#cardCambioEtiquetas").show();
        }
    });

    // Al pulsar el botón cambiamos al formulario para cambiar los datos de la Cookie
    $("#botonCookie").click( function() {
        $("#divElo").show();
        $("#divEloSel").hide();
    });

    // Formulario para etiquetar posiciones
    $("#respuestas").submit(function(e){
        // Si la cantidad de checkboxes "chequeados" es cero,
        // entonces se evita que se envíe el formulario y se
        // muestra un mensaje al usuario
        if ($('input[type=checkbox]:checked').length === 0) {
            e.preventDefault();
            $("#obligatorio").fadeIn();
            $("#obligatorio").fadeOut(5000);
        }
        else{
            // Ocultamos las respuestas para que no aparezcan si no queremos seguir evaluando posiciones
            $("#instrucciones").show();
            $("#respuestas").hide();
            $("#cardCambioEtiquetas").hide();
        }
    });

    $(".form-check").click(function(){
        // Si pulsamos cualquiera de las 10 primeras opciones
        // la opción 11 se desactiva
        $("#opcion11").prop("checked", false);
    });

    $(".form-check-no").click(function(){
        // Si pulsamos la opción 11 se desactiva cualquiera de
        // las otras opciones que estén activas
        $("#opcion1").prop("checked", false);
        $("#opcion2").prop("checked", false);
        $("#opcion3").prop("checked", false);
        $("#opcion4").prop("checked", false);
        $("#opcion5").prop("checked", false);
        $("#opcion6").prop("checked", false);
        $("#opcion7").prop("checked", false);
        $("#opcion8").prop("checked", false);
        $("#opcion9").prop("checked", false);
        $("#opcion10").prop("checked", false);
    });

    // Botón para cambiar etiquetas
    $("#botonCambiarEtiquetas").click( function() {

        if (!$("#opcion1").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion1").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion1").value = aleatorio; 
        }
        if (!$("#opcion2").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion2").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion2").value = aleatorio; 
        }
        if (!$("#opcion3").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion3").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion3").value = aleatorio; 
        }
        if (!$("#opcion4").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion4").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion4").value = aleatorio; 
        }
        if (!$("#opcion5").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion5").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion5").value = aleatorio; 
        }
        if (!$("#opcion6").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion6").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion6").value = aleatorio; 
        }
        if (!$("#opcion7").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion7").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion7").value = aleatorio; 
        }
        if (!$("#opcion8").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion8").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion8").value = aleatorio; 
        }
        if (!$("#opcion9").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion9").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion9").value = aleatorio; 
        }
        if (!$("#opcion10").prop('checked')){
            var aleatorio = Math.floor(Math.random() * (max-1) + 1);
            document.getElementById("labelopcion10").innerHTML = etiquetas[aleatorio];
            document.getElementById("opcion10").value = aleatorio; 
        }
    });

    // Función para resetear el tablero
    function resetBoard(){
        // Tamaño del tablero
        let nuevoBoard = 700;
        if (document.documentElement.scrollWidth >= 1100 && document.documentElement.scrollWidth < 1500){
            nuevoBoard = 500; 
        }
        else if (document.documentElement.scrollWidth >= 900 && document.documentElement.scrollWidth < 1100){
            nuevoBoard = 400; 
        }
        else if (document.documentElement.scrollWidth >= 800 && document.documentElement.scrollWidth < 900){
            nuevoBoard = 380; 
        }
        else if (document.documentElement.scrollWidth >= 700 && document.documentElement.scrollWidth < 800){
            nuevoBoard = 500; 
        }
        else if (document.documentElement.scrollWidth >= 500 && document.documentElement.scrollWidth < 700) {
            nuevoBoard = 360; 
        }
        else if (document.documentElement.scrollWidth >= 400 && document.documentElement.scrollWidth < 500) {
            nuevoBoard = 300; 
        }
        else if (document.documentElement.scrollWidth < 400) {
            nuevoBoard = 280; 
        }
        const boardWidth = nuevoBoard;
        const boardHeight = nuevoBoard;
        const showBoardCoords = true;
        const showBorder = false;
        const borderType = 'solid';
        
        removeChessBoard();
        createChessBoard(boardWidth, boardHeight, showBoardCoords, showBorder, true, borderType);
        createPieces();

        const offsetW  = $("#a1").innerWidth()/2.75;
        const offsetH  = $("#a1").innerHeight()/2.75;
        const flipOffsetW  = $("#chessboard").innerWidth() - $("#a1").innerWidth()/1.65;
        const flipOffsetH  = $("#chessboard").innerHeight() - $("#a1").innerHeight()/1.65;

        // Comprobamos si debemos realizar o no un giro
        if(giro){
            $("#chessboard").css("transform","rotateZ(180deg)");
            $(".piece").css("transform","rotateZ(180deg)");
            $(".coord-col").css({"transform":"rotateZ(180deg) translateY("+flipOffsetH.toString()+"px)","color":"black"});
            $(".coord-row").css({"transform":"rotateZ(180deg) translateX("+flipOffsetW.toString()+"px)","color":"black"});
        }
        else{
            $("#chessboard").css("transform","rotateZ(360deg)");
            $(".piece").css("transform","rotateZ(360deg)");
            $(".coord-col").css("transform","rotateZ(360deg) translateY("+offsetH.toString()+"px)");
            $(".coord-row").css("transform","rotateZ(360deg) translateX("+offsetW.toString()+"px)");
        }
        
    }
    
    resetBoard();
    /* Enter press event */
    $(document).on('keypress',function(e) {
        if(e.which == 13) {
                resetBoard();
        }
    });

    $("#botonElo").click(()=>{resetBoard()});

    // Redimensionamos el tablero según varíe el tamaño de la pantalla
    window.addEventListener("resize", function(){
        resetBoard();
    });

});
    