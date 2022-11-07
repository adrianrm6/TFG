<?php
    include_once("database.php");

    // Nos conectamos a la base de datos
    $conectar = conectar();
    
    // Obtenemos el número de filas de la tabla etiquetas
    $stmt1 = $conectar->prepare('SELECT * FROM etiquetas');
    $stmt1->execute();

    $result1 = $stmt1->rowCount();

    $filas = 59;

    if ($result1 >= 0){
        $filas = $result1; 
    }

    // Número aleatorio
    $numAleatorio = rand(1, $filas);

    // Inicializamos el array de etiquetas
    $array  = array("opcion1"=>"", 
                    "opcion2"=>"", 
                    "opcion3"=>"", 
                    "opcion4"=>"",
                    "opcion5"=>"", 
                    "opcion6"=>"", 
                    "opcion7"=>"", 
                    "opcion8"=>"",
                    "opcion9"=>"", 
                    "opcion10"=>"");


    foreach ($array as $clave_opcion=>$opcion){
        if ($numAleatorio >= ($filas+1)){
            $numAleatorio = $numAleatorio % $filas;
        }

        // Obtenemos la fila de la base de datos
        $stmt2 = $conectar->prepare('SELECT * FROM etiquetas WHERE IDetiqueta=?');
        $stmt2->execute(array($numAleatorio));
        $valor = $stmt2->fetch();

        // Actualizamos el array
        $array["$clave_opcion"] = $valor[0];

        // Aumentamos el número aleatorio en una unidad
        $numAleatorio = $numAleatorio+rand(1, $filas-1);    
    }

    // Obtenemos el número de filas de la tabla posiciones
    $stmt3 = $conectar->prepare('SELECT * FROM posiciones');
    $stmt3->execute();

    $result3 = $stmt3->rowCount();


    $filasFEN = 5000;

    if ($result3 >= 0){
        $filasFEN = $result3; 
    }

    $numAleatorioFEN = rand(1, $filasFEN);

    // Obtenemos la fila de la base de datos
    $stmt4 = $conectar->prepare('SELECT * FROM posiciones WHERE IDfen=?');
    $stmt4->execute(array($numAleatorioFEN));
    $resultadoFEN = $stmt4->fetch();
    $codFEN = $resultadoFEN[1];

    // Cerramos la conexión
    $conectar = null;
?>

<script>
    document.getElementById("instrucciones").style.display = "none";
    document.getElementById("divElo").style.display = "none";
    document.getElementById("divEloSel").style.display = "grid";

    var codigo = '<?php echo htmlspecialchars(substr($codFEN,0,strpos($codFEN,';')), ENT_QUOTES, 'UTF-8'); ?>';
    var mov1 = '<?php echo htmlspecialchars(substr($codFEN,-4,2), ENT_QUOTES, 'UTF-8'); ?>';
    var mov2 = '<?php echo htmlspecialchars(substr($codFEN,-2,2), ENT_QUOTES, 'UTF-8'); ?>';
    var max = '<?php echo htmlspecialchars($filas, ENT_QUOTES, 'UTF-8'); ?>';
    var etiquetas = '<?php echo htmlspecialchars(implode(",", $etiquetas), ENT_QUOTES, 'UTF-8'); ?>'.split(",");
</script>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="CSS/fen.css" type="text/css" media="all" />
    
    <title>Formularios</title>    
</head>

