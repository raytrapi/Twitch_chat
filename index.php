<?php
use src\core\bd\BD;
?>
<html>
   <head>
   		<link href="css/base.css" rel="stylesheet" type="text/css">
   		
<meta http-equiv="refresh" content="5">

   </head>
   <body >
<?php
require_once 'src/core/bd/bd.inc';
$datos=BD::filas(BD::ejecutar("select m.id,m.fecha,m.idEstado,e.nombre,u.nombre usuario, m.mensaje mensaje, u.avatar avatar" 
                                ." from mensajes m, estados e, usuarios u where e.id=m.idEstado and u.id=idUsuario"
                                ." order by fecha desc limit 10"));
if(count($datos)>0){
    echo "<ul style='margin:15px'>";
    $i=1;
    foreach ($datos as $dato){
        echo "<li class=\"c".$i."\">";
        if(strlen($dato["avatar"])>0){
            echo "<img src=\"".$dato["avatar"]."\" width=\"48\" valign='middle'/>&nbsp;";
        }
        echo "<strong>".$dato["usuario"]."</strong> ".$dato["mensaje"]."</li>";
        $i++;
        
    };
    echo "</ul>";
}


?>   
   </body>
</html>	