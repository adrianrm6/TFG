<?php
$server="localhost";
$user= "root"; /* Nombre de usuario de la base de datos */
$contrasena= ""; /* Contraseña */
$basededatos= "chessDB"; /* Nombre de la base de datos */
$tabla1= "respuestas"; /* Nombre de la tabla de su elección */
$tabla2= "etiquetas";

/* Acceso al sevidor SQL y creación de la tabla */
if ((!$link = mysqli_connect($server, $user, $contrasena, $basededatos))) 
  die(printf("<H3>No se puede conectar la base de datos: [%d] %s</H3>", mysqli_connect_errno(), mysqli_connect_error())); 
$result1 = mysqli_query($link, "SELECT `IDrespuesta`, `Elo`, `Pagina`, `Etiqueta`, `FEN` FROM " . $tabla1 
 . " WHERE (`Elo` = " . substr($_COOKIE["EloJugador"],0,strpos($_COOKIE["EloJugador"],'-')) . " AND `Pagina` = " . substr($_COOKIE["EloJugador"], -1) . ")"); 

  $row_cnt1 = mysqli_num_rows($result1); 
  printf("Se han encontrado " . $row_cnt1 . " filas del conjunto de datos<BR />");
  /* Ver la tabla en formato HTML */ 
  echo "<table border=\"1\" align=center width=50%"; 
  echo "<tr>"; 
  echo "<div color=\"#ffff00\">"; 
  $field_cnt1 = mysqli_field_count($link); 
  while ($field = mysqli_fetch_field($result1)) { 
    echo "<th>$field->name</A></th>"; 
  } 
  echo "</font></tr>"; 
  while($row = mysqli_fetch_row($result1)) { 
    echo "<tr>"; 
    for($i = 0; $i < $field_cnt1; $i++) { 
      echo "<td align=center>$row[$i]</td>"; 
    } 
    echo "</tr>\n"; 
  } 
  echo "</table>";
  /* close result set */ 
  mysqli_free_result($result1);

  $result2 = mysqli_query($link, "SELECT * FROM " . $tabla2);
  $row_cnt2 = mysqli_num_rows($result2);

  if ($row_cnt2 != 59){
    mysqli_query($link, "DELETE FROM " . $tabla2);
    mysqli_query($link, "ALTER TABLE " . $tabla2 . " AUTO_INCREMENT = 1");
    mysqli_query($link, "INSERT INTO " . $tabla2 . " (`IDetiqueta`, `Nombreetiqueta`) VALUES
    (1, 'Aire'),
    (2, 'Alfil Bueno'),
    (3, 'Alfil Malo'),
    (4, 'Alfiles de distino color'),
    (5, 'Alfiles del mismo color'),
    (6, 'Apertura del Centro'),
    (7, 'Ataque de las Minorías'),
    (8, 'Batería Diagonal'),
    (9, 'Batería Vertical'),
    (10, 'Bloqueo de Peón'),
    (11, 'Cambio Favorable'),
    (12, 'Centralización de Piezas'),
    (13, 'Columna Abierta'),
    (14, 'Columna Cerrada'),
    (15, 'Columa semiabierta'),
    (16, 'Control de Columna'),
    (17, 'Control de Diagonal'),
    (18, 'Control de Fila'),
    (19, 'Control del Centro'),
    (20, 'Coordinación Dama+Caballo'),
    (21, 'Coordinación de Piezas'),
    (22, 'Defensa'),
    (23, 'La pistola de Alekhine'),
    (24, 'Dominación'),
    (25, 'Enroque en flancos opuestos'),
    (26, 'Espacio'),
    (27, 'Evitar Cambio'),
    (28, 'Falange de Peones'),
    (29, 'Garita del Caballo'),
    (30, 'Iniciativa'),
    (31, 'Limitar Actividad de Pieza'),
    (32, 'Mayoría de Peones'),
    (33, 'Mejorar Actividad de Pieza'),
    (34, 'Pareja de Alfiles'),
    (35, 'Paseo del Rey'),
    (36, 'Penetración'),
    (37, 'Peón Aislado'),
    (38, 'Peón Envenenado'),
    (39, 'Peón Pasado'),
    (40, 'Peón Pasado Alejado'),
    (41, 'Peón Pasado Protegido'),
    (42, 'Peón Retrasado'),
    (43, 'Peones Doblados'),
    (44, 'Peones Ligados'),
    (45, 'Profilaxis'),
    (46, 'Rey Centralizado'),
    (47, 'Ruptura de Peón'),
    (48, 'Sacrificio Posicional - Calidad'),
    (49, 'Sacrificio Posicional - Dama'),
    (50, 'Sacrificio Posicional - Peón'),
    (51, 'Sacrificio Posicional - Pieza'),
    (52, 'Sacrificio Posicional - Torre'),
    (53, 'Seguridad del Rey'),
    (54, 'Sobreprotección'),
    (55, 'Tormenta de Peones'),
    (56, 'Torre en séptima'),
    (57, 'Torres Dobladas'),
    (58, 'Torres Ligadas'),
    (59, 'Traslado de Torre');");


    $result3 = mysqli_query($link, "SELECT * FROM " . $tabla2);
    $row_cnt3 = mysqli_num_rows($result3);
    printf("Se han encontrado " . $row_cnt3 . " filas del conjunto de datos<BR />");
      /* Ver la tabla en formato HTML */ 
    echo "<table border=\"1\" align=center width=50%"; 
    echo "<tr>"; 
    echo "<div color=\"#ffff00\">"; 
    $field_cnt3 = mysqli_field_count($link); 
    while ($field = mysqli_fetch_field($result3)) { 
      echo "<th>$field->name</A></th>"; 
    } 
    echo "</font></tr>"; 
    while($row = mysqli_fetch_row($result3)) { 
      echo "<tr>"; 
      for($i = 0; $i < $field_cnt3; $i++) { 
        echo "<td align=center>$row[$i]</td>"; 
      } 
      echo "</tr>\n"; 
    } 
    echo "</table>";

    mysqli_free_result($result3);
  }
  else{
    printf("Se han encontrado " . $row_cnt2 . " filas del conjunto de datos<BR />");
    /* Ver la tabla en formato HTML */ 
    echo "<table border=\"1\" align=center width=50%"; 
    echo "<tr>"; 
    echo "<div color=\"#ffff00\">"; 
    $field_cnt2 = mysqli_field_count($link); 
    while ($field = mysqli_fetch_field($result2)) { 
      echo "<th>$field->name</A></th>"; 
    } 
    echo "</font></tr>"; 
    while($row = mysqli_fetch_row($result2)) { 
      echo "<tr>"; 
      for($i = 0; $i < $field_cnt2; $i++) { 
        echo "<td align=center>$row[$i]</td>"; 
      } 
      echo "</tr>\n"; 
    } 
    echo "</table>";
  }

  mysqli_free_result($result2);
  mysqli_close($link);
?>