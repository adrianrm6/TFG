<?php
    include_once("database.php");

    // Nos conectamos a la base de datos
    $conectar = conectar();

    // En primer lugar comprobamos si existe la cookie
    if (isset($_COOKIE["EloJugador"])){
        // Comprobamos si hemos enviado el formulario y si hemos marcado una opción que no sea "ninguna opción"
        // Si es así añadimos en la tabla respuestas las filas correspondientes a las etiquetas y al FEN
        if (isset($_POST['enviar'])){
            if (isset($_POST['opcion'])){
                if (is_array($_POST['opcion'])){

                    // Obtenemos los valores a insertar en la tabla
                    $Elo = substr($_COOKIE["EloJugador"],0,strpos($_COOKIE["EloJugador"],'-'));
                    
                    // Comprobamos si la variable es numérica
                    if (ctype_digit($Elo)){

                        switch (substr($_COOKIE["EloJugador"], -1)) {
                            case "1":
                                $Pagina = 1;  
                            break; 
                            case "2":
                                $Pagina = 2; 
                            break;
                            case "3":
                                $Pagina = 3;
                            break;
                            case "4":
                                $Pagina = 4;   
                            break;
                            case "5":
                                $Pagina = 5;
                            break;
                            case "6":
                                $Pagina = 6;   
                            break;    
                            case "7":
                                $Pagina = 7;      
                            break; 
                            case "8":
                                $Pagina = 8;      
                            break;  
                            case "9":
                                $Pagina = 9;
                            break;   
                            default:
                                $Pagina = 9;
                            break;
                        }

                        // Fen de la posición
                        $FEN = htmlentities(trim(strip_tags(stripslashes($_POST['numFEN']))), ENT_NOQUOTES, 'UTF-8');

                        if (ctype_digit(($FEN))){
                            // Recorremos las opciones marcadas y añadimos por cada opción una fila en la tabla respuestas
                            foreach($_POST['opcion'] as $key => $value){
                                $idEtiqueta = htmlspecialchars(stripslashes(trim($value)));
                                if (ctype_digit($idEtiqueta)){
                                    // Sentencia SQL
                                    $insertar = $conectar->prepare('INSERT INTO respuestas(Elo, Pagina, Etiqueta, FEN) VALUES (?,?,?,?)');
                                    // Bind
                                    $insertar->bindParam(1,$Elo);
                                    $insertar->bindParam(2,$Pagina);
                                    $insertar->bindParam(3,$idEtiqueta);
                                    $insertar->bindParam(4,$FEN);
                                    
                                    // Insertamos en la tabla respuestas
                                    $insertar->execute();
                                }
                            }
                        }
                    }
                    else{
                        echo'<script type="text/javascript">
                                alert("ELO must be numeric");
                            </script>';
                    }
                }
            }   
        }
    }

    // Cerramos la conexión
    $conectar = null;
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
</head>

<body>

    <script language="javascript">
        var idiomaSeleccionado = '<?php echo htmlspecialchars($_POST['idioma'], ENT_QUOTES, 'UTF-8'); ?>';
        var frase = 'Do you want to continue tagging items?';

        if (idiomaSeleccionado == 'esp'){
            frase = '¿Desea seguir etiquetando posiciones?';
        }
        else if (idiomaSeleccionado == 'fre'){
            frase = 'Souhaitez-vous continuer à marquer des postes?';
        }
        // Comprobamos si el usuario quiere seguir evaluando
        if (confirm(frase) == true) {
            if (idiomaSeleccionado == 'eng' || idiomaSeleccionado == 'esp' || idiomaSeleccionado == 'fre'){
                window.location.replace("https://lsi2.ugr.es/fjmelero/chessai/?langID=<?php echo htmlspecialchars($_POST['idioma'], ENT_QUOTES, 'UTF-8'); ?>");
            }
            else{
                window.location.replace("https://lsi2.ugr.es/fjmelero/chessai/");
            }
        } 
        else {
            if (idiomaSeleccionado == 'eng' || idiomaSeleccionado == 'esp' || idiomaSeleccionado == 'fre'){
                window.location.replace("https://lsi2.ugr.es/fjmelero/chessai/despedida.php?langID=<?php echo htmlspecialchars($_POST['idioma'], ENT_QUOTES, 'UTF-8'); ?>");
            }
            else{
                window.location.replace("https://lsi2.ugr.es/fjmelero/chessai/despedida.php?langID=eng");
            }
        }
    </script>
</body>

</html>