<body>  
    <!--Fen erróneo-->
    <div class="alert alert-danger text-center" id="fracasoFen" style="display:none">
        <?php echo htmlspecialchars($fracaso['1'], ENT_QUOTES, 'UTF-8'); ?>
    </div>

    <!--CONTENIDO-->
    <div class="container" id="contenedor">
        <!--Formulario para etiquetar posiciones-->
        <form action="insertar.php" class="formulario" id="respuestas" name="respuestas" method="post">
            <!--Aquí se coloca la imagen de la posición-->
            <div class="card" id="cardImagen">                       
                <div id="image-container">
                    <div id="image-display">
                    </div>
                </div>
            </div>

            <!--Para pasar la variable a insertar.php-->
            <input type="hidden" id="numFEN" name="numFEN" value="<?php echo htmlspecialchars($numAleatorioFEN, ENT_QUOTES, 'UTF-8'); ?>"> 
            
            <div class="card" id="cardOpciones">
                <div class="container float-left">

                    <!--Botón para cambiar etiquetas no seleccionadas-->
                    <div class="container" id="cardCambioEtiquetas" name="cardCambioEtiquetas">
                        <button class="btn btn-primary btn-block text-center" id="botonCambiarEtiquetas" type="button">
                            <?php echo htmlspecialchars($enviarForm['1'], ENT_QUOTES, 'UTF-8'); ?>
                        </button>

                        <br>
                    </div>

                    <!--Conjunto de etiquetas seleccionadas aleatoriamente-->
                    <div class="checkbox" id="opcionesEtiquetas">
                        <ul>                
                            <li>
                                <input class="form-check" type="checkbox" id="opcion1" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion1"], ENT_QUOTES, 'UTF-8'); ?>"> 
                                <label for="opcion1" id="labelopcion1"><?php echo htmlspecialchars($etiquetas[$array["opcion1"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                            <input class="form-check" type="checkbox" id="opcion2" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion2"], ENT_QUOTES, 'UTF-8'); ?>">
                            <label for="opcion2" id="labelopcion2"><?php echo htmlspecialchars($etiquetas[$array["opcion2"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check" type="checkbox" id="opcion3" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion3"], ENT_QUOTES, 'UTF-8'); ?>">
                                <label for="opcion3" id="labelopcion3"><?php echo htmlspecialchars($etiquetas[$array["opcion3"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>        
                                <input class="form-check" type="checkbox" id="opcion4" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion4"], ENT_QUOTES, 'UTF-8'); ?>">
                                <label for="opcion4" id="labelopcion4"><?php echo htmlspecialchars($etiquetas[$array["opcion4"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>        
                                <input class="form-check" type="checkbox" id="opcion5" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion5"], ENT_QUOTES, 'UTF-8'); ?>">   
                                <label for="opcion5" id="labelopcion5"><?php echo htmlspecialchars($etiquetas[$array["opcion5"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>        
                                <input class="form-check" type="checkbox" id="opcion6" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion6"], ENT_QUOTES, 'UTF-8'); ?>">
                                <label for="opcion6" id="labelopcion6"><?php echo htmlspecialchars($etiquetas[$array["opcion6"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check" type="checkbox" id="opcion7" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion7"], ENT_QUOTES, 'UTF-8'); ?>"> 
                                <label for="opcion7" id="labelopcion7"><?php echo htmlspecialchars($etiquetas[$array["opcion7"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check" type="checkbox" id="opcion8" name="opcion[]" value="<?php echo htmlspecialchars($array["opcion8"], ENT_QUOTES, 'UTF-8'); ?>">
                                <label for="opcion8" id="labelopcion8"><?php echo htmlspecialchars($etiquetas[$array["opcion8"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check" type="checkbox" id="opcion9" name="opcion[]" value ="<?php echo htmlspecialchars($array["opcion9"], ENT_QUOTES, 'UTF-8'); ?>"> 
                                <label for="opcion9" id="labelopcion9"><?php echo htmlspecialchars($etiquetas[$array["opcion9"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check" type="checkbox" id="opcion10" name="opcion[]" value ="<?php echo htmlspecialchars($array["opcion10"], ENT_QUOTES, 'UTF-8'); ?>">
                                <label for="opcion10" id="labelopcion10"><?php echo htmlspecialchars($etiquetas[$array["opcion10"]], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>

                            <li>
                                <input class="form-check-no" type="checkbox" id="opcion11" name="ninguna">
                                <label for="opcion11"><?php echo htmlspecialchars($etiquetas['0'], ENT_QUOTES, 'UTF-8'); ?></label>
                            </li>
                        </ul>
                    </div>

                    <input type="submit" class="btn btn-primary btn-block text-center" id="enviar" name="enviar" value="<?php echo htmlspecialchars($enviarForm['0'], ENT_QUOTES, 'UTF-8'); ?>">  
                </div>
                
                <!--Aviso en caso de no seleccionar ninguna etiqueta-->
                <div class="alert alert-danger text-center" id="obligatorio" style="display:none">
                    <?php echo htmlspecialchars($obligatorio['0'], ENT_QUOTES, 'UTF-8'); ?>
                </div>
            </div>                                                  
            <!--Para saber el idioma seleccionado-->   
            <input type="hidden" id="idioma" name="idioma" value="<?php echo htmlspecialchars($lang, ENT_QUOTES, 'UTF-8'); ?>"/>
        </form>
    </div>

</body>

</html>