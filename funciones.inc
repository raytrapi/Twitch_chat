<?php
$urls=[
    "autenticacion"=>["servidor"=>"https://id.twitch.tv/oauth2/authorize"],
    "info"=>["servidor"=>"https://api.twitch.tv/helix/users"],
    // https://twitch.tv/"
    //"join_chat"=>["servidor"=>"irc-ws.chat.twitch.tv","puerto"=>"80"]
   //"join_chat"=>["servidor"=>"irc-ws.chat.twitch.tv","puerto"=>"443"]
    "join_chat"=>["servidor"=>"irc.chat.twitch.tv","puerto"=>"6667"]
   //"join_chat"=>["servidor"=>"irc.chat.twitch.tv","puerto"=>"6697"]
];
include "cfg/config.inc";

function cogerOAuth(){
    global $urls;
    $s = curl_init();
    $parametros="client_id=".ID_CLIENTE."&redirect_uri=".REDIRECT."&response_type=token&scope=chat:read&claims={\"id_token\":{\"email_verified\":null}}";
    curl_setopt($s,CURLOPT_URL,$urls["autenticacion"]["servidor"]."?".$parametros); 
    curl_setopt($s,CURLOPT_SSL_VERIFYPEER,false);
    curl_setopt($s,CURLOPT_TIMEOUT,3000);
    //curl_setopt($s,CURLOPT_MAXREDIRS,$this->_maxRedirects);
    curl_setopt($s,CURLOPT_RETURNTRANSFER,true);
    curl_setopt($s,CURLOPT_FOLLOWLOCATION,$seguir); 
    $resultado=curl_exec($s);
    $info = curl_getinfo($s,CURLINFO_HTTP_CODE); 
    print_r($resultado);
    curl_close($s); 
    
}

function info(){
    //curl -H 'Client-ID: p0gch4mp101fy451do9uod1s1x9i4a' \
    //-X GET 'https://api.twitch.tv/helix/streams?game_id=33214'
    global $urls;
    $s = curl_init();
    $parametros="login=prex_directo";
    curl_setopt($s,CURLOPT_URL,$urls["info"]["servidor"]."?".$parametros);
    
    $cabeceras = array("Client-ID: ".ID_CLIENTE);
    curl_setopt($s, CURLOPT_HTTPHEADER, $cabeceras);
    
    curl_setopt($s,CURLOPT_SSL_VERIFYPEER,false);
    curl_setopt($s,CURLOPT_TIMEOUT,3000);
    //curl_setopt($s,CURLOPT_MAXREDIRS,$this->_maxRedirects);
    curl_setopt($s,CURLOPT_RETURNTRANSFER,true);
    
    $resultado=curl_exec($s);
    $info = curl_getinfo($s,CURLINFO_HTTP_CODE);
    print_r($resultado);
    curl_close($s);/**/ 
}

function cogerChats(){
    /*curl -H 'Accept: application/vnd.twitchtv.v5+json' \
    -H 'Client-ID: uo6dggojyb8d6soh92zknwmi5ej1q2' \
    -H 'Authorization: OAuth cfabdegwdoklmawdzdo98xt2fo512y' \
    -X GET 'https://api.twitch.tv/kraken/chat/44322889/rooms'*/
    $s = curl_init();
    
    curl_setopt($s,CURLOPT_URL,"https://api.twitch.tv/kraken/chat/441968303/rooms");
    
    $cabeceras = array("Client-ID: ".ID_CLIENTE,"Authorization: OAuth ". TOKEN,"Accept: application/vnd.twitchtv.v5+json");
    curl_setopt($s, CURLOPT_HTTPHEADER, $cabeceras);
    
    curl_setopt($s,CURLOPT_SSL_VERIFYPEER,false);
    curl_setopt($s,CURLOPT_TIMEOUT,3000);
    //curl_setopt($s,CURLOPT_MAXREDIRS,$this->_maxRedirects);
    curl_setopt($s,CURLOPT_RETURNTRANSFER,true);
    
    $resultado=curl_exec($s);
    $info = curl_getinfo($s,CURLINFO_HTTP_CODE);
    print_r($resultado);
    curl_close($s);
}
function cogerChat2(){
    global $urls;
    $socket=socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
    socket_connect($socket, $urls["join_chat"]["servidor"], $urls["join_chat"]["puerto"]);
    
    //$sock_data = socket_set_option($socket, SOL_SOCKET, SO_BROADCAST, 1); //Set
    $conexion="PASS oauth:".TOKEN."\nNICK ".USUARIO."\n";
    $sock_data = socket_write($socket, $conexion, strlen($conexion)); //Send data
    $leido=socket_read($socket, 1000);
    
    echo($leido);
    socket_close($socket); //Close socket
}

function cogerStream(){
    /*curl -H 'Accept: application/vnd.twitchtv.v5+json' \
    -H 'Client-ID: uo6dggojyb8d6soh92zknwmi5ej1q2' \
    -X GET 'https://api.twitch.tv/kraken/streams/44322889'*/
    $s = curl_init();
    
    curl_setopt($s,CURLOPT_URL,"https://api.twitch.tv/kraken/streams/441968303");
    
    $cabeceras = array("Client-ID: ".ID_CLIENTE,"Accept: application/vnd.twitchtv.v5+json");
    curl_setopt($s, CURLOPT_HTTPHEADER, $cabeceras);
    
    curl_setopt($s,CURLOPT_SSL_VERIFYPEER,false);
    curl_setopt($s,CURLOPT_TIMEOUT,3000);
    //curl_setopt($s,CURLOPT_MAXREDIRS,$this->_maxRedirects);
    curl_setopt($s,CURLOPT_RETURNTRANSFER,true);
    
    $resultado=curl_exec($s);
    $info = curl_getinfo($s,CURLINFO_HTTP_CODE);
    print_r($resultado);
    curl_close($s);
    
}
function cogerChat(){
  global $urls;
  
  $error="";
  $socket = fsockopen($urls["join_chat"]["servidor"], $urls["join_chat"]["puerto"], $errorno, $error);
  if(!$socket){
    echo "NO SOCKET [".$error."]";
    return;
  }
  socket_set_timeout($socket, 30);
  $conexion="PASS oauth:".TOKEN."\nNICK ".USUARIO."\n";
  fwrite($socket,$conexion);
  $salida="-";
  $estado=0;
  $ESPERAS=[":tmi.twitch.tv 376 ".USUARIO." :>\r\n",":End of /NAMES list"];;
  
  
  while (!feof($socket)) {
      $salida=fgets($socket, 128);
      //$salida=str_replace("\n", "<br/>", $salida);
      //$salida=str_replace("\r", ".<br/>", $salida);
      echo $salida."<br/>";
      if($salida==$ESPERAS[0] || strpos($salida,$ESPERAS[1])>0){
          $estado++; 
      }
      switch ($estado){
          case 1:
              $estado++;
              //$mensaje="JOIN #84e60028-d67c-4c17-b5ee-c4776943f682\n";
              //$mensaje="JOIN #chatrooms:441968303:35189105408\n";//
              $mensaje="JOIN #prex_directo\n";
              echo $mensaje."<br/>";
              fwrite($socket,$mensaje);
              break;
              
          case 2:
              $estado++;
              //$mensaje="JOIN #84e60028-d67c-4c17-b5ee-c4776943f682\n";
              //$mensaje="NOTICE\n";
              //echo $mensaje."<br/>";
              //fwrite($socket,$mensaje);
              break;
      }
      if($estado==1 ){
           
      }else{
          
      }
      
      
      ob_flush();
      flush();
      
  }
  fclose($socket);
  echo("COMPLETO");/**/

}