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
                                ." and date_format(m.fecha,'%d/%m/%Y')=date_format(now(),'%d/%m/%Y')"
                                ." order by fecha desc limit 10"));
if(count($datos)>0){
    echo "<ul style='margin:15px'>";
    $i=1;
    foreach ($datos as $dato){
        echo "<li class=\"c".$i."\" style='background-color: #000040d0;color: #ffffff; padding:5px; margin: 2px 0; border-radius:5px'>";
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