<?php
use src\core\bd\BD;
?>
<html>
   <head>
   		<link href="css/base.css" rel="stylesheet" type="text/css">
   		
<meta http-equiv="refresh" content="2">

   </head>
   <body >
<?php
require_once 'src/core/bd/bd.inc';
$datos=BD::filas(BD::ejecutar("select m.id,m.fecha,m.idEstado,e.nombre,u.nombre usuario, m.mensaje mensaje" 
                                ." from mensajes m, estados e, usuarios u where e.id=m.idEstado and u.id=idUsuario"
                                ." order by fecha desc limit 10"));
if(count($datos)>0){
    echo "<ul>";
    $i=10;
    foreach ($datos as $dato){
        echo "<li style=\"opacity:".($i/10)."\"><strong>".$dato["usuario"]."</strong> ".$dato["mensaje"]."</li>";
        $i--;
        
    };
    echo "</ul>";
}


?>   
   </body>
</html>	