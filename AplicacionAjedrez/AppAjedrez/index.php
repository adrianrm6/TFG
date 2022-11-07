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


    //Cookie
    if (isset($_POST['elo']) && $_POST['opciones'] != '0'){

        if(isset($_COOKIE["EloJugador"])){
            setcookie("EloJugador", "", time() - 100);
        }

        if (ctype_digit($_POST['elo']) && 0 < $_POST['elo'] && $_POST['elo'] <= 5000){
            if (ctype_digit($_POST['opciones']) && 0 < $_POST['opciones'] && $_POST['opciones'] < 10){
                $eloJugador = htmlspecialchars(stripslashes(trim($_POST['elo'])));
                $opcionesJugador = htmlspecialchars(stripslashes(trim($_POST['opciones'])));
                $eloJugador = (string)(int)($eloJugador);
                $opcionesJugador = (string)(int)($opcionesJugador);

                setcookie("EloJugador", "$eloJugador-$opcionesJugador", time() + 2592000);
                
                $_COOKIE["EloJugador"] = "$eloJugador-$opcionesJugador";
            }
            else{
                http_response_code(400);
                echo '<script>alert("Invalid platform")</script>';
            }
        }
        else{
            http_response_code(400);
            echo '<script>alert("Invalid Elo format")</script>';
        }
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
        <ul class="navbar-nav mx-auto" style="width: 70%;">     
            <!--Logo UGR-->  
            <div class="navbar-nav" id="figuraUGR">
                <img class="fotoUGR" src="assets/ugr.png" alt="foto UGR">
            </div>


                <!--Texto introductorio-->
            <div class="navbar-nav" id="textoUGR" style="margin: auto;">
                <div class="w3-container" id="textoIntroduccion">
                    <p style="font-size: 40px;"><?php echo htmlspecialchars($textoUgr['0'], ENT_QUOTES, 'UTF-8'); ?></p>
                    <p style="font-size: 15px;"><?php echo htmlspecialchars($textoUgr['1'], ENT_QUOTES, 'UTF-8'); ?></p>
                </div>
            </div>
        </ul>

        <ul class="navbar-nav mx-auto">
            <li id="formulariosInicio">
                <div id="divElo" style="width: 100%">
                    <!--Formulario para introducir el nivel de Elo y la plataforma-->
                    <form class="form-inline my-2 my-lg-0" id="formularioElo" name="formularioElo" method="post">
                        <div class="content-select">
                        
                            <input type="number" class="form-control mr-sm-2" min="1" max="5000" id="elo" name="elo" placeholder="<?php echo htmlspecialchars($seleccionElo['0'], ENT_QUOTES, 'UTF-8'); ?>" required/>
                            
                            <select class="form-control" id="opciones" name="opciones" required>
                                <option value=""><?php echo htmlspecialchars($seleccionaPlataforma['0'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="1"><?php echo htmlspecialchars($seleccionaPlataforma['1'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="2"><?php echo htmlspecialchars($seleccionaPlataforma['2'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="3"><?php echo htmlspecialchars($seleccionaPlataforma['3'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="4"><?php echo htmlspecialchars($seleccionaPlataforma['4'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="5"><?php echo htmlspecialchars($seleccionaPlataforma['5'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="6"><?php echo htmlspecialchars($seleccionaPlataforma['6'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="7"><?php echo htmlspecialchars($seleccionaPlataforma['7'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="8"><?php echo htmlspecialchars($seleccionaPlataforma['8'], ENT_QUOTES, 'UTF-8'); ?></option>
                                <option value="9"><?php echo htmlspecialchars($seleccionaPlataforma['9'], ENT_QUOTES, 'UTF-8'); ?></option>
                            </select>           
                        </div>

                        <button class="btn btn-success my-2 my-sm-0" id="botonElo" name="botonElo" type="submit">
                            <?php echo htmlspecialchars($acceder['0'], ENT_QUOTES, 'UTF-8'); ?>
                        </button>
                    </form>
                </div>

                <!--Para poder cambiar la Cookie establecida-->
                <div id="divEloSel" style="display: none">
                    <div style="margin: auto;">
                        <p><?php echo htmlspecialchars($acceder['2'], ENT_QUOTES, 'UTF-8'); ?> <?php echo htmlspecialchars(substr($_COOKIE["EloJugador"],0,strpos($_COOKIE["EloJugador"],'-')), ENT_QUOTES, 'UTF-8'); ?></p>
                        <p><?php echo htmlspecialchars($acceder['3'], ENT_QUOTES, 'UTF-8'); ?> <?php echo htmlspecialchars($seleccionaPlataforma[substr($_COOKIE["EloJugador"], -1)], ENT_QUOTES, 'UTF-8'); ?></p>
                        
                        <button class="btn btn-success" id="botonCookie" name="botonCookie" type="submit">
                            <?php echo htmlspecialchars($acceder['1'], ENT_QUOTES, 'UTF-8'); ?>
                        </button>
                    </div>
                </div>

                <!--Formulario para seleccionar el idioma-->
                <div id="divIdiomas">
                    <div style="margin: auto;">
                        <a href="https://lsi2.ugr.es/fjmelero/chessai/?langID=eng">
                            <p style="color: white"><img src="assets/uk.png"> <?php echo htmlspecialchars($seleccionLenguaje['1'], ENT_QUOTES, 'UTF-8'); ?></p>
                        </a>
                        <a href="https://lsi2.ugr.es/fjmelero/chessai/?langID=esp">
                            <p style="color: white"><img src="assets/esp.png"> <?php echo htmlspecialchars($seleccionLenguaje['2'], ENT_QUOTES, 'UTF-8'); ?></p>
                        </a>
                        <a href="https://lsi2.ugr.es/fjmelero/chessai/?langID=fre">
                            <p style="color: white"><img src="assets/fre.png"> <?php echo htmlspecialchars($seleccionLenguaje['3'], ENT_QUOTES, 'UTF-8'); ?></p>
                        </a>
                    </div>
                </div>
            </li>
        </ul>
    </nav>
    
    <!--Texto introductorio-->
    <div class="navbar-nav bg-dark" id="instrucciones" style="display: block;">
        <div class="w3-container">
            <p style="font-size: 15px; margin-left: 10%; margin-right: 10%;"><?php echo htmlspecialchars($textoUgr['2'], ENT_QUOTES, 'UTF-8'); ?></p>
            <p style="font-size: 15px; margin-left: 10%; margin-right: 10%;"><?php echo htmlspecialchars($textoUgr['3'], ENT_QUOTES, 'UTF-8'); ?></p>
        </div>
    </div>

    <!--Error al intentar acceder-->
    <div class="alert alert-danger text-center" id="fracaso" style="display:none">
        <?php echo htmlspecialchars($fracaso['0'], ENT_QUOTES, 'UTF-8'); ?>
    </div>

    <!--Añadimos el formulario-->
    <?php
        if(isset($_COOKIE["EloJugador"])){
            include("formulario.php");
        }
    ?>

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