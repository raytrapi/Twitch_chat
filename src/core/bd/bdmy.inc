<?php 
namespace src\core\bd;
require_once "bd.inc";
use src\seguridad\Log;

class BDMY extends BD{
    private $mysqli;
    public function __construct($datos){
        //gestorBD:usuario\password@host:puerto\esquema
        //mysql:api\000@localhost:3306\api
        
//        $datos=self::cogerDatosConexion($cadenaConexion);
        
        $this->mysqli = new \mysqli("p:".$datos["servidor"].":".$datos["puerto"], $datos["usuario"], $datos["clave"], $datos["esquema"]);
        return $this;
    }
    public function _ejecutar($consulta, $opciones = []){
        $sentencia = $this->mysqli->prepare($consulta);
        if($sentencia->execute()){
            return $sentencia->get_result();
        }else{
            return null;
        }
        
    }
    public function _filas($res){
        return mysqli_fetch_all($res,MYSQLI_ASSOC);
    }
    
}
