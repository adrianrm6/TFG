<?php ob_start();?>
<?php
    //Seleccionamos el idioma
    if (!isset($_GET['langID'])){
        $lang = 'eng';
        include('lang/'. $lang . '.php');
    }
    else if ($_GET['langID'] == "esp"){
        $lang = $_GET['langID'];
        include('lang/'. $lang . '.php');
    }
    else if ($_GET['langID'] == "fre"){
        $lang = $_GET['langID'];
        include('lang/'. $lang . '.php');
    }
    else{
        $lang = 'eng';
        include('lang/'. $lang . '.php');
    }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <title>TFG</title>

    <meta charset="UTF-8">
    <meta name="application-name" content="Etiquetar Posiciones">
    <meta name="author" content="Adrián Rodríguez Montero">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    
    <link rel="stylesheet" href="https://bootswatch.com/4/lumen/bootstrap.min.css"/>
    <link rel="stylesheet" href="CSS/estilo.css">          
</head>

<body>    
    <!--CABECERA-->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark"> 
        <ul class="navbar-nav mx-auto" style="width: 90%;">     
            <!--Logo UGR-->  
            <div class="navbar-nav" id="figuraUGR">
                <img class="fotoUGR" src="assets/ugr.png" alt="foto UGR">
            </div>


                <!--Texto introductorio-->
            <div class="navbar-nav" id="textoUGR">
                <div class="w3-container" id="textoIntroduccion">
                    <p style="font-size: 40px;"><?php echo htmlspecialchars($textoUgr['0'], ENT_QUOTES, 'UTF-8'); ?></p>
                    <p style="font-size: 15px;"><?php echo htmlspecialchars($textoUgr['1'], ENT_QUOTES, 'UTF-8'); ?></p>
                </div>
            </div>
        </ul>
    </nav>

    <!--Añadimos la despedida-->
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <div class="title" style="margin: 20px auto; text-align:center; color:white;">
        <h1 style="font-size: 35px"><?php echo htmlspecialchars($despedida['0'], ENT_QUOTES, 'UTF-8'); ?></h1>
        <a href="https://lsi2.ugr.es/fjmelero/chessai/?langID=<?php echo htmlspecialchars($lang, ENT_QUOTES, 'UTF-8'); ?>">
                <button class="btn btn-success" id="botonCookie" name="botonCookie" type="submit">
                    <?php echo htmlspecialchars($despedida['1'], ENT_QUOTES, 'UTF-8'); ?>
                </button>
            </a>
    </div>


    </nav>

    <!--PIE DE PAGINA-->
    <footer class="text-center text-white">
        <div class="text-center p-1" style="background-color: #555; height: auto;">
            TFG - Adrián Rodríguez Montero - DGIIM
        </div>
    </footer>
    
    <script
		src="https://code.jquery.com/jquery-3.6.0.min.js"
		integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4="
		crossorigin="anonymous"></script>
    <script src="app.js"></script>
</body>

</html>
<?php ob_end_flush(); ?>