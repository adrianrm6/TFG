<?php

    
    /**
     * Método para realizar la conexión con el servidor
     *
     * @return conectar
     */
    function conectar(){
        $hostname = "localhost";
        $usuario = "root";
        $password = "";
        $db = "chessDB";
        
        try{
            // Generamos la conexión con el servidor
            $conectar = new PDO("mysql:host=$hostname;dbname=$db", $usuario, $password);
            $conectar->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);
            $conectar->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        } catch (PDOException $e){
            echo $e->getMessage();
        }

        return $conectar;
    }
?>