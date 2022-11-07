<?php
$server="localhost";
$user= "root"; /* Nombre de usuario de la base de datos */
$contrasena= ""; /* Contraseña */
$basededatos= "chessDB"; /* Nombre de la base de datos */
$tabla1= "respuestas"; /* Nombre de la tabla de su elección */

/* Acceso al sevidor SQL y creación de la tabla */
if ((!$link = mysqli_connect($server, $user, $contrasena, $basededatos))) 
  die(printf("<H3>No se puede conectar la base de datos: [%d] %s</H3>", mysqli_connect_errno(), mysqli_connect_error())); 
$result1 = mysqli_query($link, "SELECT * FROM " . $tabla1); 

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
mysqli_close($link);
?>